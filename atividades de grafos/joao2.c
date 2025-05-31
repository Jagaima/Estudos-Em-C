// segunda versão da segunda atividade envolvendo a cidade de Nlogônia porque a primeira está passando com 99p e eu não sei o motivo

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura de lista de adjacência para representar estradas
typedef struct No {
    int cidade;         // índice da cidade
    struct No* prox;    // próxima aresta na lista
} No;

// Cria um novo nó apontando para 'cidade'
No* criarNo(int cidade) {
    No* novo = malloc(sizeof(No));
    novo->cidade = cidade;
    novo->prox = NULL;
    return novo;
}

// Insere estrada bidirecional entre u e v
void inserirAresta(No* adj[], int u, int v) {
    No* nodoV = criarNo(v);
    nodoV->prox = adj[u];
    adj[u] = nodoV;
    
    No* nodoU = criarNo(u);
    nodoU->prox = adj[v];
    adj[v] = nodoU;
}

// DFS: marca componente, conta tamanho e acha menor cidade
void dfs(int u, No* adj[], bool visit[], int compIndex[], int id, int *tamanho, int *menor) {
    visit[u] = true;
    compIndex[u] = id;
    (*tamanho)++;
    if (u < *menor) *menor = u;
    
    for (No* p = adj[u]; p != NULL; p = p->prox) {
        if (!visit[p->cidade]) {
            dfs(p->cidade, adj, visit, compIndex, id, tamanho, menor);
        }
    }
}

int main() {
    int V, J;
    if (scanf("%d %d", &V, &J) != 2) return 0;

    // Aloca vetores
    No** adj = calloc(V, sizeof(No*));      // listas de adjacência
    bool* visit = calloc(V, sizeof(bool));  // flag de visitado
    int* compIndex = malloc(V * sizeof(int));
    int* compSize = malloc(V * sizeof(int));
    int* compMin = malloc(V * sizeof(int));

    // Leitura das estradas
    int u, v;
    while (scanf("%d %d", &u, &v) == 2) {
        inserirAresta(adj, u, v);
    }

    // Descobre componentes conectados
    int totalComps = 0;
    for (int cidade = 0; cidade < V; cidade++) {
        if (!visit[cidade]) {
            int tam = 0;
            int menor = cidade;
            dfs(cidade, adj, visit, compIndex, totalComps, &tam, &menor);
            compSize[totalComps] = tam;
            compMin[totalComps] = menor;
            totalComps++;
        }
    }

    // Dados da componente do João
    int compJoao = compIndex[J];
    int sizeJoao = compSize[compJoao];

    // Encontra componente estritamente maior
    int bestSize = 0;
    int bestMin = V;
    for (int i = 0; i < totalComps; i++) {
        int tam = compSize[i];
        int mn = compMin[i];
        if (tam > sizeJoao && (tam > bestSize || (tam == bestSize && mn < bestMin))) {
            bestSize = tam;
            bestMin = mn;
        }
    }

    // Impressão do resultado
    if (bestSize > 0) {
        printf("Vamos para %d\n", bestMin);
    } else {
        // Se está isolado (tamanho 1 e sem estradas)
        if (sizeJoao == 1 && adj[J] == NULL)
            printf("Fique em casa\n");
        else
            printf("Bora pra estrada\n");
    }

    // Libera memória
    for (int i = 0; i < V; i++) {
        No* p = adj[i];
        while (p) {
            No* tmp = p;
            p = p->prox;
            free(tmp);
        }
    }
    free(adj);
    free(visit);
    free(compIndex);
    free(compSize);
    free(compMin);

    return 0;
}
