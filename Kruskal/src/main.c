#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// Estrutura para representar uma aresta
typedef struct {
  int origem, destino, peso;
} Aresta;

// Estrutura para Union-Find (Disjoint Set)
int pai[MAX];
int rank[MAX];

void inicializarConjuntos(int n) {
  for (int i = 0; i < n; i++) {
    pai[i] = i;
    rank[i] = 0;
  }
}

int encontrar(int v) {
  if (pai[v] != v) pai[v] = encontrar(pai[v]);
  return pai[v];
}

void unir(int u, int v) {
  int raizU = encontrar(u);
  int raizV = encontrar(v);

  if (raizU == raizV) return;

  if (rank[raizU] < rank[raizV]) {
    pai[raizU] = raizV;
  } else if (rank[raizU] > rank[raizV]) {
    pai[raizV] = raizU;
  } else {
    pai[raizV] = raizU;
    rank[raizU]++;
  }
}

// Função de comparação para qsort (ordenar por peso crescente)
int compararArestas(const void *a, const void *b) {
  Aresta *arestaA = (Aresta *)a;
  Aresta *arestaB = (Aresta *)b;
  return arestaA->peso - arestaB->peso;
}

void kruskal(int grafo[MAX][MAX], int n) {
  Aresta arestas[MAX * MAX];
  int contArestas = 0;

  // Transformar matriz de adjacência em lista de arestas
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {  // j=i+1 para não repetir arestas
      if (grafo[i][j] != 0) {
        arestas[contArestas].origem = i;
        arestas[contArestas].destino = j;
        arestas[contArestas].peso = grafo[i][j];
        contArestas++;
      }
    }
  }

  // Ordenar arestas pelo peso
  qsort(arestas, contArestas, sizeof(Aresta), compararArestas);

  inicializarConjuntos(n);

  printf("Arestas da AGM:\n");
  int pesoTotal = 0;

  for (int i = 0; i < contArestas; i++) {
    int u = arestas[i].origem;
    int v = arestas[i].destino;

    if (encontrar(u) != encontrar(v)) {
      printf("%d -- %d (peso %d)\n", u, v, arestas[i].peso);
      pesoTotal += arestas[i].peso;
      unir(u, v);
    }
  }

  printf("Peso total da AGM: %d\n", pesoTotal);
}

int main() {
  int grafo[MAX][MAX], n;

  printf("Informe o numero de vertices (maximo %d): ", MAX);
  scanf("%d", &n);

  printf("Informe a matriz de adjacencia (0 se nao houver aresta):\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &grafo[i][j]);
    }
  }

  kruskal(grafo, n);

  return 0;
}
