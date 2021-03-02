#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
    char value;
    struct ListNode *next;
} ListNode;

void push(ListNode **head, int value);
int pop(ListNode **head);
void printListStack(const ListNode* head);
int getSize(const ListNode *head);

#endif
