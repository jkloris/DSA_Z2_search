#include <stdio.h>
#include <time.h>
#define nextIndexForm(i) ((i)+3)


typedef struct data {
	char fname[20];
	char lname[20];
	char code[10];
}DATA;

typedef struct node {
	char fname[20];
	char lname[20];
	char key[10];

}NODE;


int findIndex(NODE* hArray, int h_i, int size, char* key);
int getHash(char *key);
DATA* getData(DATA* data);
NODE* hashInit(int initSize);
NODE* hashInsert(NODE* hashArray, char* key, char* fname, char* lname, int* size);
NODE* rehash(NODE* hashArray, int* size);

int main() {
	DATA* data = malloc(100001 * sizeof(DATA));
	data = getData(data);

	int size = 10;
	NODE* hashArray = hashInit(size);

	for (int i = 0; i < 10; i++) {

		hashArray = hashInsert(hashArray, data[i].code, data[i].fname, data[i].lname, &size);
	}

	for (int i = 10; i < 100; i++) {
		hashArray = hashInsert(hashArray, data[i].code, data[i].fname, data[i].lname, &size);
	}

	hashInsert(hashArray, "DSD78dds", "LALA", "NANA", &size);
	hashInsert(hashArray, "DSD789ds", "LALA2", "NANA", &size);
	hashInsert(hashArray, "ESD78dds", "LALA3", "NANA", &size);


	return 0;
}

NODE* hashInsert(NODE * hashArray, char* key, char* fname, char* lname, int *size) {

	int h_i = getHash(key) % *size;
	int buf = h_i;
	
	if (!strcmp(hashArray[h_i].key, "")) {
		strcpy(hashArray[h_i].key, key);
		strcpy(hashArray[h_i].fname, fname);
		strcpy(hashArray[h_i].lname, lname);
		//printf("---%d\n", h_i);
		return hashArray;
	}

	while ((h_i = findIndex(hashArray, h_i, *size, key)) == -1) {
		hashArray = rehash(hashArray, size);
		h_i = getHash(key) % *size;
	}

	if (!strcmp(hashArray[h_i].key, key))
		return hashArray;
	
	strcpy(hashArray[h_i].key, key);
	strcpy(hashArray[h_i].fname, fname);
	strcpy(hashArray[h_i].lname, lname);
	//printf("---%d\n", h_i);

	return hashArray;
}

NODE* rehash(NODE* hashArray, int* size) {
	int i, h_i;
	*size *= 2;
	NODE* buf = calloc(*size, sizeof(NODE));

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

int findIndex(NODE* hArray, int h_i, int size, char* key) {
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



NODE* hashInit( int initSize) {
	NODE* start = calloc(initSize, sizeof(NODE));

	//memset(start, '\0', initSize * sizeof(NODE));
	
	return start;
}

int getHash(char *key) {
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
