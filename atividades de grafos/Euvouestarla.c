#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, J;
    scanf("%d %d %d", &N, &M, &J);                 // N: bairro, m: visitados, J: sondagem por juliano

    // Alocação e leitura das adjacências
    int *A[N], Aj[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &Aj[i]);
        A[i] = (int *)malloc(Aj[i] * sizeof(int));
        for (int j = 0; j < Aj[i]; j++)
            scanf("%d", &A[i][j]);
    }

    // Marcação de locais perigosos
    char unsafe[N];
    for (int i = 0; i < N; i++) unsafe[i] = 0;
    
    for (int i = 0; i < M; i++) {
        int loc;
        scanf("%d", &loc);
        unsafe[loc] = 1;
        for (int j = 0; j < Aj[loc]; j++)
            unsafe[A[loc][j]] = 1;
    }

    // Processamento das consultas
    while (J--) {
        int q;
        scanf("%d", &q);
        puts((q >= 0 && q < N && unsafe[q]) ? "Eu vou estar la" : "Nao vou estar la");
    }

    // Liberação de memória
    for (int i = 0; i < N; i++) free(A[i]);
    
    return 0;
}