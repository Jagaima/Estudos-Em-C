// red black eft-leaning tree

#include <stdio.h>
#include <stdlib.h>

typedef enum {red, black} Color;

typedef struct node {
    int valor;
    Color cor;
    struct node *esq, *dir; 
} Node; 

Node* criarnode(int valor, Color cor) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->valor = valor;
    novoNo->cor = red;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

int ehRaiz(Node* no){
    return (no->cor == black);
}

int ehVermelho(Node* no) {
    return (no != NULL && no->cor == red);
}

Node* rotacionarEsquerda(Node* raiz, Node* x){
    Node* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    y->cor = x->cor;
    x->cor = red;
    return y;
}

Node* rotacionarDireita (Node* raiz, Node* x){
    Node* y = x->esq;
    x->esq = y->dir;
    y->dir = x;
    y->cor = x->cor;
    x->cor = red;
    return y;
}

void trocarCores(Node* x) {
    x->cor = red;
    x->esq->cor =black;
    x->dir->cor =black;
}



Node* inserir (Node* raiz, int valor) {
    if (raiz == NULL) {
        return criarnode(valor, red);
    }
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    } else {
        return raiz; // Não insere valores duplicados
    }
    if (ehVermelho(raiz->dir) && !ehVermelho(raiz->esq)){
        raiz = rotacionarEsquerda(raiz, raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq)){
        raiz = rotacionarDireita(raiz, raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir)){
        trocarCores(raiz);
    }
    return raiz;  
}

Node* busca(Node* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return busca(raiz->esq, valor);
    } else {
        return busca (raiz->dir, valor);
    }
}

void imprime(Node* raiz){
    if (raiz == NULL) {
        return;
    }
    imprime(raiz->esq);
    printf("%d", raiz->valor);
    imprime(raiz->dir);
}

int main() {
    Node* raiz = NULL;
    int valor;

    printf("Digite os valores para inserir na árvore (digite -1 para parar):\n");
    while (1) {
        scanf("%d", &valor);
        if (valor == -1) {
            break;
        }
        raiz = inserir(raiz, valor);
        raiz->cor = black;
    }

    printf("Valores na árvore em ordem: ");
    imprime(raiz);
    printf("\n");

    return 0;
}
