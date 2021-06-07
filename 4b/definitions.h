#ifndef FUNC_H
#define FUNC_H

#define STRSIZE 20

typedef struct Rstr{
    char* str1;
    char* str2;
    int release;
    struct Rstr *next;
} Rstr;

typedef struct HNode{
	int num;
	int nodeToreplace;
	int key;
	Rstr *data;
	struct HNode *next;
} HNode;

typedef struct Node{
    int key;
    int height;
    struct Node* leftnode;
    struct Node* rightnode;
    Rstr *data;
} Node;

/// general functions
int intInput(const char* msg);
char* strInput(const char* msg);
int intchoice(int max);

/// tree functions
int TreeTiming(Node**);

Node* NodeInit(int m);


int getHeight(Node* input);
void fixHeight(Node* input);
int heightDif(Node* input);

//file functions
int fileInput(FILE *input, Node** root, HNode* buf[], int bufSize);

Node* insert(Node** head, Node* input);
Node* rotateRight(Node* input);
Node* rotateLeft(Node* input);
Node* treeBalance(Node* tree);

Rstr* search(Node* root, int tkey, int rel);
void caseSearch(Node* root, HNode* buf[]);
Rstr* searchMin(Node* root, int release);
void caseSearchMin(Node* root);

Node* deleteNode(Node* root, int key);
Node* caseDelete(Node* root);

//tree print
void printNull(int key, int nullNumber, FILE* file);
void printNode(Node* input);
void printAux(Node* node, FILE* file);
void printDot(Node* tree, FILE* file);
void printData(Rstr* res);


void treeFree(Node* root);

// menu functions
void printMenu(int mode);


//buf functions
void freeBuf(HNode* buf[], int bufSize);
void freeHNode(HNode *input);
void bufInit(HNode* buf[], int bufSize);
int bufInput(HNode* buf[], Node* input, int bufsize);
int hashFunc(int key);


#endif