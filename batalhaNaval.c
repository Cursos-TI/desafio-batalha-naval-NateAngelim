#include <stdio.h>

// Definindo as dimensões do tabuleiro
#define TAMANHO_TABULEIRO 10
// Definindo o tamanho dos navios
#define TAMANHO_NAVIO 3
// Representação de água
#define AGUA 0
// Representação de navio
#define NAVIO 3

int main() {
    // 1. Representar o Tabuleiro: Matriz 10x10 inicializada com 0s 
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com AGUA (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2. Posicionar os Navios: Um na horizontal e outro na vertical

    // Navio Horizontal:
    // Coordenadas iniciais (linha, coluna) 
    int navio_h_linha = 2;
    int navio_h_coluna = 1;

    // Navio Vertical:
    // Coordenadas iniciais (linha, coluna) 
    int navio_v_linha = 5;
    int navio_v_coluna = 5;

    // Validação e posicionamento do Navio Horizontal
    // Verificar se o navio cabe no tabuleiro na horizontal
    if (navio_h_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
      
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_h_linha][navio_h_coluna + i] = NAVIO;
        }
    } else {
        printf("Erro: Navio horizontal fora dos limites do tabuleiro!\n");
    }

    // Validação e posicionamento do Navio Vertical
    // Verificar se o navio cabe no tabuleiro na vertical
    if (navio_v_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Posiciona o navio verticalmente
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Simplificação para este nível: não valida sobreposição complexa
            // Apenas verifica se a posição já não é um navio para evitar sobrescrever acidentalmente.
            // Para uma validação mais robusta, seria necessário verificar antes de posicionar.
            if (tabuleiro[navio_v_linha + i][navio_v_coluna] == AGUA) {
                tabuleiro[navio_v_linha + i][navio_v_coluna] = NAVIO;
            } else {
                printf("Aviso: Tentativa de sobrepor navio verticalmente em (%d, %d). Posição já ocupada.\n", navio_v_linha + i, navio_v_coluna);
            }
        }
    } else {
        printf("Erro: Navio vertical fora dos limites do tabuleiro!\n");
    }

    // 3. Exibir o Tabuleiro
    printf("\n Tabuleiro de Batalha Naval \n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); 
        }
        printf("\n"); 
    }
    printf("Jogo batalha naval \n");

    return 0;
}
