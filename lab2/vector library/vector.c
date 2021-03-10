#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define SIZE 20

typedef struct Vector{
    char data[SIZE];
    int size;
} Vector;

void vectorpush(Vector *vec, char value) { //push elements to the vector
	if (vec->size >= SIZE) {
        printf("Vector is full!\n");
    }
    else{
        vec->data[vec->size] = value;
        vec->size++;
    }
}

char vectorpop(Vector *vec) {
    if (vec->size == 0) {
        printf("Vector is empty!\n");
        return 1;
    }
    vec->size--;
    return vec->data[vec->size];
}
 
void vectorprint(const Vector *vec) {
    int i;
    int len = vec->size - 1;
    printf("Vector %d > ", vec->size);
    for (i = 0; i < len; i++) {
        printf("%c", vec->data[i]);
        printf(" | ");
    }
    printf("\n");
}