#ifndef INC_6_DEFINITIONS_H
#define INC_6_DEFINITIONS_H

#define STRSIZE 50

typedef struct Symbol{
    char sym;
    int freq;
    struct Symbol* next;
    struct Symbol* left, *right;
} Symbol;

typedef struct fSymbol{
    char sym;
    int left;
    int right;
}fSymbol;

typedef struct Code{
    char* code;
    int lenght;
} Code;


//menu functions
void printMenu(int m);
int choiceFunc(int max);
int intInput(char const* msg);
char* strInput(char const* msg);


//priority queue
Symbol* peek(Symbol* head);
Symbol* pop(Symbol** head);
void push(Symbol** head, Symbol* input);
void printQueue(Symbol* head);
void listPop(Symbol** head, char letter);
bool moreThan1Node(Symbol* que);

//
void encoding(FILE* input, FILE* output);
void arrayWrite(fSymbol* array[], int num, FILE* output);

//
Symbol* initSymbol(char letter);
Symbol** freqCount(char* str);
Symbol* enQueue(Symbol** list);
int treeMake(Symbol** queue);
void codesfromTree(Symbol* root, Code* letrs[256], char* code, int codeLenght);
int nodesInTree(Symbol* root);
void treeToArray(Symbol* root, fSymbol* arr[], int i);

#endif //INC_6_DEFINITIONS_H
