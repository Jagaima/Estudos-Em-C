#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura para grafo estático
typedef struct {
    int vertices[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} GrafoEstatico;

void inicializar_grafo_estatico(GrafoEstatico *g, int n) {
    g->num_vertices = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->vertices[i][j] = 0;
        }
    }
}

void adicionar_aresta_estatica(GrafoEstatico *g, int origem, int destino) {
    g->vertices[origem][destino] = 1;
    g->vertices[destino][origem] = 1; // Para grafo não direcionado
}

void imprimir_grafo_estatico(GrafoEstatico *g) {
    printf("Grafo (Matriz de Adjacencia):\n");
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < g->num_vertices; j++) {
            if (g->vertices[i][j]) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

int main() {
    GrafoEstatico g;
    inicializar_grafo_estatico(&g, 5);
    
    adicionar_aresta_estatica(&g, 0, 1);
    adicionar_aresta_estatica(&g, 0, 2);
    adicionar_aresta_estatica(&g, 1, 3);
    adicionar_aresta_estatica(&g, 2, 4);
    
    imprimir_grafo_estatico(&g);
    
    return 0;
}