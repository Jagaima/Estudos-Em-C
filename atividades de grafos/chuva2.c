#include <stdio.h>
#include <stdlib.h>

#define MAX 500

int N, M;
char w[MAX][MAX+1];  // cada linha tem M caracteres + '\0'

int main(){
    // Leitura de N e M
    if (scanf("%d %d\n", &N, &M) != 2) 
        return 0;
    // Leitura das N linhas (cada linha tem exatamente M caracteres)
    for (int i = 0; i < N; i++) {
        scanf("%s\n", w[i]);
    }

    // Varre de cima para baixo
    for (int i = 0; i < N; i++) {
        // 1) Queda vertical: se i>0 e acima era 'o', então molha aqui
        if (i > 0) {
            for (int j = 0; j < M; j++) {
                if (w[i][j] == '.' && w[i-1][j] == 'o') {
                    w[i][j] = 'o';
                }
            }
        }
        // 2) Escorrimento horizontal só faz sentido se não for última linha
        if (i < N-1) {
            // 2a) Escorre para a esquerda: esquema de j = M-2 .. 0
            for (int j = M-2; j >= 0; j--) {
                if (w[i][j] == '.' 
                    && w[i][j+1] == 'o' 
                    && w[i+1][j+1] == '#') 
                {
                    w[i][j] = 'o';
                }
            }
            // 2b) Escorre para a direita: esquema de j = 1 .. M-1
            for (int j = 1; j < M; j++) {
                if (w[i][j] == '.' 
                    && w[i][j-1] == 'o' 
                    && w[i+1][j-1] == '#') 
                {
                    w[i][j] = 'o';
                }
            }
        }
    }

    // Imprime a matriz resultante
    for (int i = 0; i < N; i++) {
        printf("%s\n", w[i]);
    }
    return 0;
}
