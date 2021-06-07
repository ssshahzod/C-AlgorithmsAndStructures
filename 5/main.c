#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"

// вывод пути и проверка корректности пути
// создание одинаковых ребер
// при удалении первой вершины первый элемент списка не удаляется
//

int main(){
    int graphsize = 1;
    int x = 0, res = 0;
    Node* graph = NULL, *tmp;
    Queue *queue = createQueue(QSIZE);
    List* path;
    FILE* output;
    FILE* input;
    printMenu(1);
    do {
        x = intchoice(9);
        switch (x) {
            case (1):
                if(x == 1){ //input vertice
                    tmp = createNode();
                    graph = graphInput(graph, tmp);
                    push(queue, tmp);
                }
            case (2):
                if(x == 2){//create edge
                    casecreateEdges(graph, 1);
                }
            case(3):
                if(x == 3){//search1
                    char* str2 = strInput("Input name of vertex to search from: ");
                    char* str = strInput("Input name of the vertex to search for: ");
                    if((path = bfs(graph, str, str2)) != NULL)
                        printpathList(path);
                    else
                        printf("Path doesnt exist!\n");
                    free(str);
                    free(str2);
                }
            case(4):
                if(x == 4){//search2
                }
            case(5):
                if(x == 5){//search3
                    output = fopen("output.txt", "w");
                    saveToFile(graph, output);
                    fclose(output);
                }
            case(6):
                if(x == 6){//graph output
                    tmp = graph;
                    printLists(tmp);

                    /*output = fopen("output.txt", "w");
                    printDot(graph, output);
                    fclose(output);*/
                }
            case(7):
                if(x == 7){//delete vertix
                    if(!graph){
                        printf("Graph is empty!\n");
                        break;
                    }
                    char* str = strInput("Input name of the vertix: ");
                    deleteVertix(graph, str);
                    free(str);
                }
            case(8):
                if(x == 8){//delete edge
                    casecreateEdges(graph, 0);
                }
            case(9):
                if(x == 9){ //read from file
                    char* str = strInput("Input name of the file: ");
                    input = fopen(str, "r");
                    if(input == NULL)
                        printf("Error while openning file!\n");
                    else
                        graph = readfromFile(input);
                    if(graph == NULL)
                        printf("Not correct file!\n");

                    free(str);
                    fclose(input);
                }
        }
    } while(x);
}

void casecreateEdges(Node* graph, int m){
    int err = 0;
    char* name1 = strInput("Input name of 1st vertex: ");
    char* name2 = strInput("Input name of the 2nd vertex: ");
    if(m == 1)
        err = createEdges(graph, name1, name2);
    else if(m == 0)
        deleteEdge(graph, name1, name2);
    if(err == 30)
        printf("Edge already exist!\n");

    else if(err == -1)
        printf("Vertex %s doesnt exist!\n", name1);

    else if(err == -2)
        printf("Vertex %s doesnt exist!\n", name2);

    free(name1);
    free(name2);

}

void printMenu(int mode){
    if (mode == 1){
        printf("0. Exit\n");
        printf("1. Input element.\n");
        printf("2. Create edge.\n");
        printf("3. Check for the path (BFS).\n");
        printf("4. \n");
        printf("5. \n");
        printf("6. Print graph.\n");
        printf("7. Delete vertix.\n");
        printf("8. Delete edge.\n");
        printf("9. Read graph from file.\n");
    }
    else if(mode == 2){

    }
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
            exit(-1);
        }
    } while(x < 1 || n > max || n < 0);
    return n;
}