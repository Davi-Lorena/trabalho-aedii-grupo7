#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"
#include <time.h>

//STRUCTS
struct metricas{
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
};

struct request {
    int user_id;
    int chegada;
};

//OPERAÇÕES COM METRICAS

met *alocaMetricas() {
    met *m = (met *)malloc(sizeof(met));
    if (m != NULL) {
        m->comparacoes = 0;
        m->movimentacoes = 0;
    }
    return m;
}

void liberaMetricas(met *m) {
    free(m);
}

void imprimeMetricas(met *m) {
    printf("Comparacoes: %llu\nMovimentacoes: %llu\n", m->comparacoes, m->movimentacoes);
}

void salvaMetricas(met *m, char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar as métricas.\n");
        return;
    }
    fprintf(arq, "Comparacoes: %llu\nMovimentacoes: %llu\n", m->comparacoes, m->movimentacoes);
    fclose(arq);
}

//TIPOS DE VETORES

r *geraAleatorios(int tam, unsigned int seed) {
    if (seed == 0) srand(time(NULL));
    else srand(seed);

    r *vet = (r *) malloc(tam * sizeof(r));
    for (int i = 0; i < tam; i++) {
        vet[i].user_id = rand() % 1000;
        vet[i].chegada = i;
    }
    return vet;
}

r *geraOrdenados(int tam, unsigned int seed) {
    r *vet = geraAleatorios(tam, seed);
    met *mTemp = alocaMetricas();


    mergeSort(vet, 0, tam - 1, mTemp);

    liberaMetricas(mTemp);
    return vet;
}

r *geraQuaseOrdenados(int tam, unsigned int seed, unsigned int porc) {
    r *vet = geraOrdenados(tam, seed);

    int qtdTrocas = (tam * porc) / 100;
    for (int i = 0; i < qtdTrocas; i++) {
        int p1 = rand() % tam;
        int p2 = rand() % tam;
        r aux = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = aux;
    }
    return vet;
}

r *geraDecrescente(int tam, unsigned int seed) {

    r *vet = geraAleatorios(tam, seed);

    met *mTemp = alocaMetricas();
    mergeSort(vet, 0, tam - 1, mTemp);
    liberaMetricas(mTemp);

    int i, j;
    r aux;
    for (i = 0, j = tam - 1; i < j; i++, j--) {
        aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
    }

    return vet;
}

//OPERAÇÕES COM VETOES

void imprimeVet(r *vet, int tam) {
    for (int i = 0 ; i < tam ; i++) {
        printf("%d - %d\n", vet[i].user_id, vet[i].chegada);
    }
}

void salvaVetor(r *vet, int tam, char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar o vetor.\n");
        return;
    }
    for (int i = 0; i < tam; i++) {
        fprintf(arq, "%d\t%d\n", vet[i].user_id, vet[i].chegada);
    }
    fclose(arq);
}

void liberaVetor(r *vet) {
    free(vet);
}


//METODOS DE ORDENAÇÃO


met *bolhaInteligente(r *vet, int tam) {
    met *m = alocaMetricas();
    r aux;
    int i,j,ordenado;
    for (i = 0 ; i < tam ; i++) {
        ordenado = 1;
        for (j = 0 ; j < tam - 1 - i ; j++) {
            m->comparacoes++;
            if (vet[j].user_id > vet[j + 1].user_id) {
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
                m->movimentacoes+=3;
                ordenado = 0;
            }
        }
        if (ordenado == 1) {
            break;
        }
    }
    return m;
}

met *selecao(r *vet, int tam) {
    met *m  = alocaMetricas();
    int menor;
    r aux;
    for (int i = 0 ; i < tam ; i++) {
        menor = i;
        for (int j = i + 1 ; j < tam; j++) {
            m->comparacoes++;
            if (vet[j].user_id < vet[menor].user_id) {
                menor = j;
            }
        }
        if (menor != i){
            aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
            m->movimentacoes+=3;

        }

    }
    return m;
}

met *insercao(r *vet, int tam) {
    met *m = alocaMetricas();
    for(int i = 0 ; i < tam ; i++) {
        r aux = vet[i];
        m->movimentacoes++;
        int pos = i - 1;
        while (pos >= 0) {
            m->comparacoes++;
            if (aux.user_id < vet[pos].user_id) {
                vet[pos + 1] = vet[pos];
                m->movimentacoes++;
                pos --;
            }
            else {
                break;
            }
        }
        m->movimentacoes++;
        vet[pos + 1] = aux;
    }

    return m;
}

