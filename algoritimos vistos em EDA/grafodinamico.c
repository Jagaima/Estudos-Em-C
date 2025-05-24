#include <stdio.h>
#include <stdlib.h>

// Estrutura para nó da lista de adjacência
typedef struct No {
    int vertice;
    struct No *prox;
} No;

// Estrutura para grafo dinâmico
typedef struct {
    No **lista_adj;
    int num_vertices;
} GrafoDinamico;

No* criar_no(int v) {
    No *novo = (No*)malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = NULL;
    return novo;
}

void inicializar_grafo_dinamico(GrafoDinamico *g, int n) {
    g->num_vertices = n;
    g->lista_adj = (No**)malloc(n * sizeof(No*));
    for (int i = 0; i < n; i++) {
        g->lista_adj[i] = NULL;
    }
}

void adicionar_aresta_dinamica(GrafoDinamico *g, int origem, int destino) {
    // Adiciona destino na lista de origem
    No *novo = criar_no(destino);
    novo->prox = g->lista_adj[origem];
    g->lista_adj[origem] = novo;
    
    // Para grafo não direcionado, adiciona origem na lista de destino
    novo = criar_no(origem);
    novo->prox = g->lista_adj[destino];
    g->lista_adj[destino] = novo;
}

void imprimir_grafo_dinamico(GrafoDinamico *g) {
    printf("Grafo (Lista de Adjacencia):\n");
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i);
        No *atual = g->lista_adj[i];
        while (atual) {
            printf("%d ", atual->vertice);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void liberar_grafo(GrafoDinamico *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista_adj[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->lista_adj);
}

int main() {
    GrafoDinamico g;
    inicializar_grafo_dinamico(&g, 5);
    
    adicionar_aresta_dinamica(&g, 0, 1);
    adicionar_aresta_dinamica(&g, 0, 2);
    adicionar_aresta_dinamica(&g, 1, 3);
    adicionar_aresta_dinamica(&g, 2, 4);
    
    imprimir_grafo_dinamico(&g);
    
    liberar_grafo(&g);
    
    return 0;
}