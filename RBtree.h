#ifndef RBTREE
#define RBTREE
//https://www.programiz.com/dsa/red-black-tree
// Implementing Red-Black Tree in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum nodeColor {
	RED,
	BLACK
};


struct rbNode {
	int dats, color;
	struct rbNode* link[2];

	//moje
	char fname[20]; 
	char lname[20];
	char code[10];
};

struct rbNode* root = NULL;

// Create a red-black tree
struct rbNode* createNode(int dats, char* fname, char* lname, char* code) {
	struct rbNode* newnode;
	newnode = (struct rbNode*)malloc(sizeof(struct rbNode));
	newnode->dats = dats;
	newnode->color = RED;
	newnode->link[0] = newnode->link[1] = NULL;
	strcpy(newnode->code, code);
	strcpy(newnode->lname, lname);
	strcpy(newnode->fname, fname);
	/*
		char fname[20];
		char lname[20];
		char code[10];*/
	return newnode;
}

// Insert an node
void insertion(int dats, char* fname, char* lname, char* code) {
	struct rbNode* stack[98], * ptr, * newnode, * xPtr, * yPtr;
	int dir[98], ht = 0, index;
	ptr = root;
	if (!root) {
		root = createNode(dats, fname, lname, code);
		return;
	}

	stack[ht] = root;
	dir[ht++] = 0;
	while (ptr != NULL) {
		if (ptr->dats == dats) {
			//printf("Duplicates Not Allowed!!\n");
			return;
		}
		index = (dats - ptr->dats) > 0 ? 1 : 0;
		stack[ht] = ptr;
		ptr = ptr->link[index];
		dir[ht++] = index;
	}
	stack[ht - 1]->link[index] = newnode = createNode(dats, fname, lname,  code);
	while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
		if (dir[ht - 2] == 0) {
			yPtr = stack[ht - 2]->link[1];
			if (yPtr != NULL && yPtr->color == RED) {
				stack[ht - 2]->color = RED;
				stack[ht - 1]->color = yPtr->color = BLACK;
				ht = ht - 2;
			}
			else {
				if (dir[ht - 1] == 0) {
					yPtr = stack[ht - 1];
				}
				else {
					xPtr = stack[ht - 1];
					yPtr = xPtr->link[1];
					xPtr->link[1] = yPtr->link[0];
					yPtr->link[0] = xPtr;
					stack[ht - 2]->link[0] = yPtr;
				}
				xPtr = stack[ht - 2];
				xPtr->color = RED;
				yPtr->color = BLACK;
				xPtr->link[0] = yPtr->link[1];
				yPtr->link[1] = xPtr;
				if (xPtr == root) {
					root = yPtr;
				}
				else {
					stack[ht - 3]->link[dir[ht - 3]] = yPtr;
				}
				break;
			}
		}
		else {
			yPtr = stack[ht - 2]->link[0];
			if ((yPtr != NULL) && (yPtr->color == RED)) {
				stack[ht - 2]->color = RED;
				stack[ht - 1]->color = yPtr->color = BLACK;
				ht = ht - 2;
			}
			else {
				if (dir[ht - 1] == 1) {
					yPtr = stack[ht - 1];
				}
				else {
					xPtr = stack[ht - 1];
					yPtr = xPtr->link[0];
					xPtr->link[0] = yPtr->link[1];
					yPtr->link[1] = xPtr;
					stack[ht - 2]->link[1] = yPtr;
				}
				xPtr = stack[ht - 2];
				yPtr->color = BLACK;
				xPtr->color = RED;
				xPtr->link[1] = yPtr->link[0];
				yPtr->link[0] = xPtr;
				if (xPtr == root) {
					root = yPtr;
				}
				else {
					stack[ht - 3]->link[dir[ht - 3]] = yPtr;
				}
				break;
			}
		}
	}
	root->color = BLACK;
}

