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

	int size = 11;
	int stored = 0;
	NODE_H* hashArray = hashInit(size);
	hashArray = testInsertHashLinear(hashArray, 10000, &size, &stored, data);

	/*testInsertNodes(start, 1000, data);
	testInsertRB(1000, data);
	testInstertHashTable(dic, 1000, data);*/

	//hashSearch(hashArray, "aaaaa", size);
	printf("\n");
	/*testSearchRB(root, 100000);
	testSearchAVL(start, 100000);
	testSearchHashTable(dic, 100000, data);*/
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