#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "definitions.h"


int main() {
    int x = 1, choice;
    FILE* input, *output;
    char* tmp, *str = NULL;
    printMenu(0);
    do {
        x = choiceFunc(3);
        switch(x){
            case (1):
                if (x == 1) { //encode the string

                    tmp = strInput("Input name of the file: ");
                    if(!tmp){
                        printf("Memory allocation error!\n");
                        x = 0;
                        free(tmp);
                        break;
                    }
                    input = fopen(tmp, "r");
                    strcat(tmp, "cmp");
                    output = fopen(tmp, "wb");
                    if(input) {
                        printf("HERERE\n");
                        encoding(input, output);
                        fclose(input);
                    }
                    else
                        printf("Error while openning file!\n");
                    free(tmp);

                }
            case (2):
                if (x == 2) { // decode the string
                    tmp = strInput("Input name of the file: ");
                    if(!tmp){
                        printf("Memory allocation error!\n");
                        x = 0;
                        free(tmp);
                        break;
                    }
                    if (!(input = fopen(tmp, "rb"))) { //rb - read binary
                        printf("Couldn't open the file!\n");
                        free(tmp);
                        break;
                    }
                    else {
                        //decoding(input);
                    }

                }

        }
    }while(x);
    return 0;
}


void encoding(FILE* input, FILE* output){
    int num = 0;
    char* str;
    char code[256];
    Code** letters = (Code**)malloc(sizeof (Code) * 256);
    Symbol** arr, *que;
    for(int i = 0; i < 256; i++) {
        letters[i] = 0;
        code[i] = 0;
    }

    //while(){}
    str = strInput("Input the string: ");
    arr = freqCount(str);
    que = enQueue(arr);
    treeMake(&que);
    codesfromTree(que, letters, code, num);
    num = nodesInTree(que);

    fSymbol* array[num * 3];
    for(int i = 0; i < num * 3; i++)
        array[i] = NULL;

    treeToArray(que, array, 1);
    arrayWrite(array, num * 3, output);
    scanf("%d", &num);
}

void printMenu(int m){
    if(m == 0)
        printf("1. Encode text string.\n"
                      "2. Decode binary string.\n");
    else if(m == 1)
        printf("1.Input.\n"
                      "2.Read from file.\n");
}

void caseEncodeString(){
    int choice = 0;
    printf("1.Input the string.\n");
    printf("2.Read string from the text file.\n");
    choice = choiceFunc(2);

    if(choice == 1){
        char* str = strInput("Input the string: ");

    }
    else{
        ///
    }
}

int choiceFunc(int max){
    int res, var;
    do{
        printf("Make a choice: ");
        var = scanf("%d", &res);
        if(var == 0)
            while(getchar() != '\n'){}
    } while(var < 1 || res > max || res < 0);
    return res;
}

int intInput(char const* msg){
    int res;
    int var;
    do{
        printf("Input integer value: ");
        var = scanf("%d", &res);
        if(var == -1){
            printf("End of file!\n");
            exit(-1);
        }

    } while(var < 1);
    return res;
}

char* strInput(char const* msg){
    char* str = (char*)malloc(sizeof (char) * STRSIZE);
    if(!str)
        return NULL;
    printf("%s", msg);
    while(getchar() != '\n');
    if(scanf("%[^\n]%*c", str) == -1){
        printf("End of file!\n");
        exit(-1);
    }
    printf("%s\n", str);
    return str;
}