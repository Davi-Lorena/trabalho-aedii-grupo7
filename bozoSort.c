#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structs

typedef struct metricas {
    unsigned long long comparacoes, movimentacoes;
} met;

typedef struct request {
    int user_id, chegada;
} r;

// Funções para gerar os vetores

r* gerar_aleatorio(int tam) { return geraAleatorios(tam, time(NULL)); }
r* gerar_ordenado(int tam) { return geraOrdenados(tam, 0); }
r* gerar_decrescente(int tam) { return geraDecrescente(tam, 0); }
r* gerar_quase_ordenado(int tam) { return geraQuaseOrdenados(tam, time(NULL), 10); }

// Algoritmo para testar o bozoSort
void testar_bozo(int tam, int tempo_limite_segundos) {
    char* cenarios[] = {"Aleatorio", "Ordenado", "Decrescente", "Quase Ordenado"};
    int repeticoes = 5;
    clock_t global_inicio = clock();
    unsigned long long totalComp = 0, totalMov = 0;
    double totalTempo = 0.0;
    int concluidos = 0;
    clock_t inicio, fim;
    met *m;
    r *vetor;

    printf("\nTestando BozoSort | Tamanho: %d\n", tam);

    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < repeticoes; i++) {

            if (((double)(clock() - global_inicio) / CLOCKS_PER_SEC) > tempo_limite_segundos) {
                break;
            }

            if (c == 0) vetor = gerar_aleatorio(tam);
            else if (c == 1) vetor = gerar_ordenado(tam);
            else if (c == 2) vetor = gerar_decrescente(tam);
            else vetor = gerar_quase_ordenado(tam);

            inicio = clock();
            m = bozoSort(vetor, tam);
            fim = clock();

            totalTempo += ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
            totalComp += m->comparacoes;
            totalMov += m->movimentacoes;
            concluidos++;

            liberaVetor(vetor);

        }

        if (concluidos > 0) {
            printf("[%s] Media: %.2fms | Comp: %.0llu | Mov: %.0llu | (%d/%d execucoes)\n",
                   cenarios[c], totalTempo / concluidos, totalComp / concluidos, totalMov / concluidos, concluidos, repeticoes);
        } else {
            printf("[%s] TIMEOUT: O algoritmo excedeu o tempo limite.\n", cenarios[c]);
        }
    }
}

// Método para descobrir o maior tamanho de vetor 
void descobrir_limite_5min() {
    printf("\nBuscando maior tamanho para 5 minutos (300s)\n");
    int tam = 1;
    double tempo = 0;
    clock_t inicio, fim;
    r *vetor;

    while (tempo < 300.0) {
        tam++;
        vetor = gerar_aleatorio(tam);

        inicio = clock();
        bozoSort(vetor, tam);
        fim = clock();

        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tamanho %d: %.2fs\n", tam, tempo);

        liberaVetor(vetor);

        if (tempo > 300.0) {
            printf("\n>>> O maior tamanho suportado em menos de 5 min foi: %d\n", tam - 1);
            break;
        }

        if (tam > 15) {
            printf("Interrompendo busca por Complexidade Fatorial.\n");
            break;
        }
    }
}

int main() {
    int tamanhos[] = {4, 8, 10, 12};

    for (int i = 0; i < 4; i++) {
        testar_bozo(tamanhos[i], 30);
    }

    descobrir_limite_5min();

    return 0;
}