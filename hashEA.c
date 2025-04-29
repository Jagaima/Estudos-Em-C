
// endereçamento aberto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define TABLE_SIZE 23
#define empty -1
#define deleted -2

typedef struct {
    int chave;
    int valor;
} Hitem;

Hitem Tabela [TABLE_SIZE];

void iniciaTabela() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Tabela[i].chave = empty;
        Tabela[i].valor = 0;
    }
}

int hash(int chave) {
    return chave%TABLE_SIZE;
}




void insere(int chave, int valor) {
    int i = hash(chave);
    int Maxcolisao = 0;
    while (Tabela[i].chave != empty && Tabela[i].chave != deleted && Maxcolisao < 10) {
        if (Tabela[i].chave == chave) {
            Tabela[i].valor = valor;
            return;
        }
        i = (i + 1) % TABLE_SIZE;
        Maxcolisao++;

    }
    Tabela[i].chave = chave;
    Tabela[i].valor = valor;
    return;
}

void removedor (int chave) {
    int i = hash(chave);
    int Maxcolisao = 0;
    while (Tabela[i].chave != empty && Maxcolisao < 10) {
        if (Tabela[i].chave == chave) {
            Tabela[i].chave = deleted;
            return;
        }
        i = (i + 1) % TABLE_SIZE;
        Maxcolisao++;
    
    }
}


void busca (int chave) {
    int i = hash(chave);
    int Maxcolisao = 0;
    while (Tabela[i].chave != empty && Tabela[i].chave != deleted && Maxcolisao < 10) {
        if (Tabela[i].chave == chave) {
            printf ( "Valor %d\n", Tabela[i].valor);
            return;
        }
        i = (i + 1) % TABLE_SIZE;
        Maxcolisao++;
    }
}

void imprimetudo () {
    for (int i=0; i < TABLE_SIZE; i++) {
        if (Tabela[i].chave != empty && Tabela[i].chave != deleted) {
            printf("chave: %d, valor: %d\n", Tabela[i].chave, Tabela[i].valor);
    }
}
}

int main (){
    iniciaTabela();
    
    // Testes
    insere(10, 100);
    insere(33, 200);  // Colisão com 10 (ambos hash = 10)
    insere(56, 300);  // Colisão com 10 e 33
    
    printf("Tabela após inserções:\n");
    imprimetudo();
    
    printf("\nBuscando chave 33: ");
    busca(33);
    
    printf("\nRemovendo chave 33\n");
    removedor(33);
    
    printf("\nTabela após remoção:\n");
    imprimetudo();
    
    printf("\nBuscando chave 33: ");
    busca(33);
    
    return 0;

}
