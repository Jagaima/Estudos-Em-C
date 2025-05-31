// essa é a versão de Empresa feita em sala pelo professor (quer dizer ele fez pseudocódigo mas uma tradução aproximada é isso daqui)

#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005   //"folga" pra evitar explosão

int chefe[MAXN], salario[MAXN];
int subordinados[MAXN][MAXN];
int numSubordinados[MAXN];
int insatisfeito[MAXN];

int estaInsatisfeito(int i) {
    for (int j = 0; j < numSubordinados[i]; j++) {
        int sub = subordinados[i][j];
        if (salario[sub] > salario[i]) return 1;
    }
    return 0;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &chefe[i], &salario[i]);
        if (i != 1) {
            subordinados[chefe[i]][numSubordinados[chefe[i]]++] = i;  // o subordinado é o atual e o anterior (na primeira rodada 1) é o chefe, adiciona isso lá, incrementa os subordinados do chefe e adiciona =i para por ele de filho.
        }
    }

    int totalInsatisfeitos = 0;
    for (int i = 1; i <= N; i++) {
        insatisfeito[i] = estaInsatisfeito(i);
        if (insatisfeito[i]) totalInsatisfeitos++;
    }

    printf("%d\n", totalInsatisfeitos);

    int A;
    scanf("%d", &A);

    for (int a = 0; a < A; a++) {
        int I, X;
        scanf("%d %d", &I, &X);

        salario[I] = X;

        // Recalcular satisfação do chefe de I e do próprio I
        int c = chefe[I];//chefe do funcionário
        int mudou;     
        mudou = estaInsatisfeito(c);                  
        if (mudou != insatisfeito[c]) {   // 0 é falso pelo c  então vai pro else. Se mudou for 1 e insatisfeito era 0 então mudou segue 1 pois a condição é realmente diferente e o 1 faz o incremento já que 1=true
            if (mudou) totalInsatisfeitos++;
            else totalInsatisfeitos--;
            insatisfeito[c] = mudou;
        }
                                                            
        mudou = estaInsatisfeito(I);
        if (mudou != insatisfeito[I]) {                                 // lembrar: aqui fazemos com I e C apenas, pois estão próximos e relacionados fazendo ser eficiente.
            if (mudou) totalInsatisfeitos++;
            else totalInsatisfeitos--;
            insatisfeito[I] = mudou;
        }

        printf("%d\n", totalInsatisfeitos);
    }

    return 0;
}

 //sobre a complexidade da estrutura: é como uma dfs pois o(n) pra adicionar tudo, como as comparações só são feitas em adjascência podem levar n mas são geralmente menores 
 //então o(N * K) mesma coisa com a estrutura de mudança A que fica o(A * K) o que nos leva a o(N*k + A * K) como K é considerado pequeno em média o caso médio é o(N+A) com o pior caso quadratico


