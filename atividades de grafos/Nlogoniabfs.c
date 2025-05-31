#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int v;
    struct No* proximo;
} No;

No* criarNo(int v) {
    No* novo = (No*) malloc(sizeof(No));
    novo->v = v;
    novo -> proximo = NULL;
    return novo;
}

// FUnção BFS inicial. 

void bfs(int inicio, bool visitado[], No* adj[], int V) {
    int *fila = (int*) malloc(V * sizeof(int));
    int inicioF = 0;
    int FimF = 0;

    visitado[inicio] = true;
    fila[FimF++] = inicio;

    while (inicioF < FimF) {
        int u = fila[inicioF++];
        for (No* ptr = adj[u]; ptr != NULL; ptr = ptr ->proximo){
            int v = ptr->v;
            if (!visitado[v]) {
                visitado[v] = true;
                fila[FimF++] = v;
            }

        }
    }
    free(fila);
}


int main() {
    int V;
    if (scanf("%d", &V) != 1) return 0;  // lê número de cidades

    // Cria vetor de listas de adjacência
    No** adj = (No**) malloc(V * sizeof(No*));
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }

    // Lê pares até EOF
    int v, w;
    while (scanf("%d %d", &v, &w) == 2) {
        // aresta v -> w
        No* novo = criarNo(w);
        novo->proximo = adj[v];
        adj[v] = novo;
        // aresta w -> v
        novo = criarNo(v);
        novo->proximo = adj[w];
        adj[w] = novo;
    }

    // Vetor de visitados
    bool* visitado = (bool*) calloc(V, sizeof(bool));

    int componentes = 0;
    // Para cada vértice, se não visitado, inicia DFS e conta nova componente
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            componentes++;
            bfs(i, visitado, adj, V);
        }
    }

    printf("%d\n", componentes);

    // Libera memória
    for (int i = 0; i < V; i++) {
        No* ptr = adj[i];
        while (ptr) {
            No* tmp = ptr;
            ptr = ptr->proximo;
            free(tmp);
        }
    }
    free(adj);
    free(visitado);

    return 0;
}