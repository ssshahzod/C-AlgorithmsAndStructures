#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "definitions.h"

Node* NodeInit(int m){
    Node* tmp = NULL;
    tmp = (Node*) malloc(sizeof(Node));
    tmp->data = (Rstr*)malloc(sizeof (Rstr));
    if(m == 1) {
        tmp->key = intInput("Input integer key: ");
        tmp->data->str1 = strInput("Input first string: ");
        tmp->data->str2 = strInput("Input second string: ");
    }
    else {
        tmp->data->str1 = (char *) malloc(sizeof(char) * STRSIZE);
        tmp->data->str2 = (char *) malloc(sizeof(char) * STRSIZE);
    }
    if(!(tmp) || !(tmp->data) || !(tmp->data->str1) || !(tmp->data->str2)){
        return NULL;
    }
    tmp->height = 1;
    tmp->data->release = 1;
    tmp->data->next = NULL;
    tmp->leftnode = NULL;
    tmp->rightnode = NULL;
    return tmp;
}

HNode* HNodeInit(Node* input){
    HNode* tmp = (HNode*)malloc(sizeof(HNode));
    if(tmp == NULL)
        return NULL;
    tmp->key = input->key;
    tmp->data = input->data;
    tmp->num = 1;
    tmp->nodeToreplace = 1;
    tmp->next = NULL;
    return tmp;
}

int hashFunc(int key){
    return key % 10; 
}

void bufInit(HNode* buf[], int bufSize){
    for(int i = 0; i < bufSize; i++){
        buf[i] = NULL;
    }
}

int bufInput(HNode* buf[], Node* input, int bufsize){
    int numofnodes = bufsize / 10;
    HNode* result = HNodeInit(input);

    if(!result)
        return -1; //memory allocation error
    
    int hashkey = hashFunc(input->key);
    HNode* tmp = buf[hashkey];
    if(buf[hashkey] == NULL){
        buf[hashkey] = result;
        return 1;
    }
    //if there is elem and its not full
    else if(buf[hashkey]->num < numofnodes){
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = result;
        buf[hashkey]->num++;
        return 1;
    }
    //if this line is full
    else{
        if(tmp->nodeToreplace == 1) {
            result->next = tmp->next;
            result->num = tmp->num;
            result->nodeToreplace = 2;
            buf[hashkey] = result;
            freeHNode(tmp);
            return 1;
        }
        else if(tmp->nodeToreplace == 2){
            tmp = tmp->next;
            result->next = tmp->next;
            result->num = tmp->num;
            result->nodeToreplace = 3;
            buf[hashkey]->next = result;
            freeHNode(tmp);
            return 1;
        }
        else{
            tmp = tmp->next->next;
            result->next = NULL;
            result->num = tmp->num;
            result->nodeToreplace = 1;
            buf[hashkey]->next->next = result;
            freeHNode(tmp);
            return 1;
        }
    }
}

void freeBuf(HNode* buf[], int bufSize){
    HNode* tmp, *deletionval;
    for(int i = 0; i < bufSize; i++){
        tmp = buf[i];
        if(tmp){
            if(tmp->next) {
                while (tmp->next) {
                    deletionval = tmp;
                    tmp = tmp->next;
                    freeHNode(deletionval);
                }
                freeHNode(tmp);
            }
            else
                freeHNode(buf[i]);
        }
        
    }
}

int getHeight(Node* input){
    if(input)
        return input->height;
    return 0;
}

int heightDif(Node* input){
    int dif;
    dif = getHeight(input->rightnode) - getHeight(input->leftnode);
    return dif;
}

void fixHeight(Node* input){
    int lefth = getHeight(input->leftnode);
    int righth = getHeight(input->rightnode);
    if(lefth > righth)
        input->height = lefth + 1;
    else
        input->height = righth + 1;
}

Node* rotateRight(Node* input){
    Node* tmp;
    tmp = input->leftnode;
    input->leftnode = tmp->rightnode;
    tmp->rightnode = input;
    fixHeight(input);
    fixHeight(tmp);
    return tmp;
}

Node* rotateLeft(Node* input){
    Node* tmp;
    tmp = input->rightnode;
    input->rightnode = tmp->leftnode;
    tmp->leftnode = input;
    fixHeight(input);
    fixHeight(tmp);
    return tmp;
}

