#ifndef VECTOR_H
#define VECTOR_H


typedef struct Vector Vector;

void vectorpush(Vector *vec, char value);
char vectorpop(Vector *vec);
void vectorprint(const Vector *vec);

#endif