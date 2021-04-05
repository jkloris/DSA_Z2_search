#include <stdio.h>
#include "AVLtree.h"
#include "RBtree.h"
#include "hash_prevzate.h"
#include "hashLinear.h"
#define DATASIZE 200000
#define TESTSIZE 100000
DATA* getData(DATA* data);
DATA* getDataShuffle(DATA* data);

int main() {
	DATA* data = malloc((DATASIZE + 1) * sizeof(DATA));
	data = getData(data);
	DATA* dataShuf = malloc((DATASIZE + 1) * sizeof(DATA));
	dataShuf = getDataShuffle(dataShuf);

	NODE* start = NULL;
	struct dictionary* dic = dic_new(0);

	int size = 11;
	int stored = 0;
	NODE_H* hashArray = hashInit(size);

	//start = testInsertNodes(start, TESTSIZE, data);
	//testInsertRB(TESTSIZE, data);
	//testInstertHashTable(dic, TESTSIZE, data);
	//hashArray = testInsertHashLinear(hashArray, TESTSIZE, &size, &stored, data);

	start = testInsertNodesDupl(start, TESTSIZE, data);
	testInsertRBDupl(TESTSIZE, data);
	testInstertHashTableDupl(dic, TESTSIZE, data);
	hashArray = testInsertHashLinearDupl(hashArray, TESTSIZE, &size, &stored ,data, DATASIZE);


	printf("\n");
	testSearchAVL(start, TESTSIZE, data); //hladanie  v poradi ako boli ukladane
	testSearchAVL(start, TESTSIZE, dataShuf);//hladane v inom nahodnom poradi
	testSearchAVLfromZero(start, TESTSIZE); //hladanie podla hodnot od 0 po TESTSIZE
	testSearchRB(root, TESTSIZE, data);
	testSearchRB(root, TESTSIZE, dataShuf);
	testSearchRBfromZero(root, TESTSIZE);
	testSearchHashTable(dic, TESTSIZE, data);
	testSearchHashTable(dic, TESTSIZE, dataShuf);
	testSearchHashLinear(hashArray, TESTSIZE, size, data);
	testSearchHashLinear(hashArray, TESTSIZE, size, dataShuf);



	return 0;
}

DATA* getData(DATA* data) {
	FILE* f = fopen("data.txt", "r");
	char* buff[20];
	int i = 0, num;
	while (fscanf(f, "%s", buff) > 0) {
		strcpy(data[i].fname, buff);
		fscanf(f, "%s", buff);
		strcpy(data[i].lname, buff);
		fscanf(f, "%s", buff);
		strcpy(data[i].code, buff);
		fscanf(f, "%d", &num);
		data[i].num = num;
		i++;
	}

	return data;

}

DATA* getDataShuffle(DATA* data) {
	FILE* f = fopen("dataShuffle.txt", "r");
	char* buff[20];
	int i = 0, num;
	while (fscanf(f, "%s", buff) > 0) {
		strcpy(data[i].fname, buff);
		fscanf(f, "%s", buff);
		strcpy(data[i].lname, buff);
		fscanf(f, "%s", buff);
		strcpy(data[i].code, buff);
		fscanf(f, "%d", &num);
		data[i].num = num;
		i++;
	}

	return data;

}