#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line{ //Line of the matrix
	int n; //number of elements
	int *a; 
} Line;

typedef struct Matrix{ //matrix
	int lines; //number of lines
	Line * matr;
} Matrix;

int savescanf(int *a);
void output(const char *msg, Matrix a);
void arrayclean(Matrix *a);
int input(Matrix *rm);
int matrixprocess(Matrix a);



int main(){
	Matrix matr = {0, NULL}; 

	if (input(&matr) == 0){ //reading matrix
		printf("%s\n", "Конец файла!");
		return 1;
	}

	output("Введенная матрица", matr);
	matrixprocess(matr);
	arrayclean(&matr);
	return 0;
}



int savescanf(int *a){
	int n;
	n = scanf("%d", a);
	if (n == 0){ 
		while(getchar() != '\n'){
		}
		return -1;
	}
	if (n < 0) 
		return 0; //End of file
	return 1;
}

void arrayclean(Matrix *a){
	int i;
	for (i = 0; i < a->lines; ++i)
		 free(a->matr[i].a);
	free(a->matr);
	a->lines = 0;
	a->matr = NULL;
}

int matrixprocess(Matrix a){
	int i, j, fl = 0;
	int *p, *m, *n;
	printf("Полученный вектор:\n b = (");
	for (i = 0; i < a.lines; ++i){ 
		p = a.matr[i].a; 
		//watching all strings

		for (j = 0; j < a.matr[i].n; ++j, ++p){
			if(j == 0)
				n = p; //first element
			if((*p < 0) && (fl == 0)) //negative number in the string
				fl = 1;

			if (j == a.matr[i].n - 1)
				m = p; //last elements
		}
		if(fl == 1)
			printf(" %d", *m);
		if(fl == 0)
			printf(" %d", *n);
		fl = 0;
	}
	printf(" )\n"); 
}

int input(Matrix *rm){
	const char *pr = ""; 
	int m;
	int i, j, sv;
	int *p;

	do{ //input number of lines
		printf("%s\n", pr);
		printf("Введите количество строк в матрице: ");
		pr = "Неккоректный ввод!";
		if ((sv = savescanf(&m)) == 0){
			return 0;
		}
	} while ((m < 1) || (sv < 1));
	rm->lines = m; //number of lines
	//allocating memory for struct array and cleaning it
	rm->matr = (Line *)calloc(m, sizeof(Line));


	for (i = 0; i < rm->lines; ++i){ //for every line

		pr = "";
		do{
			printf("%s\n", pr);
			printf("Введите количество элементов в строке %d : ", i + 1);
			pr = "Неккоректный ввод!";
			if ((sv = savescanf(&m)) == 0){
				rm->lines = i; 
				arrayclean(rm);
				return 0; 
			}
		} while ((m < 1) || (sv < 1));
		rm->matr[i].n = m;

		p = (int *)calloc(m, sizeof(int)); //allocating memory for one element
		rm->matr[i].a = p;

		printf("Введите элементы матрицы для строки %d:\t\n", i + 1);
		j = 0;
		do{
			printf("%s %d :", "Введите элемент", (j + 1));
			if ((sv = savescanf(p)) == 0){
				rm->lines = i + 1; 
				arrayclean(rm);
				return 0;
			}
			if (sv == -1){
				printf("Неккоректный ввод!\n");
				j--;
				p--;
			}
			++j;
			++p;
		} while((j < m));
	}
	return 1;
}

void output(const char *msg, Matrix a){
	int i, j;
	int *p;
	printf("%s:\n", msg);
	for (i = 0; i < a.lines; ++i){
		p = a.matr[i].a;
		for (j = 0; j < a.matr[i].n; ++j, ++p)
			printf("%d ", *p);
		printf("\n");
	}
}