// Delete a node
void deletion(int dats) {
	struct rbNode* stack[98], * ptr, * xPtr, * yPtr;
	struct rbNode* pPtr, * qPtr, * rPtr;
	int dir[98], ht = 0, diff, i;
	enum nodeColor color;

	if (!root) {
		printf("Tree not available\n");
		return;
	}

	ptr = root;
	while (ptr != NULL) {
		if ((dats - ptr->dats) == 0)
			break;
		diff = (dats - ptr->dats) > 0 ? 1 : 0;
		stack[ht] = ptr;
		dir[ht++] = diff;
		ptr = ptr->link[diff];
	}

	if (ptr->link[1] == NULL) {
		if ((ptr == root) && (ptr->link[0] == NULL)) {
			free(ptr);
			root = NULL;
		}
		else if (ptr == root) {
			root = ptr->link[0];
			free(ptr);
		}
		else {
			stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
		}
	}
	else {
		xPtr = ptr->link[1];
		if (xPtr->link[0] == NULL) {
			xPtr->link[0] = ptr->link[0];
			color = xPtr->color;
			xPtr->color = ptr->color;
			ptr->color = color;

			if (ptr == root) {
				root = xPtr;
			}
			else {
				stack[ht - 1]->link[dir[ht - 1]] = xPtr;
			}

			dir[ht] = 1;
			stack[ht++] = xPtr;
		}
		else {
			i = ht++;
			while (1) {
				dir[ht] = 0;
				stack[ht++] = xPtr;
				yPtr = xPtr->link[0];
				if (!yPtr->link[0])
					break;
				xPtr = yPtr;
			}

			dir[i] = 1;
			stack[i] = yPtr;
			if (i > 0)
				stack[i - 1]->link[dir[i - 1]] = yPtr;

			yPtr->link[0] = ptr->link[0];

			xPtr->link[0] = yPtr->link[1];
			yPtr->link[1] = ptr->link[1];

			if (ptr == root) {
				root = yPtr;
			}

			color = yPtr->color;
			yPtr->color = ptr->color;
			ptr->color = color;
		}
	}

	if (ht < 1)
		return;

	if (ptr->color == BLACK) {
		while (1) {
			pPtr = stack[ht - 1]->link[dir[ht - 1]];
			if (pPtr && pPtr->color == RED) {
				pPtr->color = BLACK;
				break;
			}

			if (ht < 2)
				break;

			if (dir[ht - 2] == 0) {
				rPtr = stack[ht - 1]->link[1];

				if (!rPtr)
					break;

				if (rPtr->color == RED) {
					stack[ht - 1]->color = RED;
					rPtr->color = BLACK;
					stack[ht - 1]->link[1] = rPtr->link[0];
					rPtr->link[0] = stack[ht - 1];

					if (stack[ht - 1] == root) {
						root = rPtr;
					}
					else {
						stack[ht - 2]->link[dir[ht - 2]] = rPtr;
					}
					dir[ht] = 0;
					stack[ht] = stack[ht - 1];
					stack[ht - 1] = rPtr;
					ht++;

					rPtr = stack[ht - 1]->link[1];
				}

				if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
					(!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
					rPtr->color = RED;
				}
				else {
					if (!rPtr->link[1] || rPtr->link[1]->color == BLACK) {
						qPtr = rPtr->link[0];
						rPtr->color = RED;
						qPtr->color = BLACK;
						rPtr->link[0] = qPtr->link[1];
						qPtr->link[1] = rPtr;
						rPtr = stack[ht - 1]->link[1] = qPtr;
					}
					rPtr->color = stack[ht - 1]->color;
					stack[ht - 1]->color = BLACK;
					rPtr->link[1]->color = BLACK;
					stack[ht - 1]->link[1] = rPtr->link[0];
					rPtr->link[0] = stack[ht - 1];
					if (stack[ht - 1] == root) {
						root = rPtr;
					}
					else {
						stack[ht - 2]->link[dir[ht - 2]] = rPtr;
					}
					break;
				}
			}
			else {
				rPtr = stack[ht - 1]->link[0];
				if (!rPtr)
					break;

				if (rPtr->color == RED) {
					stack[ht - 1]->color = RED;
					rPtr->color = BLACK;
					stack[ht - 1]->link[0] = rPtr->link[1];
					rPtr->link[1] = stack[ht - 1];

					if (stack[ht - 1] == root) {
						root = rPtr;
					}
					else {
						stack[ht - 2]->link[dir[ht - 2]] = rPtr;
					}
					dir[ht] = 1;
					stack[ht] = stack[ht - 1];
					stack[ht - 1] = rPtr;
					ht++;

					rPtr = stack[ht - 1]->link[0];
				}
				if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
					(!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
					rPtr->color = RED;
				}
				else {
					if (!rPtr->link[0] || rPtr->link[0]->color == BLACK) {
						qPtr = rPtr->link[1];
						rPtr->color = RED;
						qPtr->color = BLACK;
						rPtr->link[1] = qPtr->link[0];
						qPtr->link[0] = rPtr;
						rPtr = stack[ht - 1]->link[0] = qPtr;
					}
					rPtr->color = stack[ht - 1]->color;
					stack[ht - 1]->color = BLACK;
					rPtr->link[0]->color = BLACK;
					stack[ht - 1]->link[0] = rPtr->link[1];
					rPtr->link[1] = stack[ht - 1];
					if (stack[ht - 1] == root) {
						root = rPtr;
					}
					else {
						stack[ht - 2]->link[dir[ht - 2]] = rPtr;
					}
					break;
				}
			}
			ht--;
		}
	}
}

