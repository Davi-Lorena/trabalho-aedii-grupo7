#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int opcao, tam, tipoVetor;
    unsigned int seed;
    char resposta;
    clock_t t1;

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
        printf("8. BozoSort (NAO TESTEM COM VETORES MAIS DE 10, O PC TRAVA TUDOOOOOOOO!!!!!!!!!!!!!!!!!!)\n");

        printf("QUALQUER outro número para Sair\n");
        printf("Escolha o algoritmo: ");
        scanf("%d", &opcao);

        r *vetor = NULL;
        if (opcao == 0) {
            break;
        }
        if (opcao < 0 || opcao > 8) {
            printf("OPCAO INCORRETA, DIGITE UM NUMERO DE 1 - 8!\n");
            continue;
        }


        printf("1. Aleatorio\n2. Ordenado\n3. Decrescente\n4. Quase Ordenado\n");
        scanf("%d", &tipoVetor);

        switch (tipoVetor) {
            case 1:
                vetor = geraAleatorios(tam, seed);
                break;
            case 2:
                vetor = geraOrdenados(tam,seed);
                break;
            case 3:
                vetor = geraDecrescente(tam,seed);
                break;
            case 4:
                vetor = geraQuaseOrdenados(tam, seed, 70);
                break;
            default:
                printf("Gerando vetor aleatorio por padrao.\n");
                vetor = geraAleatorios(tam, seed);
                break;
        }
        if (vetor == NULL) return 1;

        if (opcao == 1) {
            t1 = clock();
            met *metricasBolha = bolhaInteligente(vetor, tam);
            t1 = clock() - t1;

            printf("\nVetor Ordenado Método Bolha Inteligente:\n");
            imprimeVet(vetor, tam);
            imprimeMetricas(metricasBolha);

            salvaMetricas(metricasBolha, "metricas_ultima_execucao.txt");

            printf("BOLHA -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricasBolha);
        }

        else if (opcao == 2) {
            t1 = clock();
            met *metricaSelecao = selecao(vetor, tam);
            t1 = clock()- t1;

            printf("\nVetor Ordenado Método Seleção:\n");
            imprimeVet(vetor, tam);
            imprimeMetricas(metricaSelecao);

            salvaMetricas(metricaSelecao, "metricas_ultima_execucao.txt");

            printf("Selecao -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricaSelecao);
        }

        else if (opcao == 3) {
            t1 = clock();
            met *metricaInsercao = insercao(vetor, tam);
            t1 = clock()- t1;

            printf("\nVetor Ordenado Método Inserção:\n");
            imprimeVet(vetor, tam);
            imprimeMetricas(metricaInsercao);

            salvaMetricas(metricaInsercao, "metricas_ultima_execucao.txt");

            printf("Insercao -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricaInsercao);
        }

        else if (opcao == 4) {
            t1 = clock();
            met *metricaMarge = alocaMetricas();
            mergeSort(vetor,0,tam -1,metricaMarge);
            t1 = clock()- t1;

            printf("\nVetor Ordenado Método Merge\n");
            imprimeVet(vetor, tam);
            imprimeMetricas(metricaMarge);

            salvaMetricas(metricaMarge, "metricas_ultima_execucao.txt");

            printf("Merge -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricaMarge);
        }

        else if (opcao == 5) {
            t1 = clock();
            met *metricaQuick = alocaMetricas();
            quickSort(vetor,0,tam -1,metricaQuick);
            t1 = clock()- t1;

            printf("\nVetor Ordenado Método Quick");
            //imprimeVet(vetor, tam);
            imprimeMetricas(metricaQuick);

            salvaMetricas(metricaQuick, "metricas_ultima_execucao.txt");

            printf("Quick -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricaQuick);
        }
        else if (opcao == 6) {
            t1 = clock();
            met *metricaShell = shellSort(vetor, tam);

            t1 = clock()- t1;

            printf("\nVetor Ordenado Método Shell");
            imprimeVet(vetor, tam);
            imprimeMetricas(metricaShell);

            salvaMetricas(metricaShell, "metricas_ultima_execucao.txt");

            printf("Shell -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricaShell);
        }
        else if (opcao == 7) {
            t1 = clock();
            met *metricaHeap = heapSort(vetor, tam);
            t1 = clock()- t1;

            printf("\nVetor Ordenado Método Heap");
            imprimeVet(vetor, tam);
            imprimeMetricas(metricaHeap);

            salvaMetricas(metricaHeap, "metricas_ultima_execucao.txt");

            printf("Heap -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricaHeap);
        }
        else if (opcao == 8) {
            t1 = clock();
            met *metricaBozo = bozoSort(vetor,tam);

            t1 = clock()- t1;

            printf("\nVetor Ordenado Método Bozo");
            imprimeVet(vetor, tam);
            imprimeMetricas(metricaBozo);

            salvaMetricas(metricaBozo, "metricas_ultima_execucao.txt");

            printf("Bozo -> TEMPO : %.2f ms\n ",((double)t1) /  CLOCKS_PER_SEC *1000);
            liberaMetricas(metricaBozo);
        }

        printf("\nDeseja salvar o resultado em arquivo? (s/n): ");
        scanf(" %c", &resposta);

        if (resposta == 's' || resposta == 'S') {
            salvaVetor(vetor, tam, "vetor_ordenado.txt");
            printf("Vetor salvo em 'vetor_ordenado.txt'!\n");
        }

        liberaVetor(vetor);
    }while (opcao != 0);

    return 0;
}