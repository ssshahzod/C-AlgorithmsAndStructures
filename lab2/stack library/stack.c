#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "../list library/list.h"
#include "../vector library/vector.h"


typedef struct st_container{  //составляем библиотеку stack из библиотек vector и list   
	#ifdef USE_LIST
		ListNode *List;
	#else
		Vector *vector;
	#endif	
} st_container;

void printStack(const st_container *stack){
	#ifdef USE_LIST
		void printList(const ListNode *stack);
	#else 
		void vectorprint(const Vector *stack);
	#endif
}


char stackpop(st_container *stack){ 
	#ifdef USE_LIST
		void listpop(ListNode **stack);
	#else
		char vectorpop(Vector *stack);
	#endif
}


void stackpush(st_container *stack, char value){
	#ifdef USE_LIST
		void listpush(ListNode *stack, char value);
	#else
		void vectorpush(Vector *stack, char value);
	#endif
}


