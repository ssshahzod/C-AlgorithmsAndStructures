#ifndef STACK_H
#define STACK_H

typedef struct st_container st_container;

void printStack(const st_container *stack);
char stackpop(st_container *stack);
void stackpush(st_container *stack, char value);




#endif