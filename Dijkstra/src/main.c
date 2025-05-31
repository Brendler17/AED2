#include <limits.h>
#include <stdio.h>

#define MAX 20
#define INFINITO 9999

void dijkstra(int grafo[MAX][MAX], int n, int origem, int destino) {
  int distancia[MAX], visitado[MAX], anterior[MAX];
  int i, j, minimo, prox;

  for (i = 0; i < n; i++) {
    distancia[i] = INFINITO;
    visitado[i] = 0;
    anterior[i] = -1;
  }

  distancia[origem] = 0;

  for (i = 0; i < n - 1; i++) {
    minimo = INFINITO;
    for (j = 0; j < n; j++) {
      if (!visitado[j] && distancia[j] <= minimo) {
        minimo = distancia[j];
        prox = j;
      }
    }

    visitado[prox] = 1;

    for (j = 0; j < n; j++) {
      if (!visitado[j] && grafo[prox][j] && distancia[prox] + grafo[prox][j] < distancia[j]) {
        distancia[j] = distancia[prox] + grafo[prox][j];
        anterior[j] = prox;
      }
    }
  }

  if (distancia[destino] == INFINITO) {
    printf("Nao existe caminho entre %d e %d\n", origem, destino);
  } else {
    printf("Distancia minima de %d para %d: %d\n", origem, destino, distancia[destino]);
    printf("Caminho: ");
    int caminho[MAX];
    int count = 0;
    int atual = destino;
    while (atual != -1) {
      caminho[count++] = atual;
      atual = anterior[atual];
    }
    for (i = count - 1; i >= 0; i--) {
      printf("%d", caminho[i]);
      if (i != 0) printf(" -> ");
    }
    printf("\n");
  }
}

int main() {
  int grafo[MAX][MAX], n, i, j;
  int origem, destino;

  printf("Informe o numero de vertices (maximo %d): ", MAX);
  scanf("%d", &n);

  printf("Informe a matriz de adjacencia (0 se nao houver aresta):\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &grafo[i][j]);
      if (i == j) grafo[i][j] = 0;
      if (grafo[i][j] == 0 && i != j) grafo[i][j] = INFINITO;
    }
  }

  printf("Informe o vertice de origem (0 a %d): ", n - 1);
  scanf("%d", &origem);
  printf("Informe o vertice de destino (0 a %d): ", n - 1);
  scanf("%d", &destino);

  dijkstra(grafo, n, origem, destino);

  return 0;
}
