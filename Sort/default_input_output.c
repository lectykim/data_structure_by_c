#include "default_input_output.h"



void re_create_data(int* ptr, int size) {
	printf("Before : ");
	for (int i = 0; i < size; i++) {
		*(ptr + i) = (rand() % size);
	}
	for (int i = 0; i < size; i++) {
		printf("%d ", *(ptr + i));
	}
	printf("\n");
}

void after_print_data(int* ptr, int size) {
	printf("After : ");
	for (int i = 0; i < size; i++) {
		printf("%d ", *(ptr + i));
	}
	printf("\n");
}
