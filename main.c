#include <stdio.h>
#include "dataStruc.h"
#include "AVLtree.h"
#include "RBtree.h"
#include "hash_prevzate.h"
#include "hashLinear.h"


#define DATASIZE 200000
#define TESTSIZE 100000

int main() {
	//nacitanie testovacich udajov
	DATA* data = malloc((DATASIZE + 1) * sizeof(DATA));
	data = getData(data);
	DATA* dataShuf = malloc((DATASIZE + 1) * sizeof(DATA));
	dataShuf = getDataShuffle(dataShuf);

	NODE* start = NULL; //avl strom
	struct dictionary* dic = dic_new(0); //chaining hash

	//linear probing hash
	int size = 11;
	int stored = 0;
	NODE_H* hashArray = hashInit(size);


	/*TESTOVANIE*/

	//naplnenie zoznamov
	start = testInsertNodes(start, TESTSIZE, data);
	testInsertRB(TESTSIZE, data);
	testInstertHashTable(dic, TESTSIZE, data);
	hashArray = testInsertHashLinear(hashArray, TESTSIZE, &size, &stored, data);

	//duplikovane naplenenie stromov
	//start = testInsertNodesDupl(start, TESTSIZE, data);
	//testInsertRBDupl(TESTSIZE, data);
	//testInstertHashTableDupl(dic, TESTSIZE, data);
	//hashArray = testInsertHashLinearDupl(hashArray, TESTSIZE, &size, &stored ,data, DATASIZE);

	printf("\n");
	//hladanie v rovnakom poradi ako boli naplene 
	testSearchAVL(start, TESTSIZE, data);
	testSearchRB(root, TESTSIZE, data);
	testSearchHashTable(dic, TESTSIZE, data);
	testSearchHashLinear(hashArray, TESTSIZE, size, data);

	//hladanie podla klucov od 0 po TESTSIZE
	testSearchAVLfromZero(start, TESTSIZE); 
	testSearchRBfromZero(root, TESTSIZE);

	//hladanie v inom poradi a aj inych prvkov ake boli naplene
	testSearchAVL(start, TESTSIZE, dataShuf);
	testSearchRB(root, TESTSIZE, dataShuf);
	testSearchHashTable(dic, TESTSIZE, dataShuf);
	testSearchHashLinear(hashArray, TESTSIZE, size, dataShuf);
	
	
	return 0;
}