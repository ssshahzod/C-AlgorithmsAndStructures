//Linked list and functions for it

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h" 

typedef struct ListNode {
    char value;
    struct ListNode *next;
} ListNode;

void main() {
    printf("Okay\n");

}


ListNode* getLast(ListNode *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}


ListNode* getLastNode(ListNode *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void listPush(ListNode **head, char value) { //pushing new element into the list
    ListNode *last = getLastNode(*head);
    ListNode *tmp = (ListNode*) malloc(sizeof(ListNode));
    tmp->value = value;
    tmp->next = NULL;
    last->next = tmp;
}

void deleteList(ListNode **head) {
    ListNode* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

void printList(const ListNode *head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void listPop(ListNode **head) {
    ListNode *pFwd = NULL;  //this node
    ListNode *pBwd = NULL;  //next node
    if ((!head) || !(*head)) { //list is empty
        exit(-1);
    }     
    pFwd = *head; 
    while (pFwd->next) { 
        pBwd = pFwd;
        pFwd = pFwd->next;
    }
 
    if (pBwd == NULL) {
        free(*head);
        *head = NULL;
    } else {
        free(pFwd->next);
        pBwd->next = NULL;
    }
}



