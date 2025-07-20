// versão levemente (mesmo) menor

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define INFINITO INT_MAX

typedef struct {
    int vertice;
    int peso;
} Aresta;

int N, M, H, capacidade_tanque, combustivel_inicial, capacidade_mochila, P;
int* postos_gasolina;
int** distancias;
int** proximo_salto;
Aresta** grafo;
int* grau;
int* pedidos_restaurante;
int** destinos_pedidos;
int total_pedidos_pendentes;

void adicionar_vizinho(int origem, int destino, int peso) {
    grafo[origem] = realloc(grafo[origem], (grau[origem] + 1) * sizeof(Aresta));
    grafo[origem][grau[origem]].vertice = destino;
    grafo[origem][grau[origem]].peso = peso;
    grau[origem]++;
}

void dijkstra(int inicio) {
    int* visitados = calloc(N+1, sizeof(int));
    int* dist = malloc((N+1) * sizeof(int));
    
    for (int i = 1; i <= N; i++) {
        dist[i] = INFINITO;
        proximo_salto[inicio][i] = -1;
    }
    dist[inicio] = 0;
    
    for (int iteracao = 0; iteracao < N; iteracao++) {
        int vertice_atual = -1;
        int menor_dist = INFINITO;
        
        for (int i = 1; i <= N; i++) {
            if (!visitados[i] && dist[i] < menor_dist) {
                menor_dist = dist[i];
                vertice_atual = i;
            }
        }
        
        if (vertice_atual == -1) break;
        visitados[vertice_atual] = 1;
        
        for (int i = 0; i < grau[vertice_atual]; i++) {
            Aresta e = grafo[vertice_atual][i];
            if (dist[vertice_atual] == INFINITO) continue;
            
            int nova_dist = dist[vertice_atual] + e.peso;
            if (nova_dist < dist[e.vertice]) {
                dist[e.vertice] = nova_dist;
                if (vertice_atual == inicio) {
                    proximo_salto[inicio][e.vertice] = e.vertice;
                } else {
                    proximo_salto[inicio][e.vertice] = proximo_salto[inicio][vertice_atual];
                }
            }
        }
    }
    
    for (int i = 1; i <= N; i++) {
        distancias[inicio][i] = dist[i];
    }
    
    free(visitados);
    free(dist);
}

int encontrar_proximo_vertice(int origem, int destino) {
    if (origem == destino || distancias[origem][destino] == INFINITO) 
        return -1;
    return proximo_salto[origem][destino];
}

int encontrar_posto_proximo(int local, int combustivel) {
    int posto_mais_proximo = -1;
    int menor_distancia = INFINITO;
    
    for (int i = 1; i <= N; i++) {
        if (postos_gasolina[i] && 
            distancias[local][i] <= combustivel && 
            distancias[local][i] < menor_distancia) {
            menor_distancia = distancias[local][i];
            posto_mais_proximo = i;
        }
    }
    
    return posto_mais_proximo;
}

bool precisa_abastecer_agora(int local_atual, int combustivel_atual, int capacidade_tanque) {
    if (postos_gasolina[local_atual]) return false;
    return (combustivel_atual <= (capacidade_tanque * 0.3));
}

