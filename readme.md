# Análise Comparativa de Algoritmos de Ordenação — AED II

Este repositório contém o projeto desenvolvido para a disciplina de **Algoritmos e Estruturas de Dados II** na **Universidade Federal de Itajubá (UNIFEI)**. O objetivo principal é a implementação, análise de desempenho e coleta de métricas de diversos algoritmos de ordenação aplicados sobre uma estrutura de dados de requisições.

---

## 👥 Integrantes do Grupo 7
* **Davi Lorena**
* **Theo Fellipe**
* **Diego Nadur**
* **João Pedro**

---

## 📑 Visão Geral do Projeto

O sistema foi projetado para avaliar a eficiência de algoritmos de ordenação clássicos em diferentes cenários de entrada. Para isso, utilizamos uma estrutura chamada `Request`, que simula dados reais (contendo ID de usuário e ID de documento), permitindo observar como o custo de movimentação e comparação de structs impacta o tempo de execução.

### Algoritmos Implementados
O projeto contempla algoritmos de complexidade quadrática, logarítmica e estocástica:
- **Bubble Sort (Inteligente):** Implementação com flag de parada prematura.
- **Selection Sort:** Minimização do número de trocas.
- **Insertion Sort:** Eficiente para pequenos conjuntos e dados quase ordenados.
- **Merge Sort:** Algoritmo estável baseado em "Dividir e Conquistar".
- **Quick Sort:** Utilizando o particionamento de Lomuto e pivô fixo.
- **Heap Sort:** Baseado na estrutura de dados Heap Máxima.
- **Shell Sort:** Extensão do Insertion Sort com gaps variáveis.
- **Bozo Sort:** Algoritmo estocástico utilizado para análise de limites computacionais.

---

## 📂 Arquitetura de Arquivos

A organização do código segue padrões de modularização em C:

### 核心 (Núcleo)
* **`ordenacao.h`**: O contrato do sistema. Define a estrutura `request`, a struct de `metricas` (que armazena comparações, trocas e tempo) e as assinaturas de todas as funções de ordenação e utilitários.
* **`ordenacao.c`**: O motor do projeto. Contém a lógica detalhada de cada algoritmo, bem como as funções de geração de datasets (Aleatório, Ordenado, Inverso e Quase Ordenado).

### 🧪 Ambientes de Teste
* **`main.c`**: Executável de análise em lote. Realiza baterias de testes automáticos com vetores de **1.000 a 10.000.000** de elementos. É aqui que a mágica da coleta de dados estatísticos acontece.
* **`mainTestesUnicos.c`**: Um ambiente de sandbox interativo. Permite ao desenvolvedor ou avaliador configurar manualmente um cenário específico (tamanho, semente de aleatoriedade e tipo de vetor) para depuração.
* **`bozoSort.c`**: Um script isolado para o algoritmo BozoSort. Devido à sua natureza ineficiente, ele possui uma lógica própria para detectar o "limite de paciência" do hardware, testando o máximo de elementos que o algoritmo consegue ordenar em um tempo razoável.

### 🛠️ Build e Bibliotecas
* **`CMakeLists.txt`**: Arquivo de configuração do CMake para garantir que o projeto seja compilável em diferentes sistemas operacionais.
* **`lib/lib.a`**: Arquivo de biblioteca estática contendo os objetos compilados das funções de ordenação, facilitando a portabilidade dos algoritmos.

---

## 📊 Metodologia de Análise de Desempenho

Para mitigar variações térmicas de hardware e ruídos do sistema operacional, adotamos o seguinte rigor:
1.  **Métricas Coletadas**: Contagem exata de Comparações, Movimentações de memória e Tempo de Execução (ms).
2.  **Repetições**: Para os casos de dados Aleatórios e Quase Ordenados, o sistema executa **30 iterações** e calcula a média aritmética dos resultados.
3.  **Cenários de Stress**:
    * **Ordenado**: Melhor caso para Insertion/Bubble.
    * **Inverso**: Pior caso para a maioria dos algoritmos quadráticos.
    * **Quase Ordenado**: Testa a adaptabilidade dos algoritmos.
    * **Aleatório**: Caso médio estatístico.

---

## 🚀 Como Compilar e Rodar

### Requisitos
- Compilador C (GCC ou Clang)
- CMake 3.10+

### Passo a passo
1.  Gere os arquivos de build:
    ```bash
    cmake -S . -B build
    ```
2.  Compile o projeto:
    ```bash
    cmake --build build
    ```
3.  Execute os testes:
    ```bash
    ./build/teste
    ```

---

> **Nota:** Este projeto foi desenvolvido com foco em performance e precisão estatística para fins acadêmicos.
