#include <stdio.h>

// Definindo as dimensões do tabuleiro
#define TAMANHO_TABULEIRO 10
// Definindo o tamanho dos navios
#define TAMANHO_NAVIO 3
// Representação de água
#define AGUA 0
// Representação de navio
#define NAVIO 3
// Representação de área de habilidade
#define HABILIDADE_AFETADA 5

// Definindo o tamanho das matrizes de habilidade (sempre ímpar para ter um centro)
#define TAMANHO_HABILIDADE_CONE 5
#define TAMANHO_HABILIDADE_CRUZ 5
#define TAMANHO_HABILIDADE_OCTAEDRO 5

// Função para verificar se uma posição está dentro dos limites do tabuleiro
// Retornar 1 (verdadeiro) se estiver dentro, 0 (falso) caso contrário.
int esta_dentro_limites(int linha, int coluna) {
    if (linha >= 0 && linha < TAMANHO_TABULEIRO &&
        coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
        return 1; // Verdadeiro
    }
    return 0; 
}

// Função para verificar se o posicionamento de um navio é válido 
// Retorna 1 (verdadeiro) se o posicionamento for válido, 0 (falso) caso contrário.
int validar_posicionamento_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                 int linha_inicial, int coluna_inicial,
                                 int orientacao, int tamanho_navio) {
    for (int i = 0; i < tamanho_navio; i++) {
        int linha_atual = linha_inicial;
        int coluna_atual = coluna_inicial;

        if (orientacao == 0) { // Horizontal
            coluna_atual += i;
        } else if (orientacao == 1) { // Vertical
            linha_atual += i;
        } else if (orientacao == 2) { // Diagonal principal 
            linha_atual += i;
            coluna_atual += i;
        } else if (orientacao == 3) { // Diagonal secundária 
            linha_atual += i;
            coluna_atual -= i;
        }

        // Verificar se a posição está dentro dos limites do tabuleiro
        if (!esta_dentro_limites(linha_atual, coluna_atual)) {
            return 0; // Fora dos limites (falso)
        }
        // Verificar se a posição já está ocupada por outro navio
        if (tabuleiro[linha_atual][coluna_atual] == NAVIO) {
            return 0; // Sobreposição (falso)
        }
    }
    return 1; // Posicionamento válido 
}

// Função para posicionar um navio no tabuleiro
// orientacao: 0=horizontal, 1=vertical, 2=diagonal_principal, 3=diagonal_secundaria
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int linha_inicial, int coluna_inicial,
                      int orientacao, int tamanho_navio) {
    if (validar_posicionamento_navio(tabuleiro, linha_inicial, coluna_inicial, orientacao, tamanho_navio)) {
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

//  Funções para criar e aplicar as habilidades especiais 

// Cria a matriz de habilidade Cone
void criar_habilidade_cone(int matriz_habilidade[TAMANHO_HABILIDADE_CONE][TAMANHO_HABILIDADE_CONE]) {
    int centro_x = TAMANHO_HABILIDADE_CONE / 2; // Coluna central do cone (topo)

    for (int i = 0; i < TAMANHO_HABILIDADE_CONE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CONE; j++) {
            matriz_habilidade[i][j] = 0; // Inicializa com 0 (não afetado)

            // Lógica para o cone: i é a linha (distância do topo)
            // O número de células afetadas em cada linha aumenta com a distância do topo
            // O cone se expande do centro_x para ambos os lados
            if (j >= centro_x - i && j <= centro_x + i) {
                matriz_habilidade[i][j] = 1; // Afetado
            }
        }
    }
}

// Cria a matriz de habilidade Cruz
void criar_habilidade_cruz(int matriz_habilidade[TAMANHO_HABILIDADE_CRUZ][TAMANHO_HABILIDADE_CRUZ]) {
    int centro = TAMANHO_HABILIDADE_CRUZ / 2; // Centro da matriz

    for (int i = 0; i < TAMANHO_HABILIDADE_CRUZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CRUZ; j++) {
            matriz_habilidade[i][j] = 0; // Inicializa com 0

            // Se estiver na linha central OU na coluna central
            if (i == centro || j == centro) {
                matriz_habilidade[i][j] = 1; // Afetado
            }
        }
    }
}

// Cria a matriz de habilidade Octaedro 
void criar_habilidade_octaedro(int matriz_habilidade[TAMANHO_HABILIDADE_OCTAEDRO][TAMANHO_HABILIDADE_OCTAEDRO]) {
    int centro = TAMANHO_HABILIDADE_OCTAEDRO / 2; // Centro da matriz

    for (int i = 0; i < TAMANHO_HABILIDADE_OCTAEDRO; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_OCTAEDRO; j++) {
            matriz_habilidade[i][j] = 0; // Inicializa com 0

            int dist_manhattan = (i > centro ? i - centro : centro - i) +
                                 (j > centro ? j - centro : centro - j);

            if (dist_manhattan <= centro) {
                matriz_habilidade[i][j] = 1; // Afetado
            }
        }
    }
}


