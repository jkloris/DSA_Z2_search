#ifndef HASHLINEAR
#define HASHLINEAR

#include <stdio.h>
#include <time.h>
#define nextIndexForm(i) ((i)+3)


typedef struct nodeh {
	char fname[20];
	char lname[20];
	char key[10];

}NODE_H;


int findIndex(NODE_H* hArray, int h_i, int size, char* key);
int getHash(char* key);
NODE_H* hashInit(int initSize);
NODE_H* hashInsert(NODE_H* hashArray, char* key, char* fname, char* lname, int* size);
NODE_H* rehash(NODE_H* hashArray, int* size);
NODE_H* testInsertHashLinear(NODE_H* hashArray, int count, int* size, DATA* data);
NODE_H hashSearch(NODE_H* hashArray, char* key, int size);
void testSearchHashLinear(NODE_H* hashArray, int count, int size, DATA* data);

//int main() {
//	DATA* data = malloc(100001 * sizeof(DATA));
//	data = getData(data);
//
//	int size = 10;
//	NODE_H* hashArray = hashInit(size);
//
//	/*for (int i = 0; i < 10; i++) {
//
//		hashArray = hashInsert(hashArray, data[i].code, data[i].fname, data[i].lname, &size);
//	}
//
//	for (int i = 10; i < 90000; i++) {
//		hashArray = hashInsert(hashArray, data[i].code, data[i].fname, data[i].lname, &size);
//	}*/
//
//	hashArray = testInsert(hashArray, 90000, &size, data);
//
//	testSearch(hashArray, 90000, size, data);
//
//	return 0;
//}

void testSearchHashLinear(NODE_H* hashArray, int count, int size, DATA* data) {
	int ms, counter = 0;
	clock_t dt, now = clock();
	NODE_H a;

	for (int i = 0; i < count; i++) {
		a = hashSearch(hashArray, data[i].code, size);
		if (!strcmp(a.key, ""))
			counter++;
	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;


	printf("Hladanie pomocou linearneho hashingu trvalo %d.%ds ...%d\n", ms / 1000, ms % 1000, counter);
}

NODE_H hashSearch(NODE_H* hashArray, char* key, int size) {
	int h_i = getHash(key) % size;
	int buf = h_i, f = 1;

	while (strcmp(hashArray[h_i].key, key) && (buf != h_i || f) && strcmp(hashArray[h_i].key,"")) {
		h_i = (nextIndexForm(h_i) % size);
		f = 0;
	}
	if ((buf == h_i && !f) || (!strcmp(hashArray[h_i].key, ""))) {
		NODE_H a;
		strcpy(a.key, "");
		//printf("nenasiel sa\n");
		return a;
	}

	return hashArray[h_i];
}

NODE_H* testInsertHashLinear(NODE_H* hashArray, int count, int* size, int* stored, DATA* data) {
	int i, r, ms;
	clock_t dt, now = clock();

	for (i = 0; i < count; i++) {
		//r = rand() % 100000;
		hashArray = hashInsert(hashArray, data[i].code, data[i].fname, data[i].lname, size, stored);

	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Naplnenie linearnej hash tabulky %d prvkami trvalo %d.%ds\n", count, ms / 1000, ms % 1000);

	return hashArray;
}

NODE_H* hashInsert(NODE_H* hashArray, char* key, char* fname, char* lname, int* size, int *stored) {
	//printf("%f\n", ((float)(*stored) + 1) / (*size));
	if ( ( ((float)(*stored)+1) / *size) > 0.5) {
		hashArray = rehash(hashArray, size);
	}

	int h_i = getHash(key) % *size;
	int buf = h_i;

	if (!strcmp(hashArray[h_i].key, "")) {
		strcpy(hashArray[h_i].key, key);
		strcpy(hashArray[h_i].fname, fname);
		strcpy(hashArray[h_i].lname, lname);
		//printf("---%d\n", h_i);
		(*stored)++;
		return hashArray;
	}

	while ((h_i = findIndex(hashArray, h_i, *size, key)) == -1) {
		//hashArray = rehash(hashArray, size);
		//h_i = getHash(key) % *size;
		printf("rehash.,\n");
	}

	if (!strcmp(hashArray[h_i].key, key)) {
		printf("uz je");
		return hashArray;
	}

	strcpy(hashArray[h_i].key, key);
	strcpy(hashArray[h_i].fname, fname);
	strcpy(hashArray[h_i].lname, lname);
	(*stored)++;
	//printf("---%d\n", h_i);

	return hashArray;
}

NODE_H* rehash(NODE_H* hashArray, int* size) {
	int i, h_i;
	*size *= 2;
	NODE_H* buf = calloc(*size, sizeof(NODE_H));

	for (i = 0; i < *size / 2; i++) {
		if (!strcmp(hashArray[i].key, ""))
			continue;

		h_i = getHash(hashArray[i].key) % *size;

		while (strcmp(buf[h_i].key, "")) {
			h_i = findIndex(buf, h_i, *size, ".");
			if (h_i == -1)
				break;
		}

		buf[h_i] = hashArray[i];
	}

	free(hashArray);

	return buf;
}

int findIndex(NODE_H* hArray, int h_i, int size, char* key) {
	int buf = h_i;

	do {
		h_i = (nextIndexForm(h_i) % size);

		//printf("%s\n", hArray[h_i].key);
	} while (strcmp(hArray[h_i].key, "") && h_i != buf && strcmp(hArray[h_i].key, key));

	//if (!strcmp(hArray[h_i].key, hArray[buf].key)) { //ZLE TODO
	//	return -2;
	//}

	if (h_i == buf) {
		return -1;
	}
	return h_i;
}



NODE_H* hashInit(int initSize) {
	NODE_H* start = calloc(initSize, sizeof(NODE_H));

	//memset(start, '\0', initSize * sizeof(NODE_H));

	return start;
}

int getHash(char* key) {
	char* p = key;
	int k = 3;
	int sum = *p * k;
	p++;

	while (*p != NULL) {
		sum += *p;
		sum *= k;
		p++;

	}

	//printf("%d\n", sum);
	return sum;
}




#endif