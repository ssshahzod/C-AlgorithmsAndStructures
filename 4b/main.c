#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "definitions.h"


int main(){
    int bufSize = 30;
    int x, res;
    char* filename;
    FILE *output, *input;
    Node *root = NULL, *tmp = NULL;
    HNode* buf[bufSize];
    bufInit(buf, bufSize);
    printMenu(1);
    do {
        x = intchoice(7);
        switch (x) {
            case (1): //*
                if(x == 1){ //input
                    tmp = NodeInit(1);
                    res = bufInput(buf, tmp, bufSize);
                    if(tmp == NULL || res == -1){
                        printf("Memory allocation error!\n");
                        x = 0;
                        break;
                    }
                    root = insert(&root, tmp);
                }
            case(2): //
                if(x == 2){ // file input
                    filename = strInput("Input name of the file: ");
                    input = fopen(filename, "r");
                    if(!input){
                        printf("Error while opening file!\n");
                        break;
                    }
                    if(fileInput(input, &root, buf, bufSize) == 0){
                        printf("Memory allocation error!\n");
                        free(filename);
                        x = 0;
                        break;
                    }
                    free(filename);
                }
            case (3):
                if(x == 3){ // search
                    caseSearch(root, buf);
                }
            case(4):
                if(x == 4){ //print tree
                    output = fopen("output.txt", "w");
                    printDot(root, output);
                    fclose(output);
                }
            case(5):
                if(x == 5){
                    root = caseDelete(root);
                }
            case(6):
                if(x == 6){//find min
                    caseSearchMin(root);
                }
            case(7):
                if(x == 7){
                    TreeTiming(&tmp);
                }

        }
    } while(x > 0);
    freeBuf(buf, bufSize);
    treeFree(root);
}

int TreeTiming(Node** node){
    Node* root, *tmp = NULL;
    int n = 10, key[10000], k, cnt = 1000000, i, m;
    clock_t first, last;
    srand(time(NULL));
    while(n-- > 0) {
        for (i = 0; i < 10000; ++i)
            key[i] = rand() * rand();
        for (i = 0; i < cnt;) {
            k = rand() * rand();
            tmp = NodeInit(0);
            tmp->key = k;
            if (insert(&root, tmp))
                ++i;
        }
        m = 0;
        first = clock();
        for (i = 0; i < 10000; ++i)
            if (search(root, key[i], 0))
                ++m;
        last = clock();
        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %ld\n", 10 - n, (10 - n) * cnt, (last - first));
        printf("CLOCKS per sec: %ld\n", CLOCKS_PER_SEC);
    }
    treeFree(root);
    return 1;
}


Node* caseDelete(Node* root){
    int key = intInput("Input key of the node: ");
    Node* res = deleteNode(root, key);
    if(res == 0){
        printf("Node doesnt exist!\n");
        return root;
    }
    return res;

}

void caseSearchMin(Node* root){
    Rstr* result;
    printMenu(2);
    int rel = intchoice(2);
    if(rel == 2)
        rel = intInput("Input the release: ");
    else
        rel = 0;
    result = searchMin(root, rel);
    if(result)
        printData(result);
    else
        printf("Element doesnt exist!\n");

}

void caseSearch(Node* root, HNode* buf[]){
    Rstr *res;
    HNode *tmp;
    int searchkey, release;
    printMenu(2);
    release = intchoice(2);
    searchkey = intInput("Input the key: ");
    if(release == 2) {
        release = intInput("Input the release: ");
        while(release < 0) {
            printf("Wrong release, try again! ");
            release = intInput("Input the release: ");
        }
    }
    else
        release = 0;

    if(release == 0) {
        int hash = hashFunc(searchkey);
        tmp = buf[hash];
        if (buf[hash] != NULL) {
            if (tmp->key == searchkey) {
                printData(tmp->data);
                return;
            } else if (tmp->next) {
                while (tmp->next && tmp->key != searchkey)
                    tmp = tmp->next;
                if (tmp->key == searchkey) {
                    printData(tmp->data);
                    return;
                }
            }
        }
    }

    res = search(root, searchkey, release);
    if(res) {
        printData(res);
    }
    else
        printf("Element doesnt exist!\n");

}

void printData(Rstr* res){
    printf("String 1: %s\n", res->str1);
    printf("String 2: %s\n", res->str2);
    printf("Release: %d\n", res->release);
}

void printMenu(int mode){
    if (mode == 1){
        printf("0. Exit\n");
        printf("1. Input element.\n");
        printf("2. Read from the file.\n");
        printf("3. Search for an element.\n");
        printf("4. Print tree.\n");
        printf("5. Delete element.\n");
        printf("6. Find min.\n");
    }
    else if(mode == 2){
        printf("1. Search without release.\n");
        printf("2. Search with release.\n");
    }

}