Node* treeBalance(Node* tree){
    fixHeight(tree);
    if(heightDif(tree) == 2){
        if(heightDif(tree->rightnode) < 0)
           tree->rightnode = rotateRight(tree->rightnode);
        return rotateLeft(tree);
    }
    if(heightDif(tree) == -2){
        if(heightDif(tree->leftnode) > 0)
            tree->leftnode = rotateLeft(tree->leftnode);
        return rotateRight(tree);
    }
    return tree;
}

Node* insert(Node** head, Node* input){
    Rstr* tmp;
    Node *root = *head;
    if(root == NULL){
        *head = input;
        return input;
    }

    if(root->key < input->key){
        root->rightnode = insert(&root->rightnode, input);
    }
    else if(root->key == input->key){
        tmp = root->data;
        while(tmp->next){
            tmp = tmp->next;
            input->data->release++;
        }
        input->data->release++;
        tmp->next = input->data;
        free(input);

    }
    else
        root->leftnode = insert(&root->leftnode, input);

    return treeBalance(root);
}

Rstr* search(Node* root, int tkey, int rel){
    Rstr* tmp;

    if(tkey > root->key && root->rightnode)
        search(root->rightnode, tkey, rel);

    else if(tkey < root->key && root->leftnode)
        search(root->leftnode, tkey, rel);

    else if(tkey == root->key){
        tmp = root->data;
        while(tmp->next && rel != tmp->release && rel != 0) {
            tmp = tmp->next;
        }
        if(rel == tmp->release || rel == 0){
            return tmp;
        }
        else{ //release error
            return NULL;
        }
    }
    else
        return NULL;
}



Rstr* searchMin(Node* root, int release){
    Rstr* tmp;
    Node* val = root;
    while(val->leftnode){ //finding last left min element of the tree
        val = val->leftnode;
    }
    tmp = val->data;
    if(release == 0)
        return val->data;
    else{
        while(tmp->next && tmp->release != release)
            tmp = tmp->next;
        if(tmp->release == release)
            return tmp;

        else
            return NULL;
    }
}

Node* minNode(Node* root){
    Node* res = root;
    if(res->leftnode) {
        while (res->leftnode) {
            res = res->leftnode;
        }
    }
    return res;
}

/*Node* maxNode(Node* root){
    Node* res = root;
    if(res->leftnode) {
        while (res->rightnode) {
            res = res->rightnode;
        }
    }
    return res;
}*/

Node* deleteMin(Node* root){
    if(root->leftnode == NULL)
        return root->rightnode;
    root->leftnode = deleteMin(root->leftnode);
    return treeBalance(root);
}

void freeNode(Node* input){
    free(input->data->str2);
    free(input->data->str1);
    free(input->data);
    free(input);
}

void freeHNode(HNode *input){
    free(input);
}

/*void nodeVal(Node* operand, Node* val, int mode){
    if(mode == 1)
        operand->leftnode = val;
    else if(mode == 2)
        operand->rightnode = val;
}*/

Node* deleteNode(Node* root, int key){
    if(!root)
        return NULL;
    if(key < root->key)
        root->leftnode = deleteNode(root->leftnode, key);
    else if(key > root->key)
        root->rightnode = deleteNode(root->rightnode, key);
    else{
        Node* left = root->leftnode;
        Node* right = root->rightnode;
        freeNode(root);
        if(!right) return left;
        Node* min = minNode(right);
        min->rightnode = deleteMin(right);
        min->leftnode = left;
        return treeBalance(min);
    }
    return treeBalance(root);

}

int fileInput(FILE *input, Node** root, HNode* buf[], int bufSize){
    int res;
    int linenum = 1;
    Node* tmp;
    do{
        if(linenum % 2 == 1){ //key lines
            tmp = NodeInit(0);
            res = (fscanf(input, "%d", &tmp->key));
            if(res == 1) {
                linenum++;
                continue;
            }
            freeNode(tmp);
            break; //line is empty or incorrect
        }
        else{ // data lines
            res = (fscanf(input, "%s %s", tmp->data->str1, tmp->data->str2));
            if(res == 2) {
                linenum++;
                if(bufInput(buf, tmp, bufSize) == -1){
                    return 0;
                }
                *root = insert(root, tmp);
                //printNode(tmp);
                continue;
            }
            freeNode(tmp);
            break; //empty/incorrect line
        }

    }while(1);
    return 1;
}

