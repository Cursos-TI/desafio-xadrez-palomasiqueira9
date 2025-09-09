/*
  MateCheck - Movimentação de Peças de Xadrez
  Curso: Análise e Desenvolvimento de Sistemas - Estácio de Sá
  Autor: Paloma Siqueira
  
  Objetivo:
    - Representar um tabuleiro 8x8
    - Permitir ao usuário escolher a peça e a posição inicial
    - Mostrar as casas válidas de movimento
*/

#include <stdio.h>

#define BOARD 8
#define EMPTY 0
#define PIECE 9
#define MOVE  1

/* ---------- Funções de Tabuleiro ---------- */
void print_board(int b[BOARD][BOARD]) {
    printf("\n   ");
    for (int x = 0; x < BOARD; x++) printf(" %d ", x+1);
    printf("\n  +");
    for (int x = 0; x < BOARD; x++) printf("---");
    printf("+\n");
    for (int y = 0; y < BOARD; y++) {
        printf("%d |", y+1);
        for (int x = 0; x < BOARD; x++) {
            if (b[y][x] == EMPTY) printf(" . ");
            else if (b[y][x] == PIECE) printf(" P ");
            else if (b[y][x] == MOVE) printf(" * ");
        }
        printf("|\n");
    }
    printf("  +");
    for (int x = 0; x < BOARD; x++) printf("---");
    printf("+\n\n");
}

void init_board(int b[BOARD][BOARD]) {
    for (int y = 0; y < BOARD; y++)
        for (int x = 0; x < BOARD; x++)
            b[y][x] = EMPTY;
}

void place_piece(int b[BOARD][BOARD], int x, int y) {
    b[y][x] = PIECE;
}

int in_bounds(int x, int y) {
    return (x >= 0 && x < BOARD && y >= 0 && y < BOARD);
}

/* ---------- Movimentos das peças ---------- */
void bishop_moves(int b[BOARD][BOARD], int x, int y) {
    int dirs[4][2] = {{1,1},{-1,1},{1,-1},{-1,-1}};
    for (int d = 0; d < 4; d++) {
        int cx = x + dirs[d][0], cy = y + dirs[d][1];
        while (in_bounds(cx, cy)) {
            b[cy][cx] = MOVE;
            cx += dirs[d][0]; cy += dirs[d][1];
        }
    }
}

void rook_moves(int b[BOARD][BOARD], int x, int y) {
    for (int cx = x+1; cx < BOARD; cx++) b[y][cx] = MOVE;
    for (int cx = x-1; cx >= 0; cx--) b[y][cx] = MOVE;
    for (int cy = y+1; cy < BOARD; cy++) b[cy][x] = MOVE;
    for (int cy = y-1; cy >= 0; cy--) b[cy][x] = MOVE;
}

void queen_moves(int b[BOARD][BOARD], int x, int y) {
    rook_moves(b, x, y);
    bishop_moves(b, x, y);
}

void knight_moves(int b[BOARD][BOARD], int x, int y) {
    int moves[8][2] = {
        {2,1},{1,2},{-1,2},{-2,1},
        {-2,-1},{-1,-2},{1,-2},{2,-1}
    };
    for (int i = 0; i < 8; i++) {
        int nx = x + moves[i][0], ny = y + moves[i][1];
        if (in_bounds(nx, ny)) b[ny][nx] = MOVE;
    }
}

/* ---------- Programa Principal ---------- */
int main(void) {
    int board[BOARD][BOARD];
    int escolha, linha, coluna;

    printf("=== MateCheck - Movimentação de Peças ===\n");
    printf("Escolha a peça:\n");
    printf("1 - Bispo\n");
    printf("2 - Torre\n");
    printf("3 - Rainha\n");
    printf("4 - Cavalo\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    printf("Digite a linha (1 a 8): ");
    scanf("%d", &linha);
    printf("Digite a coluna (1 a 8): ");
    scanf("%d", &coluna);

    // Ajustar índices para [0..7]
    int x = coluna - 1;
    int y = linha - 1;

    if (!in_bounds(x,y)) {
        printf("Posição inválida!\n");
        return 1;
    }

    init_board(board);
    place_piece(board, x, y);

    switch (escolha) {
        case 1: bishop_moves(board, x, y); printf("\nMovimentos do Bispo:\n"); break;
        case 2: rook_moves(board, x, y);   printf("\nMovimentos da Torre:\n"); break;
        case 3: queen_moves(board, x, y);  printf("\nMovimentos da Rainha:\n"); break;
        case 4: knight_moves(board, x, y); printf("\nMovimentos do Cavalo:\n"); break;
        default: printf("Opcao invalida!\n"); return 1;
    }

    print_board(board);

    return 0;
}
