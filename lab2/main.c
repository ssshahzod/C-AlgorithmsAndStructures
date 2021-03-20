#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

#ifndef MAXSIZE
#define MAXSIZE 20
#endif

bool operator(char x);
bool operand(char ch);
int precendece(char c);
void infix2postfix(char* infix);
bool isinfix(char* input);


int main(){
	int i = 1;

	char* input = malloc(MAXSIZE);
	printf("Input the infix formula:\n");
	fgets(input, MAXSIZE - 1, stdin);

	while (!isinfix(input)){
		printf("Wrong formula! Try again:\n");
		fgets(input, MAXSIZE - 1, stdin);

		if(!fgets(input, MAXSIZE - 1, stdin)){
			printf("End of file!\n");
			exit(-1);
		}

	}
	infix2postfix(input);
	free(input);

}

bool operator(char x){
	if(x == '+' || x == '-' || x == '*' || x == '/')
		return true;
	return false;
}

bool number(char x){
	if(x == '0' || x == '1' || x == '2' || x == '3' || x == '4' 
					|| x == '5' || x == '6' || x =='7' || x == '8' || x == '9')
					return true;
	return false;
}

int precendece(char c) { 
    if(c == '*' || c == '/') 
    	return 2; 
    else if(c == '+' || c == '-') 
    	return 1; 
    else
    	return -1; 
} 

bool operand(char ch) { 
    return (ch >= 'a' && ch <= 'z') ||  (ch >= 'A' && ch <= 'Z'); 
} 

bool isinfix(char* input){
	int i = 0, sg = 0, let = 0, sk = 0;
	while(i, i < strlen(input)){
		if(operand(input[i]))
			let++;
		else if(operator(input[i])){
			sg++;
		}
		else if(input[i] == '(' || input[i] == ')')
			sk++;
		else if(number(input[i])){
			return false;
			break;
		}
        i++;

	}
	if((let - sg == 1) && (sk % 2 == 0) 
			&& (sg + let + sk == strlen(input) - 1) && sk % 2 == 0){
		return true;
	}
	else
		return false;
        
}

void infix2postfix(char* infix){
	int sign = 0, sk = 0;
	int i = 0;
	int size = strlen(infix);

	bool overflow = false;

	Stack* postfixStack = StackGeneration();
	Stack* operatorStack = StackGeneration(); 

	while(*(infix + i) != '\0'){

		if(*(infix + i) == ' '){
            i++;
            continue;
        }

        if(operand(*(infix + i))){ 
            overflow = push(postfixStack, infix[i]);
            //printf("%c\n", *(infix + i));
        }

        else if(*(infix + i) == '('){
            overflow = push(operatorStack, infix[i]);
            sk++;
            i++;
            continue;
        }  

        else if(operator(*(infix + i))){
        	sign++;
        	//printf("%s %d\n", "sign:", sign);
        	while(precendece(*(infix + i)) <= precendece(peek(operatorStack))){

                overflow = push(postfixStack, pop(operatorStack));
                sign--;
            }

            overflow = push(operatorStack, infix[i]);
        }    

        else if(*(infix + i) == ')'){
            while(peek(operatorStack) != '('){
                overflow = push(postfixStack, pop(operatorStack));
            }
            pop(operatorStack);
        }

        else if(overflow){
            printf("Invalid formula!\n");
            exit(1);
        }

        i++;

	}
	//printf("%d\n", sign);
	if(sign == 1 && sk == 1){}
	else{
		overflow = push(postfixStack, pop(operatorStack));
	}

	printf("Infix formula: \n");
	print(postfixStack);
	//print(operatorStack);
	delete(postfixStack);
	delete(operatorStack);
	
}



        
