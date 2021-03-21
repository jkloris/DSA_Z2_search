#include <stdio.h>
#include <time.h>

typedef struct data {
	char fname[20];
	char lname[20];
	char code[10];
}DATA;

typedef struct node {
	struct node* next;
	struct node* prev;
	char fname[20];
	char lname[20];
	char key[10];

}NODE;



int getHash(NODE* node);
DATA* getData(DATA* data);

int main() {
	DATA* data = malloc(100001 * sizeof(DATA));
	data = getData(data);

	NODE* a = malloc(sizeof(NODE));
	strcpy(a->key, "ABC");
	getHash(a);
	return 0;
}

int getHash(NODE *node) {
	char* p = node->key;
	int k = 3;
	int sum = *p * k;
	p++;

	while (*p != NULL) {
		sum += *p;
		sum *= k;
		p++;

	}

	printf("%d\n", sum);
		
}

DATA* getData(DATA* data) {
	FILE* f = fopen("data.txt", "r");
	char* buff[20];
	int i = 0;
	while (fscanf(f, "%s", buff) > 0) {
		strcpy(data[i].fname, buff);
		fscanf(f, "%s", buff);
		strcpy(data[i].lname, buff);
		fscanf(f, "%s", buff);
		strcpy(data[i].code, buff);
		i++;
	}

	return data;

}
