#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define TAMANHO_HABILIDADE 5
#define AREA_HABILIDADE 5

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se é possível posicionar o navio
int validarPosicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                   int linha, int coluna, int ehVertical)
{
    if (ehVertical)
    {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
            return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (tabuleiro[linha + i][coluna] == NAVIO)
                return 0;
        }
    }
    else
    {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
            return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (tabuleiro[linha][coluna + i] == NAVIO)
                return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, int ehVertical)
{
    if (ehVertical)
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    }
    else
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    }
}

// Função para verificar se é possível posicionar o navio na diagonal
int validarPosicaoDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                           int linha, int coluna, int direcaoCrescente)
{
    // Verifica limites do tabuleiro
    if (direcaoCrescente)
    {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
            coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
        {
            printf("Posição inválida: navio sairia do tabuleiro\n");
            return 0;
        }
        // Verifica sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (tabuleiro[linha + i][coluna + i] == NAVIO)
            {
                printf("Posição inválida: sobreposição de navios\n");
                return 0;
            }
        }
    }
    else
    {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
            coluna - TAMANHO_NAVIO < -1)
            return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (tabuleiro[linha + i][coluna - i] == NAVIO)
                return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio na diagonal
void posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                             int linha, int coluna, int direcaoCrescente)
{
    if (direcaoCrescente)
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    }
    else
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    printf("\n  ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para criar matriz de habilidade em cone
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE])
{
    for (int i = 0; i < TAMANHO_HABILIDADE; i++)
    {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++)
        {
            // Forma de cone: mais largo na base
            if (j >= (TAMANHO_HABILIDADE / 2 - i / 2) &&
                j <= (TAMANHO_HABILIDADE / 2 + i / 2))
            {
                habilidade[i][j] = 1;
            }
            else
            {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em cruz
void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE])
{
    for (int i = 0; i < TAMANHO_HABILIDADE; i++)
    {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++)
        {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)
            {
                habilidade[i][j] = 1;
            }
            else
            {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em octaedro
void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE])
{
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++)
    {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++)
        {
            if (abs(i - centro) + abs(j - centro) <= centro)
            {
                habilidade[i][j] = 1;
            }
            else
            {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int linha, int coluna)
{
    int offsetL = TAMANHO_HABILIDADE / 2;
    int offsetC = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++)
    {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++)
        {
            int posL = linha - offsetL + i;
            int posC = coluna - offsetC + j;

            if (posL >= 0 && posL < TAMANHO_TABULEIRO &&
                posC >= 0 && posC < TAMANHO_TABULEIRO &&
                habilidade[i][j] == 1)
            {
                if (tabuleiro[posL][posC] != NAVIO)
                {
                    tabuleiro[posL][posC] = AREA_HABILIDADE;
                }
            }
        }
    }
}

int main()
{
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona navio vertical em (2,3)
    if (validarPosicao(tabuleiro, 2, 3, 1))
    {
        posicionarNavio(tabuleiro, 2, 3, 1);
    }

    // Posiciona navio horizontal em (5,4)
    if (validarPosicao(tabuleiro, 5, 4, 0))
    {
        posicionarNavio(tabuleiro, 5, 4, 0);
    }

    // Posiciona navio diagonal crescente em (7,3)
    if (validarPosicaoDiagonal(tabuleiro, 7, 3, 1))
    {
        posicionarNavioDiagonal(tabuleiro, 7, 3, 1);
        printf("Navio diagonal crescente posicionado com sucesso\n");
    }
    else
    {
        printf("Não foi possível posicionar o navio diagonal crescente\n");
    }

    // Posiciona navio diagonal decrescente em (1,8)
    if (validarPosicaoDiagonal(tabuleiro, 1, 8, 0))
    {
        posicionarNavioDiagonal(tabuleiro, 1, 8, 0);
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    // Criar e aplicar habilidades
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Aplicar cone
    criarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 4, 4);
    printf("\nTabuleiro com Cone:\n");
    exibirTabuleiro(tabuleiro);

    // Aplicar cruz
    inicializarTabuleiro(tabuleiro); // Limpa o tabuleiro
    criarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 5, 5);
    printf("\nTabuleiro com Cruz:\n");
    exibirTabuleiro(tabuleiro);

    // Aplicar octaedro
    inicializarTabuleiro(tabuleiro);
    criarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 6, 6);
    printf("\nTabuleiro com Octaedro:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
