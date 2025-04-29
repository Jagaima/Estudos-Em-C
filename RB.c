#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK} Color;

typedef struct node {
    int valor;
    Color cor;
    struct node *esq;
    struct node *dir;
    struct node *pai;
} Node;

Node* criarno(int valor) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->valor = valor;
    novoNo->cor = RED;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->pai = NULL;
    return novoNo;}

Node* minimo(Node* node) {
    while (node->esq != NULL){
        node = node->esq;
    }
    return node;
}

void leftrote (Node** raiz, Node* x) {
    Node* y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL) {
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == NULL) 
        *raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    
    y->esq = x;
    x->pai = y;
}

void rightrote (Node** raiz, Node* x) {
    Node* y = x->esq;
    x->esq = y->dir;
    if (y->dir != NULL) {
        y->dir->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->dir)
        x->pai->dir =y;
    else 
        x->pai->esq = y;

    y->dir =x;
    x->pai =y;
}

void fixinsert (Node** raiz, Node* z) {
}