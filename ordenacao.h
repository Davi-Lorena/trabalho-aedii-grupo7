#include <stdlib.h>
#include <stdio.h>

#ifndef PROJ_ORDENACAO_H
#define PROJ_ORDENACAO_H

//STRUCTS
typedef struct metricas met;
typedef struct request r;

//METRICAS
met *alocaMetricas();
void liberaMetricas(met *m);
void imprimeMetricas(met *m);
void salvaMetricas(met *m, char *nomeArquivo);

//TIPO DE VETORES
r *geraAleatorios(int tam, unsigned int seed);
r *geraOrdenados(int tam, unsigned int seed);
r *geraQuaseOrdenados(int tam, unsigned int seed, unsigned int porc);
r *geraDecrescente(int tam, unsigned int seed);

//OPERAÇOES COM VETORES
void imprimeVet(r *vet, int tam);
void salvaVetor(r *vet, int tam, char *nomeArquivo);
void liberaVetor(r *vet);

//METODOS DE ORDENAÇÃO
met *bolhaInteligente(r *vet, int tam);
met *selecao(r *vet, int tam);
met *insercao(r *vet, int tam);
void mergeSort(r *vet, int inicio, int fim, met *m);
void merge(r *vet, int inicio, int meio, int fim, met *m);
void quickSort(r *vet, int inicio, int fim, met *m);
int particiona(r *vet, int inicio, int fim, met *m);
met *shellSort(r *vet, int tam);
met *heapSort(r *vet, int tam);
void trocaMaior(r *vet, int pai, int tam, met *m) ; //auxiliar do heapsort
met *bozoSort(r *vet, int tam);



#endif //PROJ_ORDENACAO_H
