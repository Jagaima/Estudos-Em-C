#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int valor;
    struct node *esq;
    struct node *dir;
} Node;


Node* criarNo(int valor) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->valor = valor;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó.\n");
        exit(1);
    }

    return novoNo;
}


Node* inserir (Node* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    if (valor < raiz ->valor) {
        raiz -> esq = inserir(raiz->esq, valor);
    }

    else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }

    else return raiz; 

    return raiz;
}

Node* buscar(Node* raiz, int valor) {

    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscar (raiz->esq, valor);
    }
    if (valor > raiz->valor) {
        return buscar(raiz->dir, valor);
    }
}


void imprimir_em_ordem(Node *raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esq);  // Visita a subárvore esquerda
        printf("%d ", raiz->valor);         // Imprime o valor da raiz
        imprimir_em_ordem(raiz->dir);   // Visita a subárvore direita
    }
}

int main (){
    Node* raiz = NULL;
    int valor;



    printf("Digite os valores para inserir na árvore (digite -1 para parar):\n");
    while (1) {
        scanf("%d", &valor);
        if (valor == -1) {
            break;
        }
        raiz = inserir(raiz, valor);
    }

    printf("Digite o valor a ser buscado:\n");
    scanf("%d", &valor);
    Node* resultado = buscar(raiz, valor);

    if (resultado != NULL) {
        printf("Valor %d encontrado na árvore.\n", resultado->valor);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valor);
    }

    printf("Árvore em ordem: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    return 0;
}

