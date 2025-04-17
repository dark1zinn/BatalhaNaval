#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se é possível posicionar o navio
int validarPosicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int linha, int coluna, int ehVertical) {
    if (ehVertical) {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] == NAVIO) return 0;
        }
    } else {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] == NAVIO) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha, int coluna, int ehVertical) {
    if (ehVertical) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    }
}

// Função para verificar se é possível posicionar o navio na diagonal
int validarPosicaoDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                          int linha, int coluna, int direcaoCrescente) {
    // Verifica limites do tabuleiro
    if (direcaoCrescente) {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
            coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Posição inválida: navio sairia do tabuleiro\n");
            return 0;
        }
        // Verifica sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] == NAVIO) {
                printf("Posição inválida: sobreposição de navios\n");
                return 0;
            }
        }
    } else {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
            coluna - TAMANHO_NAVIO < -1) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna - i] == NAVIO) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio na diagonal
void posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                            int linha, int coluna, int direcaoCrescente) {
    if (direcaoCrescente) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n  ");
    for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona navio vertical em (2,3)
    if (validarPosicao(tabuleiro, 2, 3, 1)) {
        posicionarNavio(tabuleiro, 2, 3, 1);
    }
    
    // Posiciona navio horizontal em (5,4)
    if (validarPosicao(tabuleiro, 5, 4, 0)) {
        posicionarNavio(tabuleiro, 5, 4, 0);
    }
    
    // Posiciona navio diagonal crescente em (7,3)
    if (validarPosicaoDiagonal(tabuleiro, 7, 3, 1)) {
        posicionarNavioDiagonal(tabuleiro, 7, 3, 1);
        printf("Navio diagonal crescente posicionado com sucesso\n");
    } else {
        printf("Não foi possível posicionar o navio diagonal crescente\n");
    }
    
    // Posiciona navio diagonal decrescente em (1,8)
    if (validarPosicaoDiagonal(tabuleiro, 1, 8, 0)) {
        posicionarNavioDiagonal(tabuleiro, 1, 8, 0);
    }
    
    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
