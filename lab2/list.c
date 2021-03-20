//Linked list and functions for it

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct ListNode {
    void* value;
    struct ListNode *next;
} ListNode;

typedef struct List{
    int size;
    ListNode *head;
} List;


List* listCreation(){
    List* newList = (List *) malloc(sizeof(List));
    newList->size = 0;
    newList->head = NULL;
    return newList;
}


void listPush(List* inputList, void* data) {
    ListNode *tmp = (ListNode*) malloc(sizeof(ListNode));//creating new field
    tmp->value = data;
    tmp->next = inputList->head; //putting value, linking with last field in list

    inputList->head = tmp;
    inputList->size++;
}

void printList(List* inputList) {
    ListNode* Head = inputList->head;
    while (Head) { //while pointer isnt NULL its not last listnode
        printf("%c ", *((int *) Head->value));
        Head = Head->next;
    }
    printf("\n");
}

void* listPop(List *inputList) {
    void* x = NULL;
    ListNode *tn = NULL;  //this node
    ListNode *nn = NULL;  //next node

    if (inputList->size == 0) { //list is empty
        exit(-1);
    }

    nn = inputList->head;
    tn = nn;
    nn = nn->next;

    x = tn->value;
    inputList->head = nn;
    inputList->size--;
    free(tn);
    return x;
}

void* listPeek(List* inputList){
    void* x = NULL;
    ListNode *tn = NULL;  //this node
    ListNode *nn = NULL;  //next node

    if (inputList->size == 0) { //list is empty
        exit(-1);
    }

    tn = inputList->head;
    x = tn->value;
    return x;
}

ListNode* listGetNode(List* input, int index){
    if(index >= input->size)
        return NULL;
    ListNode* node = input->head;
    for(int i = 0; i < index; i++)
        node = node->next;

    return node;
}

void* listGet(List* input, int index){
    return listGetNode(input, index)->value;
}

void listClearNode(ListNode* node){
    free(node->value);
}

void listInsert(List* input, int index, void* data){
    if(index - 1 == input->size)
        listPush(input, data);

    if (!index){
        listPush(input, data);
    }

    ListNode* new = (ListNode*) malloc(sizeof(ListNode));
    new->value = data;

    ListNode* prev = listGetNode(input, index - 1);
    new->next = prev->next;
    prev->next = new;

    input->size++;
}

void deleteList(List* inputList) {
    ListNode* prev = inputList->head; //first node of the list
    ListNode* this = prev;
    while (prev->next) {
        this = prev;
        prev = prev->next;
        free(this);
    }
    free(prev);
    free(inputList);
}
