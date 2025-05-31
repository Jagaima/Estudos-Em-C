// minha versão (só passa nos 2 primeiros casos)

#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

// Lista de adjacência para representar os subordinados
int subordinados[MAX][MAX];
int num_subordinados[MAX]; // quantos subordinados diretos cada funcionário tem
int salarios[MAX];

int esta_insatisfeito(int chefe) {
    for (int i = 0; i < num_subordinados[chefe]; i++) {
        int sub = subordinados[chefe][i];
        if (salarios[sub] > salarios[chefe]) {
            return 1; // insatisfeito
        }
    }
    return 0;
}

int contar_insatisfeitos(int n) {
    int cont = 0;
    for (int i = 1; i <= n; i++) {
        if (esta_insatisfeito(i)) {
            cont++;
        }
    }
    return cont;
}

int main() {
    int n;
    scanf("%d", &n);

    // zera estruturas
    for (int i = 0; i <= n; i++) {
        num_subordinados[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int chefe, salario;
        scanf("%d %d", &chefe, &salario);

        salarios[i] = salario;
        if (chefe != 0) {
            subordinados[chefe][num_subordinados[chefe]++] = i;
        }
    }

    printf("%d\n", contar_insatisfeitos(n));

    int a;
    scanf("%d", &a); // número de ajustes

    for (int i = 0; i < a; i++) {
        int id, novo_salario;
        scanf("%d %d", &id, &novo_salario);
        salarios[id] = novo_salario;
        printf("%d\n", contar_insatisfeitos(n));
    }

    return 0;
}