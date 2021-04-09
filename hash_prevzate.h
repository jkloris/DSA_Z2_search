#ifndef HASH_PREVZATE
#define HASH_PREVZATE

//#include <sys/time.h>
//prevzate z https://github.com/exebook/hashdict.c 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashdict.h"
#define hash_func meiyan


static inline uint32_t meiyan(const char* key, int count) {
	typedef uint32_t* P;
	uint32_t h = 0x811c9dc5;
	while (count >= 8) {
		h = (h ^ ((((*(P)key) << 5) | ((*(P)key) >> 27)) ^ *(P)(key + 4))) * 0xad3e7;
		count -= 8;
		key += 8;
	}
#define tmp h = (h ^ *(uint16_t*)key) * 0xad3e7; key += 2;
	if (count & 4) { tmp tmp }
	if (count & 2) { tmp }
	if (count & 1) { h = (h ^ *key) * 0xad3e7; }
#undef tmp
	return h ^ (h >> 16);
}

struct keynode* keynode_new(char* k, int l) {
	struct keynode* node = malloc(sizeof(struct keynode));
	node->len = l;
	node->key = malloc(l);
	memcpy(node->key, k, l);
	node->next = 0;
	node->value = -1;
	return node;
}

void keynode_delete(struct keynode* node) {
	free(node->key);
	if (node->next) keynode_delete(node->next);
	free(node);
}

struct dictionary* dic_new(int initial_size) {
	struct dictionary* dic = malloc(sizeof(struct dictionary));
	if (initial_size == 0) initial_size = 1024;
	dic->length = initial_size;
	dic->count = 0;
	dic->table = calloc(sizeof(struct keynode*), initial_size);
	dic->growth_treshold = 2.0;
	dic->growth_factor = 10;
	return dic;
}

void dic_delete(struct dictionary* dic) {
	for (int i = 0; i < dic->length; i++) {
		if (dic->table[i])
			keynode_delete(dic->table[i]);
	}
	free(dic->table);
	dic->table = 0;
	free(dic);
}

void dic_reinsert_when_resizing(struct dictionary* dic, struct keynode* k2) {
	int n = hash_func(k2->key, k2->len) % dic->length;
	if (dic->table[n] == 0) {
		dic->table[n] = k2;
		dic->value = &dic->table[n]->value;
		dic->lastname = &dic->table[n]->lastname; //moje
		return;
	}
	struct keynode* k = dic->table[n];
	k2->next = k;
	dic->table[n] = k2;
	dic->value = &k2->value;
	dic->lastname = &k2->lastname; //moje
}

void dic_resize(struct dictionary* dic, int newsize) {
	int o = dic->length;
	struct keynode** old = dic->table;
	dic->table = calloc(sizeof(struct keynode*), newsize);
	dic->length = newsize;
	for (int i = 0; i < o; i++) {
		struct keynode* k = old[i];
		while (k) {
			struct keynode* next = k->next;
			k->next = 0;
			dic_reinsert_when_resizing(dic, k);
			k = next;
		}
	}
	free(old);
}

int dic_add(struct dictionary* dic, void* key, int keyn) {
	int n = hash_func((const char*)key, keyn) % dic->length;
	if (dic->table[n] == 0) {
		double f = (double)dic->count / (double)dic->length;
		if (f > dic->growth_treshold) {
			dic_resize(dic, dic->length * dic->growth_factor);
			return dic_add(dic, key, keyn);
		}
		dic->table[n] = keynode_new((char*)key, keyn);
		dic->value = &dic->table[n]->value;
		dic->lastname = &dic->table[n]->lastname; //moje
		dic->count++;
		return 0;
	}
	struct keynode* k = dic->table[n];
	while (k) {
		if (k->len == keyn && memcmp(k->key, key, keyn) == 0) {
			dic->value = &k->value;
			dic->lastname = &k->lastname;//moje
			return 1;
		}
		k = k->next;
	}
	dic->count++;
	struct keynode* k2 = keynode_new((char*)key, keyn);
	k2->next = dic->table[n];
	dic->table[n] = k2;
	dic->value = &k2->value;
	dic->lastname = &k2->lastname;//moje
	return 0;
}

int dic_find(struct dictionary* dic, void* key, int keyn) {
	int n = hash_func((const char*)key, keyn) % dic->length;
#if defined(__MINGW32__) || defined(__MINGW64__)
	__builtin_prefetch(gc->table[n]);
#endif

	//#if defined(_WIN32) || defined(_WIN64)			//s tym to neslo
	//	_mm_prefetch((char*)gc->table[n], _MM_HINT_T0);
	//#endif
	struct keynode* k = dic->table[n];
	if (!k) return 0;
	while (k) {
		if (k->len == keyn && !memcmp(k->key, key, keyn)) {
			dic->value = &k->value;
			dic->lastname = &k->lastname;//moje
			return 1;
		}
		k = k->next;
	}
	return 0;
}

void dic_forEach(struct dictionary* dic, enumFunc f, void* user) {
	for (int i = 0; i < dic->length; i++) {
		if (dic->table[i] != 0) {
			struct keynode* k = dic->table[i];
			while (k) {
				if (!f(k->key, k->len, &k->value, user)) return;
				k = k->next;
			}
		}
	}
}



//moje
void testInstertHashTable(struct dictionary* dic, int count, DATA* data) {
	int i, r, ms;
	clock_t dt, now = clock();


	for (i = 0; i < count; i++) {
		dic_add(dic, data[i].code, 8);
		*dic->value = data[i].fname;
		*dic->lastname = data[i].lname;
	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Naplnenie hash tabulky %d prvkami trvalo %dms\n", count, ms );
}

//moje
void testInstertHashTableDupl(struct dictionary* dic, int count, DATA* data) {
	int i, r, ms;
	clock_t dt, now = clock();


	for (i = 0; i < count/2; i++) {
		dic_add(dic, data[i].code, 8);
		*dic->value = data[i].fname;
		*dic->lastname = data[i].lname;

		dic_add(dic, data[i].code, 8);
	}
	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Naplnenie hash tabulky %d(%d pokusov)prvkami trvalo %dms\n", count/2, count, ms);
}

//moje
void testSearchHashTable(struct dictionary* dic, int count, DATA* data) {
	int i, r, ms, found = 0;
	clock_t dt, now = clock();

	for (i = 0; i < count; i++) {
		
		if (dic_find(dic, data[i].code, 8)) {
		 //printf("%s found: %s %s\n", data[i].code, *dic->value, *dic->lastname);
			found++;
		}
	//else// printf("error\n");
	}

	dt = clock() - now;
	ms = dt * 1000 / CLOCKS_PER_SEC;
	printf("Hladanie v hash tabulke %d prvkov trvalo %dms.. nenaslo %d\n", count, ms, count - found);
}

//int main() {
//	//moje
//	DATA* data = malloc(100001 * sizeof(DATA));
//	data = getData(data);
//
//	struct dictionary* dic = dic_new(0);
//
//	testInstert(dic, 100000, data);
//
//	testInstert(dic, 100, data);
//
//	testSearch(dic, 100000, data);
//
//
//
//
//	dic_delete(dic);
//	return 0;
//}

#undef hash_func
#endif // !HASH_PREVZATE
