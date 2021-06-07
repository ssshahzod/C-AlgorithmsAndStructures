#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "definitions.h"

Node* nodeInit(){
    Node* tmp;
    tmp = (Node*)malloc(sizeof (Node));
    tmp->next = NULL;
    tmp->nextbelow = NULL;
    if(!tmp)
        return NULL;
    return tmp;
}

Node* createNode(){
    Node* tmp = nodeInit();
    if(tmp) {
        tmp->name = strInput("Input name of the node: ");
        tmp->xcord = floatInput("Input X cord: ");
        tmp->ycord = floatInput("Input Y cord: ");
        return tmp;
    }
    return NULL;
}

Node* nodeInitwInfo(char* name, float xcord, float ycord){
    Node* tmp = nodeInit();
    tmp->name = name;
    tmp->xcord = xcord;
    tmp->ycord = ycord;
    return tmp;
}

List* listNode(char* info){
    List* tmp = (List*) malloc(sizeof (List));
    tmp->str = (char*) malloc(sizeof (char) * STRSIZE);
    tmp->next = NULL;
    tmp->str = info;
    return tmp;
}

Node* graphInput(Node* graph, Node* input){
    Node* tmp = graph;
    if(graph == NULL){
        graph = input;
        return graph;
    }
    //checking graph
    while(tmp->nextbelow){
        //if vertix with this name already exists
        if(!strcmp(tmp->name, input->name)){
            freeNode(input);
            return graph;
        }
        tmp = tmp->nextbelow;
    }
    if(!strcmp(tmp->name, input->name)){
        freeNode(input);
        return graph;
    }
    tmp->nextbelow = input;
    return graph;


}

float weightCounter(Node* vertix1, Node*  vertix2){
    float res;
    res = sqrtf(powf((vertix1->xcord - vertix2->xcord), 2) + powf((vertix1->ycord - vertix2->ycord), 2));
    return res;
}

int createEdges(Node* graph, char* name1, char* name2){
    int compareresult1 = 1, compareresult2 = 1, snum = 0;
    float weight;
    Node* tmp = graph;
    Node *tmp1 = NULL, *tmp2 = NULL, *firstend, *secondend;
    Node* res1, *res2;
    //searching for vertices
    while(tmp){
        if (!strcmp(tmp->name, name1))
            tmp1 = tmp;
        if (!strcmp(tmp->name, name2))
            tmp2 = tmp;
        //if vertices were found can stop searching
        if(tmp1 && tmp2) {
            break;
        }
        if(tmp->nextbelow) {
            tmp = tmp->nextbelow;
            continue;
        }
        else
            break;
    }

    if(tmp1 && tmp2) {
        secondend = tmp2;
        firstend = tmp1;

        //
        while (firstend->next && (compareresult1 = strcmp(firstend->name, name2)) != 0)
            firstend = firstend->next;

        //
        while (secondend->next && (compareresult2 = strcmp(secondend->name, name1)) != 0)
            secondend = secondend->next;

        if (!compareresult1 && !compareresult2)
            return 30; // edge already exists

        weight = weightCounter(tmp1, tmp2);
        res1 = nodeInitwInfo(tmp2->name, tmp2->xcord, tmp2->ycord);
        res2 = nodeInitwInfo(tmp1->name, tmp1->xcord, tmp1->ycord);
        firstend->next = res1;
        secondend->next = res2;
        res1->nodeWeight = res2->nodeWeight = weight;
        return 1;
    }
    return (tmp1 == NULL ? -1 : -2); // - 1 -> vertice name1 doesnt exist; -2 -> name2 doesnt exist
}

void printLists(Node* graph){
    Node* tmp, *line;
    if(graph == NULL)
        return;
    else{
        tmp = graph;
        while(tmp) {
            printf("Vertix: %s ", tmp->name);
            line = tmp->next;
            while(line){
                printf("--> Vertix: %s", line->name);
                if(line->next)
                    line = line->next;
                else
                    break;
            }
            if(tmp->nextbelow) {
                printf("\n  |\n \\/\n");
                tmp = tmp->nextbelow;
            }
            else {
                printf("\n");
                return;
            }
        }
    }
}

