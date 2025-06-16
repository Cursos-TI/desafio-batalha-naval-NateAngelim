#include <stdio.h>

// Definindo as dimensões do tabuleiro
#define TAMANHO_TABULEIRO 10
// Definindo o tamanho dos navios
#define TAMANHO_NAVIO 3
// Representação de água
#define AGUA 0
// Representação de navio
#define NAVIO 3

// Função para verificar se uma posição está dentro dos limites do tabuleiro
// Retorna 1 (verdadeiro) se estiver dentro, 0 (falso) caso contrário.
int esta_dentro_limites(int linha, int coluna) {
    if (linha >= 0 && linha < TAMANHO_TABULEIRO &&
        coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
        return 1; // Verdadeiro
    }
    return 0; // Falso
}

// Função para verificar se o posicionamento de um navio é válido (não sai do tabuleiro e não sobrepõe)
// Retornar 1 (verdadeiro) se o posicionamento for válido, 0 (falso) caso contrário.
int validar_posicionamento(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                            int linha_inicial, int coluna_inicial,
                            int orientacao, int tamanho_navio) {
    for (int i = 0; i < tamanho_navio; i++) {
        int linha_atual = linha_inicial;
        int coluna_atual = coluna_inicial;

        if (orientacao == 0) { // Horizontal
            coluna_atual += i;
        } else if (orientacao == 1) { // Vertical
            linha_atual += i;
        } else if (orientacao == 2) { // Diagonal principal (linha e coluna aumentam)
            linha_atual += i;
            coluna_atual += i;
        } else if (orientacao == 3) { // Diagonal secundária (linha aumenta, coluna diminui)
            linha_atual += i;
            coluna_atual -= i;
        }

        // Verifica se a posição está dentro dos limites do tabuleiro
        if (!esta_dentro_limites(linha_atual, coluna_atual)) {
            return 0; // Fora dos limites (falso)
        }
        // Verifica se a posição já está ocupada por outro navio
        if (tabuleiro[linha_atual][coluna_atual] == NAVIO) {
            return 0; // Sobreposição (falso)
        }
    }
    return 1; // Posicionamento válido (verdadeiro)
}

// Função para posicionar um navio no tabuleiro
// orientacao: 0=horizontal, 1=vertical, 2=diagonal_principal, 3=diagonal_secundaria
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int linha_inicial, int coluna_inicial,
                      int orientacao, int tamanho_navio) {
    if (validar_posicionamento(tabuleiro, linha_inicial, coluna_inicial, orientacao, tamanho_navio)) {
        for (int i = 0; i < tamanho_navio; i++) {
            int linha_atual = linha_inicial;
            int coluna_atual = coluna_inicial;

            if (orientacao == 0) { // Horizontal
                coluna_atual += i;
            } else if (orientacao == 1) { // Vertical
                linha_atual += i;
            } else if (orientacao == 2) { // Diagonal principal (linha e coluna aumentam)
                linha_atual += i;
                coluna_atual += i;
            } else if (orientacao == 3) { // Diagonal secundária (linha aumenta, coluna diminui)
                linha_atual += i;
                coluna_atual -= i;
            }
            tabuleiro[linha_atual][coluna_atual] = NAVIO;
        }
        printf("Navio posicionado com sucesso! (Início: %d,%d | Orientação: %d)\n", linha_inicial, coluna_inicial, orientacao);
    } else {
        printf("Erro: Não foi possível posicionar o navio (Início: %d,%d | Orientação: %d) - Verifique limites ou sobreposição.\n", linha_inicial, coluna_inicial, orientacao);
    }
}

int main() {
    // Criar um Tabuleiro 10x10:
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com AGUA (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    printf(" Posicionar Navios \n");

    // Posicionar Quatro Navios:

    // Navio 1: Horizontal
    // Início: Linha 1, Coluna 1
    posicionar_navio(tabuleiro, 1, 1, 0, TAMANHO_NAVIO);

    // Navio 2: Vertical
    // Início: Linha 5, Coluna 8
    posicionar_navio(tabuleiro, 5, 8, 1, TAMANHO_NAVIO);

    // Navio 3: Diagonal Principal 
    // Início: Linha 0, Coluna 0
    posicionar_navio(tabuleiro, 0, 0, 2, TAMANHO_NAVIO);

    // Navio 4: Diagonal Secundária 
    // Início: Linha 3, Coluna 7 (começa na linha 3, coluna 7, e vai para 4,6 e 5,5)
    posicionar_navio(tabuleiro, 3, 7, 3, TAMANHO_NAVIO);

    printf("\n Tabuleiro de Batalha Naval \n");
    // Imprime cabeçalho das colunas
    printf("   "); 
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); 
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Imprime o índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // 
        }
        printf("\n"); 
    }
    printf("Batalha naval \n");

    return 0;
}
