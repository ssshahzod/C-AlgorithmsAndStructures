#pragma once

#ifndef LIST_H
#define LIST_H

typedef struct ListNode ListNode;
typedef struct List List;

List* listCreation();
void listPush(List* inputList, void* data);
void deleteList(List* head);
void printList(List* inputList);
ListNode* listGetNode(List* input, int index);
void* listGet(List* input, int index);
void listClearNode(ListNode* node);
void listInsert(List* input, int index, void* data);
void* listPop(List *head);
void* listPeek(List* inputList);


#endif