int deleteEdge(Node* graph, char* name1, char* name2){
    int compareresult1 = 1, compareresult2 = 1;
    Node* root = graph;
    Node *tmp1 = NULL, *tmp2 = NULL;
    Node *prev1, *prev2, *firstend, *secondend;
    while(root){
        //searching for first vertix
        if(!strcmp(root->name, name1))
            tmp1 = root;
        //second
        if(!strcmp(root->name, name2))
            tmp2 = root;
        if(tmp1 && tmp2){

            printf("TMP1: %s; TMP2: %s\n", tmp1->name, tmp2->name);
            break;
        }
        if(root->nextbelow) {
            root = root->nextbelow;
            continue;
        }
        else
            break;
    }
    if(tmp1 && tmp2) {
        prev1 = firstend = tmp1;
        prev2 = secondend = tmp2;
        //searching for the node
        while (firstend->next && (compareresult1 = (!strcmp(firstend->name, name1)) != 0)) {
            prev1 = firstend;
            firstend = firstend->next;
        }


        while (secondend->next && (compareresult2 = (!strcmp(secondend->name, name2)) != 0)) {
            prev2 = secondend;
            secondend = secondend->next;
        }

        //freeNode(prev1->next);
        //freeNode(prev2->next);
        prev1->next = firstend->next;
        prev2->next = secondend->next;
    }
    else
        return (tmp1 == NULL ? -1 : -2);
}

int deleteVertix(Node* graph, char* name){
    bool done= false;
    Node* tmp = graph, *prev = NULL;
    Node* vertices = tmp;
    Queue* que = createQueue(QSIZE);

    while(tmp){

        if(!strcmp(tmp->name, name)){
            break;
        }
        if(tmp->nextbelow){
            prev = tmp;
            tmp = tmp->nextbelow;
            continue;
        }
        else
            break;
    }
    //node doesnt exist
    if(!strcmp(tmp->name, name) && !tmp->nextbelow)
        return 0;

    if(tmp->next){
        vertices = tmp->next;
        while(vertices){
            //getting all edges
            push(que, vertices);
            if(vertices->next){
                vertices = vertices->next;
                continue;
            }
            else
                break;
        }
        deleteinRow(graph, que, name);
        vertices = tmp->next;

    }

    if(prev){
        //if vertix doesnt have edges
        prev->nextbelow = tmp->nextbelow;
        freeNode(tmp);
    }
    //if vertix is first in list
    else {
        graph = graph->nextbelow;
        freeNode(tmp);
    }

}

void deleteinRow(Node* graph, Queue* que, char* name){
    int res;
    Node* tmp = graph;
    Node* row, *prev = NULL;
    //
    Node* qnode = pop(que);
    while(qnode){
        //searching for the first node
        if(!strcmp(tmp->name, qnode->name)){
            prev = tmp;
            row = tmp->next;
            while(row && ((res = strcmp(row->name, name)) != 0)){
                prev = row;
                row = row->next;

            }
            if(!res){
                prev->next = row->next;
                qnode = pop(que);
            }
        }

        if(tmp->nextbelow){
            tmp = tmp->nextbelow;
            continue;
        }
        else
            break;
    }
}

int numofVertix(Node* graph){
    Node* tmp = graph;
    int num = 0;
    while(tmp){
        num++;
        if(tmp->nextbelow)
            tmp = tmp->nextbelow;
        else
            break;
    }
    return num;
}

Node* searchbyNum(Node* graph, int num){
    Node* res = graph;
    int i = 0;
    while(i != num){;
        i++;
        if(res->nextbelow)
            res = res->nextbelow;
        else
            break;
    }
    return res;
}

