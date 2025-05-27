#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para lista de adjacência
typedef struct No {
    int vertice;
    struct No* proximo;
} No;

// Função para criar um novo nó da lista
No* criarNo(int v) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->proximo = NULL;
    return novo;
}

// DFS recursiva
void dfs(int u, bool visitado[], No* adj[]) {
    visitado[u] = true;
    for (No* ptr = adj[u]; ptr != NULL; ptr = ptr->proximo) {
        int v = ptr->vertice;
        if (!visitado[v]) {
            dfs(v, visitado, adj);
        }
    }
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
            dfs(i, visitado, adj);
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