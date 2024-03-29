#ifndef AVLTREE
#define AVLTREE

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct node {
	struct node* left;
	struct node* right;
	int value;
	int height;
	char fname[20];
	char lname[20];
	char code[10];

}NODE;


NODE* insertNode(NODE* node, int v, DATA*data);
NODE* rotateRightBST(NODE* start);
NODE* rotateLeftBST(NODE* start);
NODE* rotateRightLeftBST(NODE* start);
NODE* rotateLeftRightBST(NODE* start);

NODE* balanceBST(NODE* start);
NODE* searchAVL(NODE* node, int v);
NODE* insertNode(NODE* node, int v, char* fname, char* lname, char* code);
void testSearch(NODE* start, int searchVal);
void testSearchAVLfromZero(NODE* start, int n);
NODE* testInsertNodes(NODE* start, int n, DATA* data);




//rotacia uzlov doprava
NODE* rotateRightBST(NODE* start) {
	NODE* newTop = start->left;
	/*start->left = newTop->right;

	if (newTop->right != NULL) {
		newTop->right->left = newTop;
		newTop->right = newTop->right->right;
	}*/
	start->left = newTop->right;
	newTop->right = start;

	return newTop;

}

//rotacia uzlov dolava
NODE* rotateLeftBST(NODE* start) {
	NODE* newTop = start->right;
	/*start->right = newTop->left;

	if (newTop->left != NULL) {
		newTop->left->right = newTop;
		newTop->left = newTop->left->left;
	}*/
	start->right = newTop->left;
	newTop->left = start;

	return newTop;

}

//specialna rotacia a potom doprava
NODE* rotateRightLeftBST(NODE* start) {
	NODE* oldTop = start->left;
	start->left = oldTop->right;
	oldTop->right = start->left->left;
	start->left->left = oldTop;

	start = rotateRightBST(start);

	return start;

}

//specialna rotacia a potom dolava
NODE* rotateLeftRightBST(NODE* start) {
	NODE* oldTop = start->right;
	NODE* newTop = oldTop->left;
	start->right = newTop;
	oldTop->left = newTop->right;
	newTop->right = oldTop;

	start = rotateLeftBST(start);

	return start;

}

//hlavanie prvku podla kluca v
NODE* searchAVL(NODE* node, int v) {
	if (node != NULL) {
		if (node->value < v)
			return searchAVL(node->right, v);
		else if (node->value > v)
			return searchAVL(node->left, v);
		else {
			return node;
		}
	}
	return NULL;
}

//vybalancovanie stromu
NODE* balanceBST(NODE* start) {
	int left = 0, right = 0, R = 0, L = 0;
	//nacitaj vysky podstromov
	if (start->left != NULL)
		left = start->left->height + 1;
	if (start->right != NULL)
		right = start->right->height + 1;

	//lava strana je prilis velka
	if (left - right > 1) {
		//zisti hlbky podstromov laveho podstromu
		if (start->left != NULL && start->left->left != NULL)
			L = start->left->left->height + 1;
		if (start->left != NULL && start->left->right != NULL)
			R = start->left->right->height + 1;

		//podla hlbok spravi spravnu rotaciu
		if (R - L > 0) {
			L = start->left->height--;
			R = start->height--;
			start = rotateRightLeftBST(start);
			start->height = R > L ? R : L;
		}
		else {
			start->height = R > right ? R : right;
			start->left->height = start->height > L ? start->height : L;
			start = rotateRightBST(start);
		}
	} //prava strana je prilis velka
	else if (left - right < -1) {
		//zisti hlbky podstromov praveho podstromu
		if (start->right != NULL && start->right->left != NULL)
			L = start->right->left->height + 1;
		if (start->right != NULL && start->right->right != NULL)
			R = start->right->right->height + 1;

		//podla hlbok spravi spravnu rotaciu
		if (R - L < 0) {
			R = start->right->height--;
			L = start->height--;
			start = rotateLeftRightBST(start);
			start->height = R > L ? R : L;
		}
		else {
			start->height = L > left ? L : left;
			start->right->height = start->height > R ? start->height : R;
			start = rotateLeftBST(start);

		}
	}
	else {
		start->height = left > right ? left : right;
	}


	return start;
}

//vkladanie prvku do AVL stromu
NODE* insertNode(NODE* node, int v, char* fname, char* lname, char* code) {

	if (node != NULL) {
		//rekurzivne sa presiri do spravneho listu a spatne vybalancuje strom
		if (node->value < v) {
			node->right = insertNode(node->right, v, fname, lname, code);
			node = balanceBST(node);

		}
		else if (node->value > v) {
			node->left = insertNode(node->left, v,  fname, lname, code);
			node = balanceBST(node);
		}
		else {
			//printf("Given value already exists\n");
			return node;
		}
	}
	else {
		//v prazdnom liste vytvori NODE s parametrami
		node = malloc(sizeof(NODE));
		node->left = NULL;
		node->right = NULL;
		node->value = v;
		node->height = 0;
		//printf("%d\n", v);

		strcpy(node->code, code);
		strcpy(node->lname, lname);
		strcpy(node->fname, fname);
	}
	return node;
}

void testSearchAVL(NODE* start, int n, DATA* data) {
	int ms, nop = 0;
	NODE *a;
	clock_t dt = 0, now = clock();
		
	for (int i = 0; i < n; i++) {
		a = searchAVL(start, data[i].num);
		if (a == NULL) {
			nop++;
		}
	}
	dt = clock() - now;
	//dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;

	printf("Hladanie v AVL strome trvalo %dms.. nenaslo %d\n", ms , nop);
}

void testSearchAVLfromZero(NODE* start, int n) {
	int ms, nop = 0;
	NODE* a;
	clock_t dt = 0, now = clock();

	for (int i = 0; i < n; i++) {
		a = searchAVL(start, i);
		if (a == NULL) {
			nop++;
		}
	}
	dt = clock() - now;
	//dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;

	printf("Hladanie v AVL strome trvalo %dms.. nenaslo %d\n", ms , nop);
}

NODE* testInsertNodes(NODE* start, int n, DATA* data) {
	int i, r, ms;
	clock_t dt, now = clock();

	for (i = 0; i < n; i++) {
		start = insertNode(start, data[i].num, data[i].fname, data[i].lname, data[i].code);
	}

	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Naplnenie AVL stromu %d prvkami trvalo %dms\n", n,  ms );

	return start;
}

NODE* testInsertNodesDupl(NODE* start, int n, DATA* data) {
	int i, r, ms;
	clock_t dt, now = clock();

	for (i = 0; i < n/2; i++) {
		start = insertNode(start, data[i].num, data[i].fname, data[i].lname, data[i].code);
		start = insertNode(start, data[i].num, data[i].fname, data[i].lname, data[i].code);
	}

	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Naplnenie AVL stromu %d(%d pokusov) prvkami trvalo %dms\n", n/2,n, ms );

	return start;
}




#endif 