int findVert(Node* graph, char* name){
    Node* tmp = graph;
    int num = 0;
    while(tmp){
        if(!strcmp(tmp->name, name))
            return num;
        else if(tmp->nextbelow)
            tmp = tmp->nextbelow;
        else
            break;
        num++;
    }
    return num;
}

Node* searchbyName(Node* graph, char* name){
    Node* tmp = graph;
    while(tmp){
        if(strcmp(tmp->name, name) == 0)
            return tmp;
        if(tmp->nextbelow)
            tmp = tmp->nextbelow;
        else
            break;
    }
}

List* bfs(Node* graph, char* namesearchfor, char* namesearchby){
    int compareres, vertixNum = numofVertix(graph), vnum = 0;
    int neighborNum = -1;
    int visited[vertixNum];
    int prev[vertixNum];
    bool done = false;

    List* path = NULL;
    Queue* que = createQueue(QSIZE);
    Node* curr, *val;
    Node* tmp = graph;

    for(int i = 0; i < vertixNum; i++) {
        visited[i] = 0;
        prev[i] = 0;
    }

    //searching for start vertix
    while(tmp && (compareres = strcmp(tmp->name, namesearchby)) != 0){
        if(tmp->nextbelow){
            vnum++;
            tmp = tmp->nextbelow;
            continue;
        }
        else
            break;
    }
    //node namesearchby doesnt exist
    if(compareres != 0)
        return path;

    push(que, tmp);
    visited[vnum] = 1;
    //doesnt have previous node
    prev[vnum] = -1;

    while(!isEmpty(que) && !done){
        curr = pop(que);
        vnum = findVert(graph, curr->name);
        val = curr->next;
        while(val){
            neighborNum = findVert(graph, val->name);
            if(visited[neighborNum] == 0){
                tmp = searchbyName(graph, val->name);
                push(que, tmp);
                visited[neighborNum] = 1;
                prev[neighborNum] = vnum;
                if(strcmp(val->name, namesearchfor) == 0){
                    done = true;
                    break;
                }
            }
            if(val->next) {
                val = val->next;
            }
            else
                break;

        }
    }
    while(neighborNum != -1){
        tmp = searchbyNum(graph, neighborNum);
        if(path == NULL)
            path = listNode(tmp->name);
        else
            listPush(&path, tmp->name);
        neighborNum = prev[neighborNum];

    }

    return path;
}

void minTreeSearch(Node* graph){
    Node* tree;
    Node* tmp = graph;
    Node* rowVal = NULL;


}

Node* readfromFile(FILE* input){
    Node* graph = NULL, *tmp = NULL, *val;
    char* vertix, *temp = NULL, *temp2,*str;
    float cordx = 0, cordy = 0;
    int numOfVert, i = 0;
    str = (char*) malloc(sizeof (char) * STRSIZE);

    numOfVert = atoi(fgets(str, STRSIZE, input));
    if(numOfVert == 0)
        return NULL;

    while(fgets(str, STRSIZE, input) != NULL){
        temp2 = temp = strtok(str, " ");
        if(i < numOfVert) {
            vertix = (char *) malloc(sizeof(char) * STRSIZE);
            strcpy(vertix, temp);

            for(int j = 0; j < 2; j++) {
                temp2 = strtok(NULL, " ");
                if (j == 0)
                    cordx = (float) atof(temp2);
                else
                    cordy = (float) atof(temp2);
            }

            if (graph == NULL)
                graph = nodeInitwInfo(vertix, cordx, cordy);
            else {
                val = graph;
                tmp = nodeInitwInfo(vertix, cordx, cordy);
                while (val->nextbelow)
                    val = val->nextbelow;
                val->nextbelow = tmp;
            }
        }
        else{
            temp2 = strtok(NULL, " ");
            while(temp2 != NULL){
                printf("TEMP: %s", temp);
                printf("TEMP2: %s", temp2);
                printf("RES: %d\n", createEdges(graph, temp2, temp));
                temp2 = strtok(NULL, "  \n");
            }
        }
        i++;

    }

    free(str);
    return graph;
}

