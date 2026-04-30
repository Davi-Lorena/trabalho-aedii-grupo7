#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Programa de testes automatizados de algoritmos em diferentes cenários de vetor
int main() {
    int opcao, tam, tipoVetor;
    unsigned int seed, s_atual;
    char resposta;
    clock_t t1;
    int cenarios[] = {1, 2, 3, 4};
    char *nomes[] = {"ALEATORIO", "ORDENADO", "DECRESCENTE", "QUASE ORDENADO"};
    int c, i, tipo, limite;
    r *vetor = NULL;
    met *m = NULL;
    double tempo_acumulado = 0;

    // Lê o tamanho e a seed usados para gerar os vetores de teste
    printf("Tamanho do VETOR:");
    scanf("%d", &tam);

    printf("SEED desejada:");
    scanf("%d", &seed);

    do {
        printf("\n---TESTES ---\n");
        printf("1. Bolha Inteligente\n");
        printf("2. Selecao\n");
        printf("3. Insercao\n");
        printf("4. MergeSort\n");
        printf("5. QuickSort\n");
        printf("6. ShellSort\n");
        printf("7. HeapSort\n");
        printf("8. BozoSort (NAO TESTEM COM VETORES MAIS DE 10!)\n");
        printf("0. Sair\n");
        printf("Escolha o algoritmo: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;
        if (opcao < 0 || opcao > 8) {
            printf("OPCAO INCORRETA, DIGITE UM NUMERO DE 1 - 8!\n");
            continue;
        }

        // Percorre cada cenário de vetor e define quantas execuções serão feitas
        for (c = 0; c < 4; c++) {
            tipo = cenarios[c];
            limite = (tipo == 1 || tipo == 4) ? 30 : 1;
            tempo_acumulado = 0;

            printf("\n--- %s (%d execucoes) ---", nomes[c], limite);

            for (i = 0; i < limite; i++) {
                s_atual = seed + i;
                vetor = NULL;
                m = NULL;

                // Gera o vetor de teste de acordo com o cenário atual
                if (tipo == 1) vetor = geraAleatorios(tam, s_atual);
                else if (tipo == 2) vetor = geraOrdenados(tam, s_atual);
                else if (tipo == 3) vetor = geraDecrescente(tam, s_atual);
                else if (tipo == 4) vetor = geraQuaseOrdenados(tam, s_atual, 10);

                m = NULL;
                t1 = clock();

                // Executa o algoritmo selecionado e registra métricas
                if (opcao == 1) m = bolhaInteligente(vetor, tam);
                else if (opcao == 2) m = selecao(vetor, tam);
                else if (opcao == 3) m = insercao(vetor, tam);
                else if (opcao == 4) { m = alocaMetricas(); mergeSort(vetor, 0, tam - 1, m); }
                else if (opcao == 5) { m = alocaMetricas(); quickSort(vetor, 0, tam - 1, m); }
                else if (opcao == 6) m = shellSort(vetor, tam);
                else if (opcao == 7) m = heapSort(vetor, tam);
                else if (opcao == 8) m = bozoSort(vetor, tam);

                t1 = clock() - t1;
                tempo_acumulado += ((double)t1) / CLOCKS_PER_SEC * 1000;
                
                if (i == limite - 1) {
                    imprimeMetricas(m);
                    printf("TEMPO MEDIO: %.2f ms\n", tempo_acumulado / limite);
                }

                liberaMetricas(m);
                liberaVetor(vetor);
                if (limite > 1) printf(".");
            }
        }

        printf("\nDeseja rodar outro algoritmo? (0 para sair): ");
        scanf("%d", &opcao);

    } while (opcao != 0);

    return 0;
}