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

int main() {

	NODE* start = NULL;
	int r;
	for (int i = 0; i < 40; i++) {
		r = rand() % 90 + 1;
		start = insertNode(start, r);
		start = balanceBST(start);
		print_t(start);
	}

	/*for (int i = 1; i < 20; i+=2) {
		start = insertNode(start, i);
		start = balanceBST(start);
		print_t(start);
	}*/

//	print_t(start);
	//printf("%d\n",getTreeHeight(start));
	//start = rotateLeftBST(start);

	//start = rotateRightBST(start);
	

	print_t(start);
	return 0;
}

int getTreeHeight(NODE* node) {
	if (node != NULL) {
		int left = getTreeHeight(node->left);
		int right = getTreeHeight(node->right);
		return (node->height = 1 + ((left > right) ? left : right));
	}
	return -1;
}

NODE* balanceBST(NODE* start) {
	int left = getTreeHeight(start->left);
	int right = getTreeHeight(start->right);

	int i, L,R;

	if (left - right > 1) {
		R = (start->left->right == NULL) ? 0 : start->left->right->height;
		L = (start->left->left == NULL) ? 0 : start->left->left->height;
		if (L - R >= 0 ) {
			for (i = 0; i < (left - right - 1); i++) {
				start = rotateRightBST(start);
			}
		}
		else {
			for (i = 0; i < (left - right - 1); i++) {
				start = rotateRightLeftBST(start);
			}
		}
	}

	if (left - right < -1) {
		R = (start->right->right == NULL) ? 0 : start->right->right->height;
		L = (start->right->left == NULL) ? 0 : start->right->left->height;
		if (L - R >= 0) {
			for (i = 0; i < right - left - 1; i++) {
				start = rotateLeftRightBST(start);
			}
		}
		else {
			for (i = 0; i < right - left - 1; i++) {
				start = rotateLeftBST(start);
			}
		}
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
	start->right = oldTop->left;
	oldTop->left = start->right->right;
	start->right->right = oldTop;

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
		if (node->value < v)
			node->right = insertNode(node->right, v);
		else if (node->value > v)
			node->left = insertNode(node->left, v);
		else {
			printf("Given value already exists\n");
			return node;
		}
	}
	else {
		node = malloc(sizeof(NODE));
		node->left = NULL;
		node->right = NULL;
		node->value = v;
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