// Print the inorder traversal of the tree
void inorderTraversal(struct rbNode* node) {
	if (node) {
		inorderTraversal(node->link[0]);
		printf("%d  ", node->dats);
		inorderTraversal(node->link[1]);
	}
	return;
}

//moje
struct rbNode* searchRB(struct rbNode* node, int v) {
	if (node != NULL) {
		if (node->dats < v)
			return searchRB(node->link[1], v);
		else if (node->dats > v)
			return searchRB(node->link[0], v);
		else {
			return node;
		}
	}
	return NULL;
}

void  testInsertRB(int n, DATA* data) {
	int i, r, ms;
	clock_t dt, now = clock();

	for (i = 0; i < n; i++) {
		insertion(data[i].num, data[i].fname, data[i].lname, data[i].code);

	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Naplnenie Red-black stromu %d prvkami trvalo %dms\n", n, ms );

	//return start;
}

void  testInsertRBDupl(int n, DATA* data) {
	int i, r, ms;
	clock_t dt, now = clock();

	for (i = 0; i < n/2; i++) {
		insertion(data[i].num, data[i].fname, data[i].lname, data[i].code);
		insertion(data[i].num, data[i].fname, data[i].lname, data[i].code);
	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Naplnenie Red-black stromu %d(%d pokusov) prvkami trvalo %dms\n", n/2,n, ms );

	//return start;
}

void testSearchRB(struct rbNode* start, int n, DATA* data) {
	int ms, nop = 0;
	clock_t dt, now = clock();
	struct rbNode* a;
	for (int i = 0; i < n; i++) {
		a = searchRB(start, data[i].num);
		if (a == NULL) {
			nop++;
		}
	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;


	printf("Hladanie v Red-Black strome trvalo %dms.. nenaslo %d\n", ms , nop);
}


void testSearchRBfromZero(struct rbNode* start, int n) {
	int ms, nop = 0;
	clock_t dt, now = clock();
	struct rbNode* a;
	for (int i = 0; i < n; i++) {
		a = searchRB(start, i);
		if (a == NULL) {
			nop++;
		}
	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;

	
	printf("Hladanie v Red-Black strome trvalo %dms.. nenaslo %d\n", ms , nop);
}

// Driver code

#endif //  RBTREE
