#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structs do ordenacao.h 

typedef struct metricas {
unsigned long long comparacoes, movimentacoes;
} met;

typedef struct request {
int user_id, chegada;
} r;

// Funções para gerar vetores 

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

// Método para realizar o teste dos algoritmos 

void testar_algoritmo(const char* nome, int tam, int id_algoritmo) {
    char* cenarios[] = {"Aleatorio", "Ordenado", "Decrescente", "Quase Ordenado"};
    int c, // Para iterar nos cenarios
    repeticoes; // Para a média de repetições 

    // Variáveis para coleta de métricas e tempo
    clock_t inicio, fim;
    double tempo, mediaTempo, mediaComparacoes, mediaMovimentacoes, totalTempo = 0.0;
    met* m = NULL;
    met *mParaParametro = NULL; // Para algoritmos que pedem parâmetro manual
    r* vetor; 
    unsigned long long totalComparacoes = 0, totalMovimentacoes = 0;

    printf("\nAlgoritmo: %s \nTamanho: %d\n", nome, tam);

    // Define a média de repetições para teste 
    for (c = 0; c < 4; c++) {
        if(c == 0 || c == 3) {
            repeticoes = 30;
        } else {
            repeticoes = 1;
        }

        for (int i = 0; i < repeticoes; i++) {
            // Chamada dos métodos de geração criados acima
            if (c == 0) vetor = gerar_aleatorio(tam);
            else if (c == 1) vetor = gerar_ordenado(tam);
            else if (c == 2) vetor = gerar_decrescente(tam);
            else vetor = gerar_quase_ordenado(tam);

            // Algoritmos que requerem métricas
            if (id_algoritmo == 4 || id_algoritmo == 5) {
                mParaParametro = alocaMetricas();
                if (!mParaParametro) {
                    liberaVetor(vetor);
                    return;
                }
            }

            // Inicia a contagem de tempo 
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

            // Finaliza o teste e coleta as métricas
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

        mediaTempo = totalTempo / repeticoes;
        mediaComparacoes = (double) totalComparacoes / repeticoes;
        mediaMovimentacoes = (double) totalMovimentacoes / repeticoes;

        printf("[%s] Média tempo: %.2fms | Média comp: %.0f | Média mov: %.0f\n",
               cenarios[c], mediaTempo, mediaComparacoes, mediaMovimentacoes);
    }
}

int main() {
    int tamanhos[] = {1000, 10000};
    int tam2[] = {100000, 1000000, 10000000};
    int t, tam;

    for (int i = 0; i < 2; i++) {
        t = tamanhos[i];

        testar_algoritmo("Bolha Inteligente", t, 1);
        testar_algoritmo("Selecao", t, 2);
        testar_algoritmo("Insercao", t, 3);
        testar_algoritmo("MergeSort", t, 4);
        testar_algoritmo("QuickSort Tradicional", t, 5);
        testar_algoritmo("ShellSort", t, 6);
        testar_algoritmo("HeapSort", t, 7);
    }

    // Separando os métodos que rodaram com vetores de tamanho maior 
    for (int i = 0; i < 3; i++) {
        tam = tam2[i];

        testar_algoritmo("MergeSort", tam, 4);
        testar_algoritmo("ShellSort", tam, 6);
        testar_algoritmo("HeapSort", tam, 7);
    }

    return 0;
}