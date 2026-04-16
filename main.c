#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct metricas {
unsigned long long comp, moviment;
} met;

typedef struct request {
int id, x;
} r;


int main() {
    clock_t inicio, fim;
    double tempo_gasto;
    int tamanho = 1000;
    
    inicio = clock();
    //metodos de ordenacao
    fim = clock();
    tempo_gasto = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;

    return 0;
    
}