int main() {
    scanf("%d %d %d %d %d %d %d", &N, &M, &H, &capacidade_tanque, &combustivel_inicial, &capacidade_mochila, &P);
    
    postos_gasolina = calloc(N+1, sizeof(int));
    grau = calloc(N+1, sizeof(int));
    grafo = calloc(N+1, sizeof(Aresta*));
    distancias = calloc(N+1, sizeof(int*));
    proximo_salto = calloc(N+1, sizeof(int*));
    pedidos_restaurante = calloc(N+1, sizeof(int));
    destinos_pedidos = calloc(N+1, sizeof(int*));
    total_pedidos_pendentes = 0;

    for (int i = 1; i <= N; i++) {
        grafo[i] = NULL;
        distancias[i] = malloc((N+1) * sizeof(int));
        proximo_salto[i] = malloc((N+1) * sizeof(int));
        for (int j = 1; j <= N; j++) {
            distancias[i][j] = INFINITO;
            proximo_salto[i][j] = -1;
        }
        distancias[i][i] = 0;
    }

    for (int i = 0; i < P; i++) {
        int posto;
        scanf("%d", &posto);
        postos_gasolina[posto] = 1;
    }
    
    for (int i = 0; i < M; i++) {
        int origem, destino, peso;
        scanf("%d %d %d", &origem, &destino, &peso);
        adicionar_vizinho(origem, destino, peso);
    }
    
    for (int i = 1; i <= N; i++) {dijkstra(i);}
    
    int num_restaurantes;
    scanf("%d", &num_restaurantes);
    for (int i = 0; i < num_restaurantes; i++) {
        int restaurante, num_pedidos;
        scanf("%d %d", &restaurante, &num_pedidos);
        pedidos_restaurante[restaurante] = num_pedidos;
        destinos_pedidos[restaurante] = malloc(num_pedidos * sizeof(int));
        
        for (int j = 0; j < num_pedidos; j++) {
            scanf("%d", &destinos_pedidos[restaurante][j]);
        }
        total_pedidos_pendentes += num_pedidos;
    }
    
    // ponto de spawn do motoboy
    int local_atual = H;
    int combustivel_atual = combustivel_inicial;
    int* mochila = calloc(capacidade_mochila, sizeof(int));
    int num_pedidos_mochila = 0;
    int destino_planejado = -1;
    int resposta_arbitro;
    bool voltar_para_casa = false;

    while (1) { // é aqui onde as coisas ficam complicadas kk
        if (voltar_para_casa && local_atual == H) {
            printf("x\n");
            fflush(stdout);
            break;
        }
        // Entregar pedidos no local atual
        bool entregou = false;
        for (int i = 0; i < num_pedidos_mochila; ) {
            if (mochila[i] == local_atual) {
                printf("e %d\n", local_atual);
                fflush(stdout);
                scanf("%d", &resposta_arbitro);
                
                if (resposta_arbitro == 1) {
                    for (int j = i; j < num_pedidos_mochila-1; j++) {
                        mochila[j] = mochila[j+1];
                    }
                    num_pedidos_mochila--;
                    total_pedidos_pendentes--;
                    entregou = true;
                    if (num_pedidos_mochila == 0 && total_pedidos_pendentes == 0) {
                        voltar_para_casa = true;
                    }
                } else {
                    i++;
                }
            } else {
                i++;
            }
        }
        if (entregou) continue;
        
        // Coletar pedidos no restaurante atual
        if (!voltar_para_casa && pedidos_restaurante[local_atual] > 0 && 
            num_pedidos_mochila < capacidade_mochila) {
            
            while (pedidos_restaurante[local_atual] > 0 && 
                   num_pedidos_mochila < capacidade_mochila) {
                
                printf("p %d\n", destinos_pedidos[local_atual][0]);
                fflush(stdout);
                scanf("%d", &resposta_arbitro);
                
                if (resposta_arbitro == 1) {
                    mochila[num_pedidos_mochila] = destinos_pedidos[local_atual][0];
                    num_pedidos_mochila++;
                    
                    for (int j = 0; j < pedidos_restaurante[local_atual]-1; j++) {
                        destinos_pedidos[local_atual][j] = destinos_pedidos[local_atual][j+1];
                    }
                    pedidos_restaurante[local_atual]--;
                } else {
                    break;
                }
            }
            destino_planejado = -1;
            continue;
        }
        
        // Abastecer se estiver em posto - CORREÇÃO IMPORTANTE DE UM BUG ESTRANHO GERADA PELO DEEPSEEK
        if (postos_gasolina[local_atual] && combustivel_atual < capacidade_tanque) {
            printf("a\n");
            fflush(stdout);
            scanf("%d", &resposta_arbitro); 

            int necessario = capacidade_tanque - combustivel_atual;
            
            int abastecido = necessario;
            
            // Atualiza combustível do motoboy
            combustivel_atual = (combustivel_atual + abastecido > capacidade_tanque)
                              ? capacidade_tanque
                              : combustivel_atual + abastecido;
            
            continue;
        }  // Fim da correção gerada pelo Deepseek.
        
        // Planejamento de rota com prioridades
        if (voltar_para_casa) {
            destino_planejado = H;
        } 
        else if (precisa_abastecer_agora(local_atual, combustivel_atual, capacidade_tanque)) {
            destino_planejado = encontrar_posto_proximo(local_atual, combustivel_atual);
            if (destino_planejado == -1 && distancias[local_atual][H] <= combustivel_atual) {
                destino_planejado = H;
                voltar_para_casa = true;
            }
        } 
        else if (num_pedidos_mochila > 0) {
            int melhor_entrega = -1;
            int menor_distancia = INFINITO;
            for (int i = 0; i < num_pedidos_mochila; i++) {
                int destino = mochila[i];
                if (distancias[local_atual][destino] <= combustivel_atual && 
                    distancias[local_atual][destino] < menor_distancia) {
                    menor_distancia = distancias[local_atual][destino];
                    melhor_entrega = destino;
                }
            }
            destino_planejado = melhor_entrega;
        } 
        else {
            destino_planejado = -1;
            int melhor_restaurante = -1;
            int melhor_pontuacao = -1;

            for (int i = 1; i <= N; i++) {
                if (pedidos_restaurante[i] > 0) {
                    int dist = distancias[local_atual][i];
                    if (dist == INFINITO) continue;
                    if (dist <= combustivel_atual) {
                        int comb_apos = combustivel_atual - dist;
                        int dist_posto = INFINITO;
                        for (int j = 1; j <= N; j++) {
                            if (postos_gasolina[j] && distancias[i][j] < dist_posto) {
                                dist_posto = distancias[i][j];
                            }
                        }
                        
                        bool pode_voltar = (dist_posto != INFINITO && dist_posto <= comb_apos) || 
                                          (distancias[i][H] <= comb_apos);

                        if (pode_voltar) {
                            int pontuacao = pedidos_restaurante[i] * 1000 - dist;         // sistema de pontuação pra prioridade (solução de calculo proposta pelo Deepseek)
                            if (melhor_restaurante == -1 || pontuacao > melhor_pontuacao) {
                                melhor_restaurante = i;
                                melhor_pontuacao = pontuacao;
                            }
                        }
                    }
                }
            }

            if (melhor_restaurante != -1) {
                destino_planejado = melhor_restaurante;
            } else {
                destino_planejado = encontrar_posto_proximo(local_atual, combustivel_atual);
                if (destino_planejado == -1) {
                    if (distancias[local_atual][H] <= combustivel_atual) {
                        destino_planejado = H;
                        voltar_para_casa = true;
                    }
                }
            }
        }

        // Executar movimento
        if (destino_planejado != -1) {
            int proximo = encontrar_proximo_vertice(local_atual, destino_planejado);
            if (proximo != -1) {
                int custo = INFINITO;
                for (int i = 0; i < grau[local_atual]; i++) {
                    if (grafo[local_atual][i].vertice == proximo) {
                        custo = grafo[local_atual][i].peso;
                        break;
                    }
                }
                
                if (custo != INFINITO && custo <= combustivel_atual) {
                    printf("m %d\n", proximo);
                    fflush(stdout);
                    scanf("%d", &resposta_arbitro);
                    
                    if (resposta_arbitro == 1) {
                        combustivel_atual -= custo;
                        local_atual = proximo;
                        
                        if (local_atual == destino_planejado) {
                            destino_planejado = -1;
                        }
                    } else {
                        destino_planejado = -1;
                    }
                    continue;
                }
            }
            destino_planejado = -1;
        }
        
        // Se chegou até aqui sem realizar ação
        if (local_atual == H) {
            printf("x\n");
            fflush(stdout);
            break;
        }
        destino_planejado = -1;
    }

    for (int i = 1; i <= N; i++) {
        if (grafo[i]) free(grafo[i]);
        free(distancias[i]);
        free(proximo_salto[i]);
        if (destinos_pedidos[i]) free(destinos_pedidos[i]);
    }    
    return 0;
}

