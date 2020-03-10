#include <stdio.h>
#include <stdlib.h>      
#include <time.h>      
#include <string.h>

#define MAX_NUMBER 10000
#define SIZE 10000

/**
* Funções de ordenação
*/
int * bubbleSort(int elements[]);
int * insertionSort(int arr[]);
int * selectionSort(int elements[]);
void swap(int *xp, int *yp);

/** 
* Esta é a única função interessante
* Centraliza o processo de medir e trabalha com chamada dinamica a função em C.
*/
void  measure(int elements[SIZE],char algorithm[], int * (*f)(int*));
  
void showValues(int elements[SIZE]);
void startValues(int elements[SIZE]);

int main() {
	int values[SIZE];

	startValues(values);
	
	measure(values,"Insercao",insertionSort);
	measure(values,"Selecao" ,selectionSort);
	measure(values,"Bolha"   ,bubbleSort);

}

int * bubbleSort(int arr[])  {  
    int i, j;  
    int n = SIZE;
    
    for (i = 0; i < n-1; i++)      
       for (j = 0; j < n-i-1; j++)  
         if (arr[j] > arr[j+1])  
              swap(&arr[j], &arr[j+1]);
              
	return arr;  
}

int * insertionSort(int arr[]) { 
    int i, key, j, n; 
    n = SIZE;
    for (i = 1; i < n; i++) { 
        key = arr[i]; 
        j = i - 1; 
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
    return arr;  
} 

int * selectionSort(int arr[]) {  
    int i, j, min_idx;  
    int n;
    
    n = SIZE;
  
    for (i = 0; i < n-1; i++)  {  
        min_idx = i;  
        for (j = i+1; j < n; j++)  
           if (arr[j] < arr[min_idx])  
               min_idx = j;  
        swap(&arr[min_idx], &arr[i]);  
   }  
   return arr;  
}  



void showValues(int elements[SIZE]) {
   int i;
   for( i = 0; i < SIZE; i++) {
       printf("%d -> %d \n",i,elements[i]);
   }
}

void measure(int elements[SIZE],char algorithm[], int * (*f)(int*)) {
	// Aloca a memória com a cópia do conjunto original
    size_t temp_size = sizeof(*(elements)) * (SIZE);
    clock_t begin,end;
    double time_spent;
    
    int * copy = malloc(temp_size);
    memcpy(copy, elements, temp_size);
    
    // executa a ordenação e mede -> usa a função de forma dinâmica
    
    begin = clock();
    
    (*f)(copy);

    end = clock();
    
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s,%d,%fs \n",algorithm, SIZE, time_spent);
    free( copy );
}

void startValues(int elements[SIZE]) {
   int i;
   srand (time(NULL));	  
   for( i = 0; i < SIZE; i++) {
       elements[i] = rand() % MAX_NUMBER;	
   }
}

void swap(int *xp, int *yp)  {  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
