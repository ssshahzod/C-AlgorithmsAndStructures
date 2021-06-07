#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "definitions.h"

//to-do подсчет частоты символов
//построение дерева на основе частоты
//сохранение дерева в файле
//

Symbol* initSymbol(char letter){
    Symbol* tmp = (Symbol*)malloc(sizeof (Symbol));
    tmp->sym = letter;
    tmp->freq = 1;
    tmp->left = tmp->right = tmp->next = NULL;
    return tmp;
}

Symbol* nodeInit(int num){
    Symbol* tmp = (Symbol*) malloc(sizeof (Symbol));
    tmp->next = tmp->left = tmp->right = NULL;
    tmp->freq = num;
    tmp->sym = '*';
    return tmp;
}

Symbol** freqCount(char* str){ //
    int num, lettersNum = 0;
    Symbol* queue = NULL;
    Symbol* tmp = NULL;
    Symbol** list = (Symbol**) malloc(sizeof (Symbol) * 256);

    for(int i = 0; i < 256; i++)
        list[i] = NULL;

    for(int i = 0; i < strlen(str); i++){
        num = str[i] - ' ';
        if(list[num] == NULL){
            list[num] = initSymbol(str[i]);
            lettersNum++;
        }
        else
            list[num]->freq++;
    }

    return list;
}

Symbol* enQueue(Symbol** list){
    Symbol* queue = NULL;

    int j = 0;
    for(int i = 0; i < 256; i++){
        if(list[i] != NULL){
            push(&queue, list[i]);

        }
    }

    return queue;
}

int treeMake(Symbol** queue){
    int i = 0;
    Symbol* tmp;
    Symbol* leftt, *rightt;
    while(moreThan1Node(*queue)){
        leftt = pop(queue);
        rightt = pop(queue);
        tmp = nodeInit(leftt->freq + rightt->freq);
        tmp->left = leftt;
        tmp->right = rightt;
        push(queue, tmp);
        printQueue(*queue);
        i++;
    }
    return i;
}

void codesfromTree(Symbol* root, Code** codes, char code[256], int codeLenght){

    if(root->left){
        code[codeLenght] = '0';
        codeLenght++;
        codesfromTree(root->left, codes, code, codeLenght);
    }

    if(root->right){
        code[codeLenght] = '1';
        codeLenght++;
        codesfromTree(root->right, codes, code, codeLenght);
    }

    if(!root->right && !root->left){
        Code* tmp = (Code*) malloc(sizeof (Code));
        tmp->code = (char*) malloc(sizeof (char ) * codeLenght);
        tmp->lenght = codeLenght;
        strcpy(tmp->code, code);
        codes[root->sym - ' '] = tmp;
    }

}

//for decoding
void codesfromArray(){

}

int nodesInTree(Symbol* root){
    static int num = 1;
    if(root->left){
        num++;
        nodesInTree(root->left);
    }
    if(root->right){
        num++;
        nodesInTree(root->right);
    }
    return num;
}

void treeToArray(Symbol* root, fSymbol* arr[], int i){
    Symbol* tmp = root;

    arr[i] = (fSymbol*) malloc(sizeof (fSymbol));
    if(!tmp->left && !tmp->right) {
        arr[i]->sym = root->sym;
        arr[i]->left = arr[i]->right = -1;
    }

    if(tmp->left){
        arr[i]->left = 2 * i;
        arr[i]->right = 2 * i + 1;
        treeToArray(root->left, arr, 2 * i);
    }
    if(tmp->right){
        arr[i]->left = 2 * i;
        arr[i]->right = 2 * i + 1;
        treeToArray(root->right, arr, 2 * i + 1);
    }

}

void arrayWrite(fSymbol* array[], int num, FILE* output){
    //size of array
    fwrite(&num, sizeof (int), 1, output);

    for(int i = 1; i < num; i++){
        fwrite(array[i]->sym, sizeof (char), 1, output);
        fwrite(&array[i]->left, sizeof (int), 1, output);
        fwrite(&array[i]->right, sizeof (int ), 1, output);
    }
}



// Priority Queue:

Symbol* peek(Symbol* head){
    if(head)
        return head;
    return NULL;
}

Symbol* pop(Symbol** head){
    Symbol* tmp = *head;
    *head = (*head)->next;
    tmp->next = NULL;
    return tmp;
    //free(tmp);
}

void push(Symbol** head, Symbol* input){
    Symbol* first = *head;

    if((*head) == NULL){
        *head = input;
        (*head)->next = NULL;
        return;
    }
    if(input->freq < (*head)->freq){
        input->next = *head;
        (*head) = input;
    } else{
        while(first->next && first->next->freq < input->freq)
            first = first->next;

        input->next = first->next;
        first->next = input;
    }
}

bool moreThan1Node(Symbol* que){
    if(que)
        if(que->next)
            return true;
    return false;
}

void printQueue(Symbol* head){
    int i = 0;
    Symbol* tmp = head;
    while(tmp->next) {
        i++;
        printf("Symbol: %c, Freq: %d\n", tmp->sym, tmp->freq);
        tmp = tmp->next;
    }
    printf("Symbol: %c, Freq: %d\n", tmp->sym, tmp->freq);
}
