#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vector.h"

#ifndef MAXSIZE
#define MAXSIZE 20
#endif

typedef struct Vector{
    int maxsize;
    int size;
    void **array;
} Vector;

Vector* vectorGenerate(){
    Vector* newVector = (Vector*) malloc(sizeof(Vector));
    newVector->maxsize = MAXSIZE;
    newVector->size = 0;
    newVector->array = (void **) malloc(MAXSIZE*sizeof(void**));
    return newVector;
}

bool vectorPush(Vector *vec, void* value) { //push elements to the vector
	if (vec->size >= MAXSIZE - 1) {
        return true;
    }
    else{
        vec->array[vec->size] = value;
        vec->size++;
        return false;
    }
}

bool vectorPushBack(Vector* vec, void* value, int i){
    if(!vec->size){
        vectorPush(vec, value);
        return true;
    } else if(vec->size >= MAXSIZE - 1)
        return false;
    else if(i < MAXSIZE - 1){
        vec->array[MAXSIZE - 1 - i] = value;
        return true;
    }
}

void* vectorPop(Vector *vec) {
    void* x;
    if (vec->size == 0) {
        //printf("Vector is empty!\n");
    }

    x = vec->array[vec->size - 1];
    vec->size--;
    return x;
}

void* vectorPeek(Vector *vec){
  if (vec->size == 0) {
      //printf("Vector is empty!\n");
  }

  return vec->array[vec->size - 1];
}


bool vectorInsert(Vector* vec, int index, void* x){
    int i = 0;
    if(index > vec->size || vec->size == MAXSIZE)
        return false;
    while(vec->size - i != index){
        vec->array[vec->size - i] = vec->array[vec->size - i - 1];
        i++;
    }
    vec->array[index] = x;
    vec->size++;
    return true;
}

void* vectorExtract(Vector* vec, int index){
    void* x;
    int i = 0;
    int s = vec->size;
    if(!vec->size || vec->size < index)
        return NULL;
    if(vec->size == index)
        return vectorPop(vec);
    x = vec->array[index];
    vec->size--;

    while(index + i != s){
        vec->array[index + i] = vec->array[index + i + 1];
        i++;
    }

    return x;
}

void* vectorGet(Vector* vec, int index){
    void* x;
    if(index > vec->size - 1)
        return NULL;
    x = vec->array[index];
    return x;
}

void vectorPrint(Vector *vec) {
    int i;
    int len = vec->size;
    
    for (i = 0; i < len; i++) {
        printf("%c", (vec->array[i]));
    }
    printf("\n");
}

void vectorClear(Vector* vec){
    if(vec->array)
        free(vec->array);

    free(vec);
}
