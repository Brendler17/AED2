#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define INFINITE 9999

// Estrutura para aresta
typedef struct {
  int origin, destination, weight;
} Edge;

// Estrutura para Union-Find
int father[MAX], rank[MAX];

// Função de comparação para o QSort
int compareEdges(const void *a, const void *b) {
  Edge *edgeA = (Edge *)a;
  Edge *edgeB = (Edge *)b;
  return edgeA->weight - edgeB->weight;
}

// Encontra a raiz de um vértice ou conjunto
int find(int vertice) {
  if (father[vertice] != vertice) {
    father[vertice] = find(father[vertice]);
  }

  return father[vertice];
}

// Faz a união dos conjuntos
void unionSets(int u, int v) {
  int rootU = find(u);
  int rootV = find(v);

  if (rootU == rootV) return;  // Já estão no mesmo conjunto

  if (rank[rootU] > rank[rootV]) {
    father[rootV] = rootU;
  } else if (rank[rootU] < rank[rootV]) {
    father[rootU] = rootV;
  } else {
    father[rootV] = rootU;  // Escolhe rootU como raiz
    rank[rootU]++;          // Incrementa o rank da nova raiz
  }
}

void showMenu() {
  printf("\n------- MENU -------");
  printf("\n1. Inserir Grafo");
  printf("\n2. Gerar Grafo");
  printf("\n3. Exibir Matriz de Adjacência");
  printf("\n4. Calcular o Menor Caminho");
  printf("\n5. Calcular a Árvore Geradora Mínima");
  printf("\n0. Sair");
}

void freeGraph(int **graph, int numberOfLines) {
  for (int line = 0; line < numberOfLines; line++) {
    free(graph[line]);
  }
  free(graph);
}

