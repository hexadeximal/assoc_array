#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct array {
	char *key;
	char *value;
	int index;
	int size;
};

static void init_array(struct array ***arr, const int size)
{
	

	(*arr) = calloc(size, sizeof(struct array *));

	if((*arr) == NULL) {
		fprintf(stderr, "error alloc\n");
		exit(-1);
	}

	for(int i = 0; i < size; i++) {
		(*arr)[i] = calloc(1, sizeof(struct array));
		(*arr)[i]->size = size;
		(*arr)[i]->key = NULL;
		(*arr)[i]->index = i;
	}
}

static void array_add(struct array ***arr, const char *key, const char *value)
{
	int empty_index = 0;
	int set = 0;
	size_t key_len = 0;
	size_t val_len = 0;


	for(int i = 0; i <	(*arr)[0]->size; i++) {
		if((*arr)[i]->key == NULL) {
			empty_index = i;
			set = 1;
			break;
		}
	}

	/* no empty slots in array found, realloc */
	if(set == 0) {
		int old_index = (*arr)[0]->size;
		int nsize = (*arr)[0]->size * 2;
		(*arr) = realloc((*arr), nsize * sizeof(struct array *));

		if((*arr) == NULL) {
			fprintf(stderr, "error alloc\n");
		}

		/* set new empty_index to old_index + 1 */
		empty_index = nsize - old_index;

		/* alloc and set index on array from old_index */
		for(int i = old_index; i < nsize; i++) {
			(*arr)[i] = calloc(1, sizeof(struct array));
			(*arr)[i]->key = NULL;
			(*arr)[i]->index = i;
		}

		/* reset size on all elements */
		for(int i = 0; i < nsize; i++) {
			(*arr)[i]->size = nsize;
		}	
	}

	key_len = snprintf(NULL, 0, "%s", key) + 1;
	val_len = snprintf(NULL, 0, "%s", value) + 1;


	(*arr)[empty_index]->key = calloc(key_len, sizeof(char));
	(*arr)[empty_index]->value = calloc(val_len, sizeof(char));

	if((*arr)[empty_index]->key == NULL || (*arr)[empty_index]->value == NULL) {
		fprintf(stderr, "error alloc\n");
		exit(-1);
	}


	snprintf((*arr)[empty_index]->key, key_len, "%s", key);
	snprintf((*arr)[empty_index]->value, val_len, "%s", value);
}

static char *array_get(struct array **arr, const char *key)
{
	for(int i = 0; i < arr[0]->size; i++) {

		if(arr[i]->key != NULL && strcmp(key, arr[i]->key) == 0) {
			printf("key: %s\nvalue: %s\nindex: %d\n",arr[i]->key, arr[i]->value, arr[i]->index); 
		}
	}

	return NULL;
}


static void array_free(struct array ***arr) 
{
	int size = (*arr)[0]->size;

	for(int i = 0; i < size; i++) {
		free((*arr)[i]->key);
		free((*arr)[i]->value);
		free((*arr)[i]);
	}

	free((*arr));
}

int main(void)
{
	struct array **arr;

	init_array(&arr, 10);

	array_add(&arr, "_key1", "value1");
	array_add(&arr, "_key2", "value2");
	array_add(&arr, "_key3", "value3");
	array_add(&arr, "_key4", "value4");
	array_add(&arr, "_key5", "value5");
	array_add(&arr, "_key6", "value6");
	array_add(&arr, "_key7", "value7");
	array_add(&arr, "_key8", "value8");
	array_add(&arr, "_key9", "value9");
	array_add(&arr, "_key10", "value10");
	array_add(&arr, "_key11", "value2");
	array_add(&arr, "test", "str");
	array_add(&arr, "123", "num");
	array_add(&arr, "%%45", "spc");
	array_add(&arr, "_)(()(", "spc2");

	array_get(arr, "_key1");
	array_get(arr, "_key2");
	array_get(arr, "_key3");
	array_get(arr, "_key4");
	array_get(arr, "_key5");
	array_get(arr, "_key6");
	array_get(arr, "_key7");
	array_get(arr, "_key8");
	array_get(arr, "_key9");
	array_get(arr, "_key10");
	array_get(arr, "_key11");

	array_get(arr, "test");
	array_get(arr, "123");
	array_get(arr, "%%45");
	array_get(arr, "_)(()(");
	array_free(&arr);
	return 0;
}
