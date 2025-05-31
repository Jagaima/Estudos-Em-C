// atividade sobre Nlogônica, usa DFS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_V 5000

// Estrutura para lista de adjacência
typedef struct No {
    int vertice;
    struct No* proximo;
} No;

typedef struct Componente {
    int id; 
    int tamanho;
    int menorV;
    
} Componente;

// Função para criar um novo nó da lista
No* criarNo(int v) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->proximo = NULL;
    return novo;
}





// DFS recursiva
void dfs(int u, bool visitado[], No* adj[], int componente_id[], Componente* comp) {
    visitado[u] = true;
    componente_id[u] = comp->id;
    comp->tamanho += 1;
    if(u < comp->menorV){
    comp->menorV = u;}

    for (No* ptr = adj[u]; ptr != NULL; ptr = ptr->proximo) {
        int v = ptr->vertice;
        if (!visitado[v]) {
            dfs(v, visitado, adj, componente_id, comp);
        }
    }
}

int main() {
    int V, J;
    if (scanf("%d %d", &V, &J) != 2) return 1;  // lê número de cidades

    // Cria vetor de listas de adjacência
    No** adj = (No**) malloc(V * sizeof(No*));
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }

    // Lê pares até EOF
    int v, w;
    while (scanf("%d %d", &v, &w) == 2) {
        if (v >= V || w >= V || v < 0 || w < 0) continue;
        // aresta v -> w
        No* novo = criarNo(w);
        novo->proximo = adj[v];
        adj[v] = novo;
        // aresta w -> v
        novo = criarNo(v);
        novo->proximo = adj[w];
        adj[w] = novo;
    }

    if (adj[J] == NULL) {
        printf("Fique em casa\n");
        goto fim;
    }

    // Vetor de visitados
    bool* visitado = (bool*) calloc(V, sizeof(bool));
    int* componente_id = (int*) malloc(V * sizeof(int));
    Componente maior = {.tamanho = 0, .menorV = MAX_V};
    Componente Joao = {.id = -1, .tamanho = 0,};
    int id = 0;
    // Para cada vértice, se não visitado, inicia DFS e conta nova componente
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            Componente atual = {.id = id, .tamanho = 0, .menorV = i};
            dfs(i, visitado, adj, componente_id, &atual);

            if (componente_id[J] == id)
            Joao = atual;

            if (atual.tamanho > maior.tamanho || (atual.tamanho == maior.tamanho && atual.menorV < maior.menorV)) {maior = atual;}
            id++;
        }
    }

    if (Joao.tamanho == maior.tamanho) {
        printf("Bora pra estrada\n");
    } else {
        printf("Vamos para %d\n", maior.menorV);
    }


    fim:

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