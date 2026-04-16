#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct metricas {
unsigned long long comparacoes, movimentacoes;
} met;

typedef struct request {
int user_id, chegada;
} r;

// --- 1. FUNÇÕES PARA GERAR VETORES ---

r* gerar_aleatorio(int tam) {
    return geraAleatorios(tam, 0);
}

r* gerar_ordenado(int tam) {
    return geraOrdenados(tam, 0); 
}

r* gerar_decrescente(int tam) {
    return geraDecrescente(tam, 0); 
}

r* gerar_quase_ordenado(int tam) {
    return geraQuaseOrdenados(tam, 0, 10); 
}

void testar_algoritmo(const char* nome, int tam, int id_algoritmo) {
    char* cenarios[] = {"Aleatorio", "Ordenado", "Decrescente", "Quase Ordenado"};
    int c, // Para iterar nos cenarios
    repeticoes; // Para a média de repetições 

    // Variáveis para coleta de métricas e tempo
    clock_t inicio, fim;
    double tempo;
    met* m = NULL;
    met *mParaParametro = NULL; // Para algoritmos que pedem parâmetro manual
    r* vetor; 

    printf("\nAlgoritmo: %s \nTamanho: %d\n", nome, tam);

    for (c = 0; c < 4; c++) {
        if(c == 0 || c == 3) {
            repeticoes = 30;
        } else {
            repeticoes = 1;
        }

        unsigned long long totalComparacoes = 0;
        unsigned long long totalMovimentacoes = 0;
        double totalTempo = 0.0;

        for (int i = 0; i < repeticoes; i++) {
            // Chamada dos métodos de geração criados acima
            if (c == 0) vetor = gerar_aleatorio(tam);
            else if (c == 1) vetor = gerar_ordenado(tam);
            else if (c == 2) vetor = gerar_decrescente(tam);
            else vetor = gerar_quase_ordenado(tam);

            if (id_algoritmo == 4 || id_algoritmo == 5) {
                mParaParametro = alocaMetricas();
                if (!mParaParametro) {
                    liberaVetor(vetor);
                    return;
                }
            }

            inicio = clock();

            // Chamadas na ordem do .h
            switch(id_algoritmo) {
                case 1: m = bolhaInteligente(vetor, tam); break;
                case 2: m = selecao(vetor, tam); break;
                case 3: m = insercao(vetor, tam); break;
                case 4:
                    mergeSort(vetor, 0, tam - 1, mParaParametro);
                    m = mParaParametro;
                    break;
                case 5:
                    quickSort(vetor, 0, tam - 1, mParaParametro);
                    m = mParaParametro;
                    break;
                case 6: m = shellSort(vetor, tam); break;
                case 7: m = heapSort(vetor, tam); break;
            }

            fim = clock();
            tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
            totalTempo += tempo;
            totalComparacoes += m->comparacoes;
            totalMovimentacoes += m->movimentacoes;

            if (mParaParametro != NULL) {
                liberaMetricas(mParaParametro);
                mParaParametro = NULL;
            }
            liberaVetor(vetor);
        }

        double mediaTempo = totalTempo / repeticoes;
        double mediaComparacoes = (double) totalComparacoes / repeticoes;
        double mediaMovimentacoes = (double) totalMovimentacoes / repeticoes;

        printf("[%s] Média tempo: %.2fms | Média comp: %.0f | Média mov: %.0f\n",
               cenarios[c], mediaTempo, mediaComparacoes, mediaMovimentacoes);
    }
}

int main() {
    int tamanhos[] = {1000, 10000, 100000, 1000000, 10000000}; 

    for (int i = 0; i < 5; i++) {
        int t = tamanhos[i];

        // Chamadas uma a uma conforme aparecem no arquivo.h 
        testar_algoritmo("Bolha Inteligente", t, 1);
        testar_algoritmo("Selecao", t, 2);
        testar_algoritmo("Insercao", t, 3);
        testar_algoritmo("MergeSort", t, 4);
        testar_algoritmo("QuickSort Tradicional", t, 5);
        testar_algoritmo("ShellSort", t, 6);
        testar_algoritmo("HeapSort", t, 7);
    }

    return 0;
}