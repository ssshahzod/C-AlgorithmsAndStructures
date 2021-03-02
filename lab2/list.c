#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h" 

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
 
typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

void main() {
    int i;
    ListNode *head = NULL;
    for (i = 0; i < 10; i++) {
        push(&head, i);
    }
    printf("size = %d\n", getSize(head));
    while (head) {
        printf("%d ", pop(&head));
    }
}

void push(ListNode **head, int value) { //pushing new element into the stack
    ListNode *tmp = malloc(sizeof(ListNode));
	if (tmp == NULL) { //stack is full
        exit(STACK_OVERFLOW);
    }
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}

//test with void* 
int pop(ListNode **head) {  
    ListNode *out;
    int value;
    if (*head == NULL)  //stack is empty
        exit(STACK_UNDERFLOW);
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

void printListStack(const ListNode* head) {
    printf("stack: ");
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
}

int getSize(const ListNode *head) {
    int size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

