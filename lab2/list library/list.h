#ifndef LIST_H
#define LIST_H

typedef struct ListNode ListNode;

ListNode* getLast(ListNode *head);
ListNode* getLastNode(ListNode *head);
void listPush(ListNode **head, char data);
void deleteList(ListNode **head);
void printList(const ListNode *head);
void listPop(ListNode **head);


#endif
