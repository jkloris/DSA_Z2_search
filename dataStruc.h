#ifndef DATASTRUC
#define DATASTRUC

#include <stdio.h>
#include <string.h>

typedef struct data {
	char fname[20];
	char lname[20];
	char code[10];
	int num;
}DATA;


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

#endif // !DATASTRUC

