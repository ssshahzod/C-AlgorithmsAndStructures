#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "definitions.h"


int main(){
    FILE* fp;
    int x = 0, n = 0;
    char* str;
    Node* root = NULL;
    Node* tmp = NULL;
    printMenu(1);
    do {
        x = intinput(5);
        switch (x) {
            case (1):
                if(x == 1){
                    tmp = caseNodeInit();
                    if(tmp == NULL){
                        printf("Unable to allocate memory!\n");
                        x = 0;
                        break;
                    }
                    n = nodeInput(&root, tmp);
                    if(n == 30)
                        printf("Node already exist!\n");
                }
            case (2):
                if(x == 2){
                    printf("Input key: \n");
                    str = input();
                    tmp = search(root, str);
                    if(tmp) {
                        printNode(tmp);
                    }
                    else
                        printf("Node doesnt exist!\n");
                    free(str);
                }
            case(3):
                if(x == 3){
                    fp = fopen("output.txt", "w");
                    if(root == NULL){
                        printf("Tree is empty!\n");
                        fclose(fp);
                        break;
                    }
                    printDot(root, fp);
                    fclose(fp);

                }
            case(4):
                if(x == 4){
                    printf("Input the key: \n");
                    str = input();
                    if(root) {
                        n = deleteNode(root, str);
                        if(n == 0)
                            printf("Node doesnt exist!\n");
                    }
                    else
                        printf("Tree is empty!\n");
                    free(str);
                }
            case(5):
                if(x == 5){
                    Node* sRoot = NULL;
                    printf("Input the sentence: ");
                    if(inputWords(&sRoot) == -1){
                        printf("End of file!\n");
                        treeWordFree(sRoot);
                        x = 0;
                        break;
                    } //tree with our words
                    outputWords(sRoot);
                    treeWordFree(sRoot);
                }

        }
    } while(x);
    if(root)
        treeFree(root);

}

Node* caseNodeInit(){
    Node* nd;
    char* str;
    char* tmp;
    printf("Input the key: \n");
    str = input();
    printf("Input the data: \n");
    tmp = input();
    nd = nodeInit(tmp, str);
    return nd;
}

void printMenu(int mode){
    if (mode == 1){
        printf("0. Exit\n");
        printf("1. Input element.\n");
        printf("2. Search for an element.\n");
        printf("3. Print table.\n");
        printf("4. Delete element.\n");
        printf("5. Count words in sentence.\n");
    }
    else if(mode == 2){

    }
}

char* input(){
    char* str = (char*)malloc(sizeof (char) * STRSIZE);
    int n = 0;
    n = scanf("%s", str);
    if (n == -1){
        printf("End of file!\n");
        return NULL;
    }
    return str;
}

int intinput(int max) {
    int n, x;

    do{
        printf("Make a choice: ");
        x = scanf("%d", &n);
        if(x == 0)
            while(getchar() != '\n'){}
        if(x == -1){
            printf("End of file!\n");
            exit(-1);
        }
    } while(x < 1 || n > max || n < 0);

    return n;
}