#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define INFINITE 9999

void showMenu() {
  printf("\n------- MENU -------");
  printf("\n1. Inserir Grafo");
  printf("\n2. Gerar Grafo");
  printf("\n3. Exibir Matriz de Adjacência");
  printf("\n0. Sair");
}

void freeGraph(int **graph, int numberOfLines) {
  for (int line = 0; line < numberOfLines; line++) {
    free(graph[line]);
  }
  free(graph);
}

int main() {
  int **graph;
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

        // Alocar ponteiro para linhas
        graph = (int **)malloc(numberOfVertices * sizeof(int *));

        for (int i = 1; i <= numberOfVertices; i++) {
          // Alocar cada linha (colunas)
          graph[i] = (int *)malloc(numberOfVertices * sizeof(int));
        }

        printf("Digite a matriz de adjacência (0 se não houver aresta): \n");
        for (int i = 1; i <= numberOfVertices; i++) {
          for (int j = 1; j <= numberOfVertices; j++) {
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
        graph = (int **)malloc(sizeof(int *) * numberOfVertices);
        for (int line = 1; line <= numberOfVertices; line++) {
          graph[line] = (int *)malloc(sizeof(int) * numberOfVertices);
        }

        for (int i = 1; i <= numberOfVertices; i++) {
          for (int j = 1; j <= numberOfVertices; j++) {
            fscanf(file, "%d", &graph[i][j]);

            if (i == j) {
              graph[i][j] = 0;
            } else if (graph[i][j] == 0) {
              graph[i][j] = INFINITE;
            }
          }
        }

        printf("\nMatriz gerada com sucesso!\n");
        fclose(file);

      } break;
      case 3: {
        printf("\n-------Matriz de Adjacência-------\n");
        for (int i = 1; i <= numberOfVertices; i++) {
          for (int j = 1; j <= numberOfVertices; j++) {
            if (graph[i][j] == INFINITE) {
              printf("INF\t");
            } else {
              printf("%d\t", graph[i][j]);
            }
          }
          printf("\n");
        }
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