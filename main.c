#include <stdio.h>
#include "AVLtree.h"
#include "RBtree.h"
#include "hash_prevzate.h"
#include "hashLinear.h"

DATA* getData(DATA* data);

int main() {
	DATA* data = malloc(100001 * sizeof(DATA));
	data = getData(data);

	NODE* start = NULL;
	struct dictionary* dic = dic_new(0);
	int size = 10000;
	NODE_H* hashArray = hashInit(size);

	testInsertNodes(start, 100000, data);
	testInsertRB(100000, data);
	testInstertHashTable(dic, 100000, data);
	testInsertHashLinear(hashArray, 100000, &size, data);
	printf("\n");
	testSearchRB(root, 100000);
	testSearchAVL(start, 100000);
	testSearchHashTable(dic, 100000, data);
	testSearchHashLinear(hashArray, 100000, size, data);


	return 0;
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