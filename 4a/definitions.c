#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "definitions.h"


Node* nodeInit(char* info, char* Key){
    Node* tmp = (Node*)malloc(sizeof (Node));
    if(tmp == NULL)
        return NULL;
    //->key = (char*)malloc(sizeof(char)* STRSIZE);
    //tmp->data = (char*)malloc(sizeof(char) * STRSIZE);
    tmp->data = info;
    tmp->key = Key;
    tmp->left = tmp->right = NULL;
    tmp->same = false;
    return tmp;
}

int nodeInput(Node** head, Node* ins){
    Node* temp = *head;
    if(*head == NULL){
        *head = ins;
        return 1;
    }

    while(temp){
        if(strcmp(ins->key, temp->key) > 0){
            if(temp->right) {
                temp = temp->right;
                continue;
            } else {
                temp->right = ins;
                return 1;
            }
        }
        else if((strcmp(ins->key, temp->key) < 0)){
            if(temp->same) {
                temp = temp->right;
                continue;
            }
            else{
                if (temp->left) {
                    temp = temp->left;
                    continue;
                } else {
                    temp->left = ins;
                    return 1;
                }
            }
        }
        else if(strcmp(ins->key, temp->key) == 0) {
            while(temp->right && !strcmp(ins->key, temp->right->key)
                                && (strcmp(ins->data, temp->data) != 0)) {
                temp->same = true;
                temp = temp->right;
            }
            if(strcmp(ins->data, temp->data) == 0)
                return 30;
            if(temp->right || temp->left){
                if(temp->right)
                    ins->right = temp->right;
                if(temp->left)
                    ins->left = temp->left;
                temp->right = ins;
                temp->same = true;
                return 1;
            }
            temp->same = true;
            temp->right = ins;
            temp->left = NULL;

            return 1;
        }
    }

}

void printNode(Node* input){
    if(input) {
            printf("Key: %s\n", input->key);
            printf("Data: %s\n", input->data);
            printf("\n");

    }
}

void prevNext(Node* prev, int side, Node* tmp){
    if (side == 1)
        prev->left = tmp;
    else if (side == 2)
        prev->right = tmp;
}

void getMin(Node* curr, Node* right){
    Node* start = right;
    Node* prev = curr;
    while(start->left) {
        prev = start;
        start = start->left;
    }

    curr->data = start->data;
    curr->key = start->key;

    prev->left = start->right ? start->right : NULL;
    clearNode(start);
}

void getMax(Node* curr, Node* left){
    Node* start = left;
    Node* prev = curr;
    while(start->right) {
        prev = start;
        start = start->right;
    }

    curr->data = start->data;
    curr->key = start->key;

    prev->right = start->left ? start->left : NULL;
    clearNode(start);
}

int deleteNode(Node* root, char* dkey){
    //tree cant be empty (checking in the main)
    Node* tmp = root, *prev = NULL, *min = NULL;
    int side = 0;
    while(1){
        if(strcmp(tmp->key, dkey) > 0){
            if(tmp->left) {
                prev = tmp;
                tmp = tmp->left;
                side = 1;
                continue;
            }
            return 0;
        }
        else if(strcmp(tmp->key, dkey) < 0){
            if(tmp->right) {
                prev = tmp;
                tmp = tmp->right;
                side = 2;
                continue;
            }
            return 0;
        }
        else{
            //1st case
            if(!tmp->right && !tmp->left){
                clearNode(tmp);
                if(prev)
                    prevNext(prev, side, NULL);
                else
                    root = NULL;
                return 1;
            }
            //3rd case
            else if(tmp->right && tmp->left){
                if(tmp->right->left || tmp->left->right){
                    if(tmp->right->left)
                        getMin(tmp, tmp->right);
                    else
                        getMax(tmp, tmp->left);
                    return 1;
                }
                else{
                    tmp->data = tmp->left->data;
                    tmp->key = tmp->left->key;
                    tmp->left = tmp->left->left;
                    clearNode(tmp->left);
                    return 1;
                }
            }
            //2nd case
            else{
                if(tmp->right)
                    prevNext(prev, side, tmp->right);
                else
                    prevNext(prev, side, tmp->left);
                clearNode(tmp);
                return 1;
            }
        }
    }
}

void clearNode(Node* node){
    if(node != NULL) {
        free(node->key);
        free(node->data);
        free(node);
        node = NULL;
    }
}

Node* search(Node* root, char* key){
    int compresult;
    bool done = false;
    Node* node = root;
    if(root == NULL) {
        return root;
    }
    while(!done){
        compresult = strcmp(node->key, key);
        if(!compresult)
            return node;
        else if((compresult > 0) && node->left)
            node = node->left;

        else if((compresult < 0) && node->right)
            node = node->right;

        else if((compresult != 0) && (!node->right || !node->left)){ //node doesnt exist
            return NULL;
        }
    }
}

void treeFree(Node* root){
    if(root != NULL){
        free(root->key);
        free(root->data);
        if(root->right)
            treeFree(root->right);
        if(root->left)
            treeFree(root->left);
        free(root);
    }
}

int inputWords(Node** root){
    while(getchar() != '\n');
    char str[150];
    char* word;
    Node* tmp;
    int i = 1, n;
    n = scanf("%[^\n]%*c", str);
    if(n == -1)
        return -1;

    word = strtok(str, " ,.-!?");
    while(word != NULL){ //extracting one word from the sentence
        i++;
        tmp = (Node*) malloc(sizeof (Node));
        tmp->same = false;
        tmp->left = tmp->right = NULL;
        tmp->key = word;
        tmp->data = word + i;
        nodeInput(root, tmp);
        word = strtok(NULL, " ,.-!?");
    }
    return 1;

}

void outputWords(Node* root){
    int i = 1;
    Node* tmp = root;
    if(tmp->right && !strcmp(tmp->key, tmp->right->key)) {
        while (tmp->right && !strcmp(tmp->key, tmp->right->key)) {
            i++;
            tmp = tmp->right;
        }
        printf("%s: %d\n", tmp->key, i);
        i = 1;
    }
    else{
        printf("%s: 1\n", tmp->key);
    }
    if(tmp->right)
        outputWords(tmp->right);
    if(tmp->left)
        outputWords(tmp->left);
}

void treeWordFree(Node* root){
    if(root != NULL){
        treeWordFree(root->right);
        treeWordFree(root->left);
        free(root);
    }
}

void printNull(char* key, int nullNumber, FILE* file){
    fprintf(file, "    null%d [shape=point];\n", nullNumber);
    fprintf(file, "    %s -> null%d;\n", key, nullNumber);
}

void printAux(Node* node, FILE* file){
    static int nullCount = 0;

    if (node->left){
        fprintf(file, "    %s -> %s;\n", node->data, node->left->data);
        printAux(node->left, file);
    }
    else if(node->same == false)
        printNull(node->data, nullCount++, file);

    if (node->right){
        fprintf(file, "    %s -> %s;\n", node->data, node->right->data);
        printAux(node->right, file);
    }
    else if(node->same == false) {
        printNull(node->data, nullCount++, file);
    }
}

void printDot(Node* tree, FILE* file){
    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(file, "\n");
    else if (!tree->right && !tree->left)
        fprintf(file, "    %s;\n", tree->data);
    else
        printAux(tree, file);

    fprintf(file, "}\n");
}