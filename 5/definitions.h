#ifndef FUNC_H
#define FUNC_H

#define STRSIZE 20
#define QSIZE 20

typedef struct Node{
    char* name;
    float xcord;
    float ycord;
    float nodeWeight;
    struct Node *next;
    struct Node *nextbelow;
} Node;

typedef struct Queue{
    int head, tail;
    int numofelem, size;
    Node** array;
} Queue;

typedef struct List{
    char* str;
    struct List *next;

} List;


//general
int intchoice(int max);
char* strInput(const char* msg);
float floatInput(const char* msg);
void printMenu(int mode);

//queue functions
Queue* createQueue(int size);
Node* pop(Queue* que);
Node* peek(Node* head);
void push(Queue* que, Node* input);
int isEmpty(Queue* que);
void printQueue(Queue* que);
//List functions
void listPush(List** head, char* info);
void printpathList(List* path);

//graph functions
Node* readfromFile(FILE* input);
void saveToFile(Node* graph, FILE* output);

//vertix functions
Node* createNode();
Node* graphInput(Node* graph, Node* input);
void freeNode(Node* input);
void deleteinRow(Node* graph, Queue* que, char* name);
int deleteVertix(Node* graph, char* name);


//edges functions
int createEdges(Node* graph, char* name1, char* name2);
void casecreateEdges(Node* graph, int m);

int deleteEdge(Node* graph, char* name1, char* name2);

//search functions
List* bfs(Node* graph, char* namesearchfor, char* namesearchby);


void printLists(Node* graph);
void printDot(Node* graph, FILE* output);
#endif