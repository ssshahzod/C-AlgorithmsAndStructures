#pragma once

#include <stdbool.h>

#ifndef VECTOR_H
#define VECTOR_H


typedef struct Vector Vector;

Vector* vectorGenerate();
bool vectorPush(Vector *vec, void* value);//
bool vectorPushBack(Vector* vec, void* value, int i);//
bool vectorInsert(Vector* vec, int index, void* x);//
void* vectorExtract(Vector* vec, int index);//
void* vectorPop(Vector *vec);//
void* vectorPeek(Vector *vec);
void vectorPrint(Vector *vec);//
void* vectorGet(Vector* vec, int index);//
void vectorClear(Vector* vec);//

#endif