void merge(r *vet, int inicio, int meio, int fim, met *m) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;


    r *L = (r *)malloc(n1 * sizeof(r));
    r *R = (r *)malloc(n2 * sizeof(r));


    for (int i = 0; i < n1; i++) {
        L[i] = vet[inicio + i];
        m->movimentacoes++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = vet[meio + 1 + j];
        m->movimentacoes++;
    }

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        m->comparacoes++;
        if (L[i].user_id <= R[j].user_id) {
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            j++;
        }
        m->movimentacoes++;
    }


    while (i < n1) {
        vet[k] = L[i];
        i++; k++; m->movimentacoes++;
    }
    while (j < n2) {
        vet[k] = R[j];
        j++; k++; m->movimentacoes++;
    }

    free(L);
    free(R);
}

void mergeSort(r *vet, int inicio, int fim, met *m) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(vet, inicio, meio, m);
        mergeSort(vet, meio + 1, fim, m);

        merge(vet, inicio, meio, fim, m);
    }
}



int particiona(r *vet, int inicio, int fim, met *m) {
    r pivo = vet[inicio];
    m->movimentacoes++;

    int i = inicio;

    for (int j = inicio + 1; j <= fim; j++) {
        m->comparacoes++;
        if (vet[j].user_id < pivo.user_id) {
            i++;
            r aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            m->movimentacoes += 3;
        }
    }

    r aux = vet[inicio];
    vet[inicio] = vet[i];
    vet[i] = aux;
    m->movimentacoes += 3;

    return i;
}

void quickSort(r *vet, int inicio, int fim, met *m) {
    if (inicio < fim) {
        int p = particiona(vet, inicio, fim, m);
        quickSort(vet, inicio, p - 1, m);
        quickSort(vet, p + 1, fim, m);
    }
}
/*le é uma evolução do Inserção. Em vez de comparar vizinhosssssssssssssssssssssssssssssssssss, ele compara elementos distantes (o h).
Conforme o h diminui, o vetor fica "quase ordenado", e a última passada (quando h=1) termina o serviço rapidinho.*/
met *shellSort(r *vet, int tam) {
    met *m = alocaMetricas();
    int h, i, j;
    r aux;

    for (h = tam / 2; h > 0; h /= 2) {
        for (i = h; i < tam; i++) {
            aux = vet[i];
            m->movimentacoes++;
            j = i;

            // Inserção com pulos de h
            while (j >= h) {
                m->comparacoes++;
                if (vet[j - h].user_id > aux.user_id) {
                    vet[j] = vet[j - h];
                    m->movimentacoes++;
                    j -= h;
                } else {
                    break;
                }
            }
            vet[j] = aux;
            m->movimentacoes++;
        }
    }
    return m;
}

void trocaMaior(r *vet, int pai, int tam, met *m) {
    int maior = pai;
    int esq = 2 * pai + 1;
    int dir = 2 * pai + 2;

    if (esq < tam) {
        m->comparacoes++;
        if (vet[esq].user_id > vet[maior].user_id) maior = esq;
    }

    if (dir < tam) {
        m->comparacoes++;
        if (vet[dir].user_id > vet[maior].user_id) maior = dir;
    }

    if (maior != pai) {
        r aux = vet[pai];
        vet[pai] = vet[maior];
        vet[maior] = aux;
        m->movimentacoes += 3;

        // Continua descendo para garantir a propriedade de Heap
        trocaMaior(vet, maior, tam, m);
    }
}

met *heapSort(r *vet, int tam) {
    met *m = alocaMetricas();

    // Construir a Heap Máxima (Build Heap)
    for (int i = tam / 2 - 1; i >= 0; i--) {
        trocaMaior(vet, i, tam, m);
    }

    //  Extrair elementos um por um
    for (int i = tam - 1; i > 0; i--) {
        r aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        m->movimentacoes += 3;


        trocaMaior(vet, 0, i, m);
    }
    return m;
}

met *bozoSort(r *vet, int tam) {
    met *m = alocaMetricas();
    if (m == NULL) return NULL;

    int ordenado = 0;
    while (!ordenado) {
        int i = rand() % tam;
        int j = rand() % tam;

        r aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        m->movimentacoes += 3;

        ordenado = 1; // Assume que está ordenado
        for (int k = 0; k < tam - 1; k++) {
            m->comparacoes++;
            if (vet[k].user_id > vet[k + 1].user_id) {
                ordenado = 0;
                break;
            }
        }
    }
    return m;
}