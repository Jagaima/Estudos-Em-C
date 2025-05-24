// estudando versão da live do professor (que já é parecida com a que eu acabei montando, mas estou fazendo conforme vejo a aula)

#include <stdio.h>
#include <stdlib.h>

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
    int v;
    Graph *G = malloc(sizeof *G);
    if (!G) { perror("malloc"); exit(1); }
    G->V = V; G->E = 0;
    G->adj = malloc(V * sizeof(link));
    if (!G->adj) { perror("malloc"); exit(1); }
    for (v = 0; v<v; v++){
        G->adj[v]=NULL;
    }
    return G;
}

void GRAPHInsert(Graph *G, Edge E) {        //colocar no inicio que custa o(1)
    int v = E.v ; int w = E.w;
    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[w]);
    G->E++;
}


int GRAPHEdges (Edge a[], Graph *G) {
    int v, E=0; link t;
    for (v =0; v < G->V; v++){
        for(t = G->adj[v]; t != NULL; t = t->next ){
            if(v<t->v) a[E++] = (Edge){v,t->v};
            
        }

    }
    return E;
}



void GRAPHRemove(Graph *G, int v, int w) {
    // implementar remoção de v de adj[w] e de w de adj[v], e G->E-- se achar.
    // (fica um pouco mais verboso que em matriz, mas segue a mesma ideia)
}

void GRAPHShow(Graph *G) {
    printf("Grafo: V=%d, E=%d\n", G->V, G->E);
    for (int v = 0; v < G->V; v++) {
        printf("%2d:", v);
        for (link p = G->adj[v]; p; p = p->next)
            printf(" %d", p->v);
        printf("\n");
    }
}

void GRAPHFree(Graph *G) {
    for (int v = 0; v < G->V; v++) {
        link p = G->adj[v], t;
        while (p) { t = p; p = p->next; free(t); }
    }
    free(G->adj);
    free(G);
}

int main() {
    Graph *G = GRAPHInit(5);
    GRAPHInsert(G, (Edge){0, 1});
    GRAPHInsert(G, (Edge){0, 2});
    GRAPHInsert(G, (Edge){1, 3});
    GRAPHInsert(G, (Edge){2, 4});
    GRAPHShow(G);
    GRAPHFree(G);
    return 0;
}
