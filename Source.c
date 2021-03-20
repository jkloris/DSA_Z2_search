#include <stdio.h>


typedef struct node {
	struct node *left;
	struct node *right;
	int value;
	int height;
}NODE;

int _print_t(NODE* tree, int is_left, int offset, int depth, char s[20][255]); //TEMP
void print_t(NODE* tree); //TEMP

NODE* insertNode(NODE* node, int v);
NODE* rotateRightBST(NODE* start);
NODE* rotateLeftBST(NODE* start);
NODE* rotateRightLeftBST(NODE* start);
NODE* rotateLeftRightBST(NODE* start);
int getTreeHeight(NODE* node);
NODE* balanceBST(NODE* start);
NODE* search(NODE* node, int v);

int main() {

	NODE* start = NULL;
	int r;
	for (int i = 0; i < 200000; i++) {
		r = rand() % 500000 + 1;
		start = insertNode(start, r);
		//print_t(start);
		//printf("%d\n", r);
	}

	NODE *a = search(start, 456);
	
	
	
	

	//print_t(start);
	return 0;
}

NODE* search(NODE* node, int v) {
	if (node != NULL) {
		if (node->value < v)
			return search(node->right, v);
		else if (node->value > v)
			return search(node->left, v);
		else {
			return node;
		}
	}
	return NULL;
}

int getTreeHeight(NODE* node) {
	if (node != NULL) {
		int left = getTreeHeight(node->left);
		int right = getTreeHeight(node->right);
		return ( 1 + ((left > right) ? left : right));
	}
	return -1;
}

NODE* balanceBST(NODE* start) {
	/*int left = getTreeHeight(start->left)+ 1;
	int right = getTreeHeight(start->right)+ 1;*/
	int left = 0, right = 0, R = 0, L = 0;
	if (start->left != NULL)
		left = start->left->height + 1;
	if (start->right != NULL)
		right = start->right->height + 1;


	if (left - right > 1) {
		/*	R = getTreeHeight(start->left->right) + 1;
			L = getTreeHeight(start->left->left) + 1;*/
		if (start->left != NULL && start->left->left != NULL)
			L = start->left->left->height + 1;
		if (start->left != NULL && start->left->right != NULL)
			R = start->left->right->height + 1;

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
	}
	else if (left - right < -1) {
		if (start->right != NULL && start->right->left != NULL)
			L = start->right->left->height + 1;
		if (start->right != NULL && start->right->right != NULL)
			R = start->right->right->height + 1;

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
	else{
		start->height = left > right ? left : right;
	}

	
	return start;
}

NODE* rotateRightLeftBST(NODE* start) {
	NODE* oldTop = start->left;
	start->left = oldTop->right;
	oldTop->right = start->left->left;
	start->left->left = oldTop;

	start = rotateRightBST(start);

	return start;

}

NODE* rotateLeftRightBST(NODE* start) {
	NODE* oldTop = start->right;
	NODE* newTop = oldTop->left;
	start->right = newTop;
	oldTop->left = newTop->right;
	newTop->right = oldTop;

	start = rotateLeftBST(start);

	return start;

}


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



NODE* insertNode(NODE* node, int v) {

	if (node != NULL) {
		if (node->value < v){
			node->right = insertNode(node->right, v);
			node = balanceBST(node);
		
		}
		else if (node->value > v) {
			node->left = insertNode(node->left, v);
			node = balanceBST(node);
		} 
		else {
			//printf("Given value already exists\n");
			return node;
		}
	}
	else {
		node = malloc(sizeof(NODE));
		node->left = NULL;
		node->right = NULL;
		node->value = v;
		node->height = 0;
	}
	return node;
}



//TEMP 
int _print_t(NODE* tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 5;

	if (!tree) return 0;

	sprintf(b, "(%03d)", tree->value);

	int left = _print_t(tree->left, 1, offset, depth + 1, s);
	int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
	for (int i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	}
#else
	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
#endif

	return left + width + right;
}

void print_t(NODE* tree)
{
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_print_t(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}