// Aplicar a matriz de habilidade ao tabuleiro principal
void aplicar_habilidade_no_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                     int matriz_habilidade_origem[][TAMANHO_HABILIDADE_CONE], // Usa o maior para flexibilidade
                                     int tamanho_habilidade,
                                     int centro_tabuleiro_linha, int centro_tabuleiro_coluna) {

    // Calcular para posicionar o centro da matriz de habilidade no ponto de origem do tabuleiro
    int offset_habilidade = tamanho_habilidade / 2;

    for (int i = 0; i < tamanho_habilidade; i++) {
        for (int j = 0; j < tamanho_habilidade; j++) {
            // Calcula a posição correspondente no tabuleiro
            int tabuleiro_linha = centro_tabuleiro_linha - offset_habilidade + i;
            int tabuleiro_coluna = centro_tabuleiro_coluna - offset_habilidade + j;

            // Se a posição da habilidade for afetada (valor 1) E estiver dentro dos limites do tabuleiro
            if (matriz_habilidade_origem[i][j] == 1 &&
                esta_dentro_limites(tabuleiro_linha, tabuleiro_coluna)) {

                // Marca a posição no tabuleiro com o valor da habilidade (se não for um navio)
                // Simplificação: Habilidade pode sobrepor água ou outras habilidades, mas não navios
                if (tabuleiro[tabuleiro_linha][tabuleiro_coluna] != NAVIO) {
                     tabuleiro[tabuleiro_linha][tabuleiro_coluna] = HABILIDADE_AFETADA;
                }
            }
        }
    }
}


int main() {
    // Definir o Tabuleiro:
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com AGUA (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    printf(" Posicionando Navios \n");

    // Posicionando Quatro Navios 
    posicionar_navio(tabuleiro, 1, 1, 0, TAMANHO_NAVIO); // Horizontal
    posicionar_navio(tabuleiro, 5, 8, 1, TAMANHO_NAVIO); // Vertical
    posicionar_navio(tabuleiro, 0, 0, 2, TAMANHO_NAVIO); // Diagonal Principal
    posicionar_navio(tabuleiro, 3, 7, 3, TAMANHO_NAVIO); // Diagonal Secundária

    printf("\n Criando e Aplicando Habilidades Especiais \n");

    // Criar Matrizes de Habilidade:
    int habilidade_cone[TAMANHO_HABILIDADE_CONE][TAMANHO_HABILIDADE_CONE];
    int habilidade_cruz[TAMANHO_HABILIDADE_CRUZ][TAMANHO_HABILIDADE_CRUZ];
    int habilidade_octaedro[TAMANHO_HABILIDADE_OCTAEDRO][TAMANHO_HABILIDADE_OCTAEDRO];

    criar_habilidade_cone(habilidade_cone);
    criar_habilidade_cruz(habilidade_cruz);
    criar_habilidade_octaedro(habilidade_octaedro);

    // Habilidade Cone: Ponto de origem no tabuleiro (centro do cone)
    int cone_origem_linha = 4;
    int cone_origem_coluna = 4;
    aplicar_habilidade_no_tabuleiro(tabuleiro, habilidade_cone, TAMANHO_HABILIDADE_CONE, cone_origem_linha, cone_origem_coluna);
    printf("Habilidade Cone aplicada em (%d,%d)\n", cone_origem_linha, cone_origem_coluna);


    // Habilidade Cruz: Ponto de origem no tabuleiro (centro da cruz)
    int cruz_origem_linha = 7;
    int cruz_origem_coluna = 2;
    aplicar_habilidade_no_tabuleiro(tabuleiro, habilidade_cruz, TAMANHO_HABILIDADE_CRUZ, cruz_origem_linha, cruz_origem_coluna);
    printf("Habilidade Cruz aplicada em (%d,%d)\n", cruz_origem_linha, cruz_origem_coluna);


    // Habilidade Octaedro: Ponto de origem no tabuleiro (centro do losango)
    int octaedro_origem_linha = 2;
    int octaedro_origem_coluna = 8;
    aplicar_habilidade_no_tabuleiro(tabuleiro, habilidade_octaedro, TAMANHO_HABILIDADE_OCTAEDRO, octaedro_origem_linha, octaedro_origem_coluna);
    printf("Habilidade Octaedro aplicada em (%d,%d)\n", octaedro_origem_linha, octaedro_origem_coluna);


    // Exibir o Tabuleiro com Habilidade:
    printf("\n Tabuleiro Final com Navios e Habilidades \n");
    // Imprime cabeçalho das colunas
    printf("   "); // Espaço para o índice da linha
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Imprime o índice da coluna
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Imprime o índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // Imprime o valor da posição com 2 espaços para alinhamento
        }
        printf("\n"); 
    }
    printf(" Batalha Naval \n");

    return 0;
}
