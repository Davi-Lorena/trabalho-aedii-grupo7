#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>

// Estruturas usadas para armazenar métricas e informações de chegada
struct metricas {
    unsigned long long comparacoes, movimentacoes;
};

struct request {
    int user_id, chegada; 
};

// Verifica se o algoritmo mantém a ordem original entre elementos com a mesma chave
int verificar_estabilidade(const char* nome, int tam, int id_algoritmo) {
    int K = 10;
    int i, j;
    int orig_i, orig_j;
    int* pos_original;
    int estavel = 1;
    int violacoes = 0;
    r tmp;
    r* vetor_original;
    r* vetor_teste;
    met* m = NULL;
    met* mParam = NULL;

    // Cria vetor de teste com chaves repetidas e posição original de chegada
    vetor_original = malloc(tam * sizeof(r));
    if (!vetor_original) return -1;

    for (i = 0; i < tam; i++) {
        vetor_original[i].user_id = i % K;
        vetor_original[i].chegada = i;
    }

    // Embaralha o vetor para testar estabilidade em ordem não trivial
    srand(42);
    for (i = tam - 1; i > 0; i--) {
        j = rand() % (i + 1);
        tmp = vetor_original[i];
        vetor_original[i] = vetor_original[j];
        vetor_original[j] = tmp;
    }

    pos_original = malloc(tam * sizeof(int));
    if (!pos_original) { free(vetor_original); return -1; }
    for (i = 0; i < tam; i++)
        pos_original[vetor_original[i].chegada] = i;

    vetor_teste = malloc(tam * sizeof(r));
    if (!vetor_teste) { free(pos_original); free(vetor_original); return -1; }
    for (i = 0; i < tam; i++)
        vetor_teste[i] = vetor_original[i];

    // Executa o algoritmo de ordenação escolhido e coleta métricas
    switch(id_algoritmo) {
        case 1: m = bolhaInteligente(vetor_teste, tam); break;
        case 2: m = selecao(vetor_teste, tam);          break;
        case 3: m = insercao(vetor_teste, tam);         break;
        case 4: mParam = alocaMetricas();
                mergeSort(vetor_teste, 0, tam - 1, mParam);
                m = mParam; break;
        case 5: mParam = alocaMetricas();
                quickSort(vetor_teste, 0, tam - 1, mParam);
                m = mParam; break;
        case 6: m = shellSort(vetor_teste, tam); break;
        case 7: m = heapSort(vetor_teste, tam);  break;
    }

    // Verifica se a estabilidade foi mantida comparando a ordem original de chegada
    for (i = 0; i < tam - 1; i++) {
        for (j = i + 1; j < tam; j++) {
            if (vetor_teste[j].user_id != vetor_teste[i].user_id) break;

            orig_i = pos_original[vetor_teste[i].chegada];
            orig_j = pos_original[vetor_teste[j].chegada];

            if (orig_i > orig_j) {
                estavel = 0;
                violacoes++;
            }
        }
    }

    printf("[Estabilidade] %-20s (tam=%6d): %s", nome, tam, estavel ? "ESTAVEL" : "NAO ESTAVEL");
    if (!estavel) printf(" (%d violacoes)", violacoes);
    printf("\n");

    if (mParam) liberaMetricas(mParam);
    else if (m) liberaMetricas(m);
    free(vetor_teste);
    free(pos_original);
    free(vetor_original);

    return estavel;
}

// Ponto de entrada: verifica a estabilidade de cada algoritmo listado
int main() {
    int tam = 100;

    printf("===== VERIFICACAO DE ESTABILIDADE =====\n\n");

    verificar_estabilidade("Bolha Inteligente", tam, 1);
    verificar_estabilidade("Selecao",           tam, 2);
    verificar_estabilidade("Insercao",          tam, 3);
    verificar_estabilidade("MergeSort",         tam, 4);
    verificar_estabilidade("QuickSort",         tam, 5);
    verificar_estabilidade("ShellSort",         tam, 6);
    verificar_estabilidade("HeapSort",          tam, 7);

    return 0;
}