int main() {
  int **graph = NULL;
  int userOption, numberOfVertices;
  FILE *file;

  do {
    showMenu();
    printf("\n\nDigite a opção desejada: ");
    scanf("%d", &userOption);

    switch (userOption) {
      case 1: {
        printf("Digite o número de vértices (máximo %d): ", MAX);
        scanf("%d", &numberOfVertices);

        // Alocar a matriz de adjacência
        graph = (int **)malloc(numberOfVertices * sizeof(int *));
        if (graph == NULL) {
          printf("\nErro ao alocar memória!\n");
          return 1;
        }
        for (int line = 0; line < numberOfVertices; line++) {
          graph[line] = (int *)malloc(numberOfVertices * sizeof(int));
          if (graph[line] == NULL) {
            printf("\nErro ao alocar memória!\n");
            freeGraph(graph, line);
            return 1;
          }
        }

        printf("Digite a matriz de adjacência (0 se não houver aresta): \n");
        for (int i = 0; i < numberOfVertices; i++) {
          for (int j = 0; j < numberOfVertices; j++) {
            scanf("%d", &graph[i][j]);
            if (i == j) {
              // Diagonal: custo de ir para si mesmo é sempre zero
              graph[i][j] = 0;
            } else if (graph[i][j] == 0) {
              // Zero fora da diagonal significa SEM ARESTA, atribuir INFINITO
              graph[i][j] = INFINITE;
            }
            // Se não é diagonal e o valor não é zero, significa que há uma aresta válida com peso informado
          }
        }

        system("clear");
        printf("\nMatriz gerada com sucesso!\n");

      } break;
      case 2: {
        // Abrir o arquivo
        file = fopen("graph.txt", "r");
        if (file == NULL) {
          printf("\nErro ao abrir o arquivo!\n");
          return 1;
        }

        fscanf(file, "%d", &numberOfVertices);

        // Alocar a matriz de adjacência
        graph = (int **)malloc(numberOfVertices * sizeof(int *));
        if (graph == NULL) {
          printf("\nErro ao alocar memória!\n");
          return 1;
        }
        for (int line = 0; line < numberOfVertices; line++) {
          graph[line] = (int *)malloc(numberOfVertices * sizeof(int));
          if (graph[line] == NULL) {
            printf("\nErro ao alocar memória!\n");
            freeGraph(graph, line);
            return 1;
          }
        }

        // Preencher matriz de adjacência
        for (int i = 0; i < numberOfVertices; i++) {
          for (int j = 0; j < numberOfVertices; j++) {
            fscanf(file, "%d", &graph[i][j]);

            if (i == j) {
              graph[i][j] = 0;
            } else if (graph[i][j] == 0) {
              graph[i][j] = INFINITE;
            }
          }
        }

        system("clear");
        printf("\nMatriz gerada com sucesso!\n");
        fclose(file);

      } break;
      case 3: {
        if (graph == NULL) {
          system("clear");
          printf("\nMatriz de adjacência está vazia!\n");
          break;
        }

        system("clear");
        printf("\n-------------- Matriz de Adjacência --------------\n");
        for (int i = 0; i < numberOfVertices; i++) {
          for (int j = 0; j < numberOfVertices; j++) {
            if (graph[i][j] == INFINITE) {
              printf("INF\t");
            } else {
              printf("%d\t", graph[i][j]);
            }
          }
          printf("\n");
        }
        printf("--------------------------------------------------\n");
      } break;
      case 4: {
        if (graph == NULL) {
          system("clear");
          printf("\nMatriz de adjacência está vazia!\n");
          break;
        }

        int distances[numberOfVertices], visited[numberOfVertices], previous[numberOfVertices];
        int minDistance, next;
        int origin, destination;

        printf("Informe o vértice de origem (0 a %d): ", numberOfVertices - 1);
        scanf("%d", &origin);
        printf("Informe o vértice de destino (0 a %d): ", numberOfVertices - 1);
        scanf("%d", &destination);

        // Inicializar estruturas
        for (int i = 0; i < numberOfVertices; i++) {
          distances[i] = INFINITE;
          visited[i] = 0;
          previous[i] = -1;
        }

        distances[origin] = 0;

        for (int vertice = 0; vertice < numberOfVertices - 1; vertice++) {
          minDistance = INFINITE;

          // Encontrar vértice com menor distância nos vértices não visitados
          for (int i = 0; i < numberOfVertices; i++) {
            if (!visited[i] && distances[i] <= minDistance) {
              minDistance = distances[i];
              next = i;
            }
          }

          // Marca o vértice como visitado
          visited[next] = 1;

          // Atualiza distâncias dos vizinhos do vértice atual
          for (int i = 0; i < numberOfVertices; i++) {
            if (!visited[i] && graph[next][i] && distances[next] + graph[next][i] < distances[i]) {
              distances[i] = distances[next] + graph[next][i];
              previous[i] = next;
            }
          }
        }

        if (distances[destination] == INFINITE) {
          system("clear");
          printf("\nNão existe caminho entre %d e %d.", origin, destination);
        } else {
          system("clear");
          printf("\nDistância mínima de %d para %d: %d", origin, destination, distances[destination]);
          printf("\nCaminho: ");

          int path[numberOfVertices];
          int current = destination;
          int counter = 0;

          // Adiciona o current no path até chegar na origem, movendo-se para o predecessor
          while (current != -1) {
            path[counter++] = current;
            current = previous[current];
          }

          // Percorre o path de trás para frente, imprimindo cada vértice do caminho
          for (int i = counter - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i != 0) printf(" -> ");
          }
          printf("\n");
        }

      } break;
      case 5: {
        if (graph == NULL) {
          system("clear");
          printf("\nMatriz de adjacência está vazia!\n");
          break;
        }

        Edge edges[(numberOfVertices * (numberOfVertices - 1)) / 2];
        int numberOfEdges = 0;

        // Transformar matriz de adjacência em lista de arestas
        for (int i = 0; i < numberOfVertices; i++) {
          for (int j = i + 1; j < numberOfVertices; j++) {
            edges[numberOfEdges].origin = i;
            edges[numberOfEdges].destination = j;
            edges[numberOfEdges].weight = graph[i][j];
            numberOfEdges++;
          }
        }

        // Ordenar as arestas pelo peso -> menor para o maior
        qsort(edges, numberOfEdges, sizeof(Edge), compareEdges);

        // Inicializar estruturas
        for (int i = 0; i < numberOfVertices; i++) {
          father[i] = i;
          rank[i] = 0;
        }

        system("clear");
        printf("\nArestas da AGM:\n");
        int totalWeight = 0;

        for (int i = 0; i < numberOfEdges; i++) {
          int u = edges[i].origin;
          int v = edges[i].destination;

          if (find(u) != find(v)) {
            printf("(%d , %d) -> peso %d\n", u, v, edges[i].weight);
            totalWeight += edges[i].weight;
            unionSets(u, v);
          }
        }

        printf("Peso total da AGM: %d\n", totalWeight);

      } break;
      case 0: {
        printf("Saindo...\n\n");
        return 0;
      } break;
      default:
        break;
    }
  } while (userOption != 0);

  freeGraph(graph, numberOfVertices);

  return 0;
}