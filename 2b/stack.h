#pragma once

#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

Stack* StackGeneration();
void print(Stack* container);
void* pop(Stack* container);
bool push(Stack* container, void* value);
void delete(Stack* container);
void* peek(Stack* container);



#endif