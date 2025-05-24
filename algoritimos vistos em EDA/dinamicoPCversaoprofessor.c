#include <stdio.h>
#include <stdlib.h>

// mesmo já tendo feito, tive dificuldades de implementar a versão do professor mesmo ela parecendo relativamente mais simples, aqui está o mais próximo que cheguei eu acho.

typedef struct {
    int V;      // número de vértices
    int E;      // número de arestas
    int **adj;  // matriz de adjacência
} Graph;

// Cria e inicializa um grafo com V vértices e 0 arestas
Graph* GRAPHInit(int V) {
    Graph *G = malloc(sizeof(*G));
    G->V = V;
    G->E = 0;

    // aloca vetor de ponteiros
    G->adj = malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        // para cada linha, aloca V inteiros e zera
        G->adj[i] = calloc(V, sizeof(int));
    }
    return G;
}

// Adiciona aresta de mão dupla entre v e w
void GRAPHAddEdge(Graph *G, int v, int w) {
    if (G->adj[v][w] == 0) {  // só conta uma vez
        G->adj[v][w] = 1;
        G->adj[w][v] = 1;
        G->E++;                 
    }
}

void GRAPHRemove(Graph *G, int v, int w) {
    if (G->adj[v][w] == 1) {
        G->adj[v][w] = 0;
        G->adj [w][v] = 0;   
        G->E--;  
    }

}

// Imprime lista de adjacência
void GRAPHShow(Graph *G) {
    printf("Grafo: V = %d, E = %d\n", G->V, G->E);
    for (int v = 0; v < G->V; v++) {
        printf("%2d:", v);
        for (int w = 0; w < G->V; w++) {
            if (G->adj[v][w]) {
                printf(" %d", w);
            }
        }
        printf("\n");
    }
}

// Libera toda a memória do grafo
void GRAPHFree(Graph *G) {
    for (int i = 0; i < G->V; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G);
}

int main() {
    Graph *G = GRAPHInit(5);

    GRAPHAddEdge(G, 0, 1);
    GRAPHAddEdge(G, 0, 2);
    GRAPHAddEdge(G, 1, 3);
    GRAPHAddEdge(G, 2, 4);

    GRAPHShow(G);
    GRAPHFree(G);
    return 0;
}
