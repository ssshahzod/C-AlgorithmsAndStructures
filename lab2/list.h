#ifndef list.h
#define list.h

typedef struct ListNode;
void push(ListNode **head, int value);
int pop(ListNode **head);
void printListStack(const ListNode* head);
size_t getSize(const ListNode *head);

#endif
