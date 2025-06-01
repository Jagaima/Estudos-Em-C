// ESSA VERSÃO ESTÁ ERRADA, MANTIVE POIS FOI COMO EU FUI CHEGANDO A LÓGICA, MAS EU INERPRETEI ERRADO AS CONDIÇÕES E PORTANTO ELA NÃO FUNCIONA CORRETAMENTE.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAXN 500
#define MAXM 500

int N, M;
char parede[MAXN][MAXM+1];

static inline int dentro(int i, int j){
    return (i >= 0 && i < N && j >=0 && j < M);
}

void dfs(int i, int j) {
    int ib = i+1;     // só pra adiantar minha vida haha

    if (dentro(ib, j)) {
        if (parede[ib][j] == '.') {
            parede[ib][j] = 'o';
            dfs(ib,j);
            return;
        }
    }
     if (parede[ib][j] == '#') {
        if (dentro(i,j-1) && parede[i][j-1] == '.'){
            parede[i][j-1] = 'o';
            dfs(i, j-1);
             }
         }
        if (dentro(i, j+1) && parede[i][j+1] == '.'){
        parede[i][j+1] = 'o';
        dfs(i,j+1);
     }
}

int main(){
    if (scanf("%d %d", &N, &M) != 2)  return 0;
    
    for (int i=0; i<N; i++) {
        fgets(parede[i], sizeof(parede[i]), stdin);

        for (int j=0; j< M; j++) {
            if (parede[i][j] == '\n') {
                parede[i][j] = '\0';
                break;
            }
        }

    }

    int j0 = -1;
    for (int j=0; j<M; j++) {
        if (parede[0][j] == 'o'){
            j0 = j;
            break;
        }
    }

    dfs(0, j0);

    for (int i = 0; i < N; i++) {
        printf("%s\n", parede[i]);
    }
    return 0;

}