void saveToFile(Node* graph, FILE* output){
    List* vertices = NULL, *val;
    bool exists = false;
    int num = numofVertix(graph), same, i;
    Node* tmp = graph, *row = NULL;
    fprintf(output, "%d\n", num);
    for(int j = 0; j < num; j++){
        fprintf(output, "%s %g %g\n", tmp->name, tmp->xcord, tmp->ycord);
        tmp = tmp->nextbelow;
    }

    tmp = graph;
    while(tmp){

        row = tmp;
        while(row){
            same = 0;
            i = 0;
            val = vertices;
            while(val){
                if(strcmp(row->name, val->str) == 0) {
                    same++;
                    exists = true;
                }
                if(val->next) {
                    i++;
                    val = val->next;
                }
                else
                    break;
            }
            if(!exists && same == i) {
                fprintf(output, "%s ", row->name);
            }
            else
                printf("SAME: %d, I: %d", same, i);

            exists = false;
            if(row->next)
                row = row->next;

            else {
                fprintf(output, "\n");
                break;
            }
        }
        if(tmp->nextbelow) {
            if(vertices == NULL)
                vertices = listNode(tmp->name);
            else
                listPush(&vertices, tmp->name);
            tmp = tmp->nextbelow;
        }
        else
            break;

    }
}

//добавить проверку копий, как в предыдущей функции
void printDot(Node* graph, FILE* output){
    Node* tmp = graph, *val;
    fprintf(output, "graph {\n");
    fprintf(output, "    node [fontname=\"Arial\"];\n");
    while(tmp){
        val = tmp->next;
        while(val){
            fprintf(output, "    %s -- %s[label=\"%f\"];\n", tmp->name, val->name, val->nodeWeight);
            if(val->next)
                val = val->next;
            else
                break;
        }

        if(tmp->nextbelow)
            tmp = tmp->nextbelow;
        else
            break;
    }
    fprintf(output, "}\n");
}

void freeNode(Node* input){
    free(input->name);
    free(input);
}

float floatInput(const char* msg){
    int rsc;
    float var;
    do {
        while(getchar() != '\n'){}
        printf("%s", msg);
        rsc = scanf("%f", &var);
        if(rsc == -1){
            printf("End of file!\n");
            exit(-1);
        }
    } while(rsc < 1);

    return var;
}


char* strInput(const char* msg){
    char* str;
    if(!(str = malloc(sizeof (char ) * STRSIZE)))
        return NULL;
    printf("%s", msg);
    scanf("%s", str);
    return str;
}

//queue

Queue* createQueue(int size){
    Queue* que = (Queue*)malloc(sizeof(Queue));
    que->numofelem = que->head = 0;
    que->size = size;
    que->tail = size - 1;
    (que->array) = (Node**) malloc(size * sizeof(Node));
    for(int i = 0; i < size; i++){
        que->array[i] = NULL;
    }
    return que;
}

Node* pop(Queue* que){
    Node* res;
    if(que->numofelem == 0)
        return NULL;
    res = que->array[que->head];
    que->head = (que->head + 1) % que->size;
    que->numofelem--;
    return res;
}

void push(Queue* que, Node* input){
    if(que->numofelem == que->size)
        return;
    que->tail = (que->tail + 1) % que->size;
    que->array[que->tail] = input;
    que->numofelem++;
}

int isEmpty(Queue* que){
    if(que->numofelem == 0)
        return 1;
    return 0;
}

void printQueue(Queue* que){
    for(int i = 0; i < que->size; i++){
        if(que->array[i])
            printf("QUE ELEM N%d: %s\n", i, que->array[i]->name);
    }
}

//List
void printpathList(List* path){
    List* tmp = path;
    while (1){
        printf("%s ", tmp->str);
        if(tmp->next) {
            printf("--> ");
            tmp = tmp->next;
        }
        else
            break;
    }
    printf("\n");
}

void listPush(List** head, char* info){
    List* tmp = listNode(info);
    tmp->next = *head;
    (*head) = tmp;
}