
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "list.h"
#include "vector.h"


typedef struct Stack { //составляем библиотеку stack из библиотек vector и list   
	#ifdef USE_LIST
		List* listContainer;
	#else
		Vector* vectorContainer;
	#endif
} Stack;

Stack* StackGeneration(){
	Stack* newStack = (Stack*) malloc(sizeof(Stack));
	#ifdef USE_LIST
		newStack->listContainer = listCreation();
	#else
		newStack->vectorContainer = vectorGenerate();
	#endif
		return newStack;
}


void print(Stack* container){
	#ifdef USE_LIST
		printList(container->listContainer);
	#else 
		vectorPrint(container->vectorContainer);
	#endif
}


void* pop(Stack* container){ 
	#ifdef USE_LIST
		return listPop(container->listContainer);
	#else
		return vectorPop(container->vectorContainer);
	#endif
}


bool push(Stack* container, void* value){
	#ifdef USE_LIST
		listPush(container->listContainer, value);
		return false;
	#else
		return vectorPush(container->vectorContainer, value);
	#endif
}


void delete(Stack* container){
	#ifdef USE_LIST
		deleteList(container->listContainer);
	#else
		vectorClear(container->vectorContainer);
	#endif
		free(container);
}

void* peek(Stack* container){
	#ifdef USE_LIST
		return listPeek(container->listContainer);
	#else
		return vectorPeek(container->vectorContainer);
	#endif
}