void freeData(Rstr* input){
    Rstr *val, *tmp = input;
    if(tmp) {
        while (tmp->next) {
            val = tmp;
            tmp = tmp->next;
            free(val->str1);
            free(val->str2);
            free(val);
        }
        free(tmp->str1);
        free(tmp->str2);
        free(tmp);
    }
}

void treeFree(Node* root){
    if(root){
        freeData(root->data);
        treeFree(root->leftnode);
        treeFree(root->rightnode);
        free(root);
    }
}

void printTable(Node* root, FILE* file){
    Rstr* tmp = root->data;
    // printing first part:    <tr><td> Anykey </td>
    fprintf(file, "            <tr><td> %d </td>", root->key);

    while (tmp->next) {
        //printing data part <td> data1 <br/> data2 </td>
        fprintf(file, "<td>%s<br/>%s</td>", tmp->str1, tmp->str2);
        tmp = tmp->next;
    }

    //printing last part ...<td> data ...</td></tr>
    fprintf(file, "<td>%s<br/>%s</td></tr>\n", tmp->str1, tmp->str2);

    if(root->leftnode){
        printTable(root->leftnode, file);
    }
    if(root->rightnode){
        printTable(root->rightnode, file);
    }
}

void printNull(int key, int nullNumber, FILE* file){
    fprintf(file, "    null%d [shape=point];\n", nullNumber);
    fprintf(file, "    %d -> null%d;\n", key, nullNumber);
}

void printAux(Node* node, FILE* file){
    static int nullCount = 0;

    if (node->leftnode){
        fprintf(file, "    %d -> %d;\n", node->key, node->leftnode->key);
        printAux(node->leftnode, file);
    }
    else
        printNull(node->key, nullCount++, file);

    if (node->rightnode){
        fprintf(file, "    %d -> %d;\n", node->key, node->rightnode->key);
        printAux(node->rightnode, file);
    }
    else{
        printNull(node->key, nullCount++, file);
    }
}

void printDot(Node* tree, FILE* file){
    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [fontname=\"Arial\"];\n");
    fprintf(file, "    aHtmlTable [\n");
    fprintf(file, "    shape=plaintext\n");
    fprintf(file, "    label=<\n");
    fprintf(file, "        <table border='1' cellspacing='0' cellpadding='3'>\n");
    fprintf(file, "            <tr><td> Keys</td><td colspan='100%%'> Data</td></tr>\n");

    //table print here
    printTable(tree, file);
    fprintf(file, "        </table>\n");
    fprintf(file, "    >];\n");

    if (!tree)
        fprintf(file, "\n");
    else if (!tree->rightnode && !tree->leftnode)
        fprintf(file, "    %d;\n", tree->key);
    else
        printAux(tree, file);

    fprintf(file, "}\n");
}

/*void printNode(Node* input){
    printf("Key: %d\n", input->key);
    printf("Data: \n");
    printf("\t String 1: %s\n\t String 2: %s\n", input->data->str1, input->data->str2);
}*/

int intInput(const char* msg){
    int var, rsc;
    do {
        while(getchar() != '\n'){}
        printf("%s", msg);
        rsc = scanf("%d", &var);
        if(rsc == -1){
            printf("End of file!\n");
            exit(-1);
        }
    } while(rsc < 1);
    return var;
}

int intchoice(int max) {
    int n, x;
    do{
        printf("Make a choice: ");
        x = scanf("%d", &n);
        if(x == 0)
            while(getchar() != '\n'){}
        if(x == -1){
            printf("End of file!\n");
            //exit(-1);
            return -1;
        }
    } while(x < 1 || n > max || n < 0);
    return n;
}

char* strInput(const char* msg){
    char* str;
    if(!(str = malloc(sizeof (char ) * STRSIZE)))
        return NULL;
    printf("%s", msg);
    scanf("%s", str);
    return str;
}