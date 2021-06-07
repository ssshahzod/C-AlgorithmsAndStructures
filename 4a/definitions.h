#ifndef FUNC_H
#define FUNC_H

#define STRSIZE 20

typedef struct Node{
    char* data;
    char* key;
    int same;
    struct Node* left;
    struct Node* right;

} Node;

Node* nodeInit(char* info, char* Key);
char* input();
int intinput(int max);
void printMenu(int mode);
void printNode(Node* input);
int nodeInput(Node** head, Node* ins);
Node* caseNodeInit();
int deleteNode(Node* root, char* dkey);
unsigned int hashStr(char* str);
Node* search(Node* root, char* key);
void printTree(Node *root, char *part, int level);
void printNull(char* key, int nullNumber, FILE* file);
void printAux(Node* node, FILE* file);
void printDot(Node* tree, FILE* file);
void clearNode(Node* node);
void treeFree(Node* root);
void treeWordFree(Node* root);
int inputWords(Node** root);
void outputWords(Node* root);


#endif
