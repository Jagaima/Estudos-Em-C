#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int v;
    struct node *next;
} *link;

typedef struct Edge {
    int v;
    int w;
} Edge;

typedef struct {
    int V, E;
    link *adj;
} Graph;

static link NEW(int v, link next) {
    link x = malloc(sizeof *x);
    if (!x) { perror("malloc"); exit(1); }
    x->v = v;
    x->next = next;
    return x;
}

Graph *GRAPHInit(int V) {
    Graph *G = malloc(sizeof *G);
    if (!G) { perror("malloc"); exit(1); }
    G->V = V;
    G->E = 0;
    G->adj = malloc(V * sizeof(link));
    if (!G->adj) { perror("malloc"); exit(1); }
    for (int v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHInsert(Graph *G, Edge E) {
    int v = E.v, w = E.w;
    // Verifica se os vértices estão dentro dos limites
    if (v < 0 || v >= G->V || w < 0 || w >= G->V) {
        fprintf(stderr, "Erro: vértice inválido %d-%d\n", v, w);
        return;
    }
    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[w]);
    G->E++;
}

void GRAPHFree(Graph *G) {
    for (int v = 0; v < G->V; v++) {
        link p = G->adj[v];
        while (p) {
            link t = p->next;
            free(p);
            p = t;
        }
    }
    free(G->adj);
    free(G);
}

int main() {
    int N, M, J;
    if (scanf("%d %d %d", &N, &M, &J) != 3) {
        fprintf(stderr, "Erro ao ler N, M, J\n");
        return 1;
    }

    Graph *G = GRAPHInit(N);

    for (int i = 0; i < N; i++) {
        int Aj;
        if (scanf("%d", &Aj) != 1) {
            fprintf(stderr, "Erro ao ler Aj para o nó %d\n", i);
            GRAPHFree(G);
            return 1;
        }
        for (int j = 0; j < Aj; j++) {
            int vizinho;
            if (scanf("%d", &vizinho) != 1) {
                fprintf(stderr, "Erro ao ler vizinho %d do nó %d\n", j, i);
                GRAPHFree(G);
                return 1;
            }
            // Verifica se o vizinho é válido antes de inserir
            if (vizinho < 0 || vizinho >= N) {
                fprintf(stderr, "Vizinho inválido %d para o nó %d\n", vizinho, i);
                continue; // Pula vizinhos inválidos
            }
            Edge E = {i, vizinho};
            GRAPHInsert(G, E);
        }
    }

    char *unsafe = calloc(N, sizeof(char));
    if (!unsafe) { perror("calloc"); GRAPHFree(G); return 1; }

    for (int i = 0; i < M; i++) {
        int loc;
        if (scanf("%d", &loc) != 1) {
            fprintf(stderr, "Erro ao ler local %d\n", i);
            free(unsafe);
            GRAPHFree(G);
            return 1;
        }
        if (loc < 0 || loc >= N) {
            fprintf(stderr, "Local inválido %d\n", loc);
            continue; // Pula locais inválidos
        }
        unsafe[loc] = 1;
        for (link t = G->adj[loc]; t != NULL; t = t->next) {
            if (t->v >= 0 && t->v < N) {
                unsafe[t->v] = 1;
            }
        }
    }

    while (J--) {
        int q;
        if (scanf("%d", &q) != 1) {
            fprintf(stderr, "Erro ao ler consulta\n");
            free(unsafe);
            GRAPHFree(G);
            return 1;
        }
        if (q >= 0 && q < N && unsafe[q])
            printf("Eu vou estar la\n");
        else
            printf("Nao vou estar la\n");
    }

    free(unsafe);
    GRAPHFree(G);

    return 0;}