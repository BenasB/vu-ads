#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define BOARD_SIZE 8
typedef char Board[BOARD_SIZE][BOARD_SIZE];

void printBoard(Board board){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

bool checkBoard(Board board){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0) return false;
        }
    }
    return true;
}

bool inBoardAndFree(Board board, int i, int j)
{
    return (i >= 0 && i < BOARD_SIZE) && (j >= 0 && j < BOARD_SIZE) && board[i][j] != 2;
}

void placeKnight(Board *board, int i, int j)
{
    (*board)[i][j] = 2;
    if (inBoardAndFree(*board, i-2, j-1)) (*board)[i-2][j-1] = 1;
    if (inBoardAndFree(*board, i-2, j+1)) (*board)[i-2][j+1] = 1;
    if (inBoardAndFree(*board, i-1, j+2)) (*board)[i-1][j+2] = 1;
    if (inBoardAndFree(*board, i+1, j+2)) (*board)[i+1][j+2] = 1;
    if (inBoardAndFree(*board, i+2, j+1)) (*board)[i+2][j+1] = 1;
    if (inBoardAndFree(*board, i+2, j-1)) (*board)[i+2][j-1] = 1;
    if (inBoardAndFree(*board, i+1, j-2)) (*board)[i+1][j-2] = 1;
    if (inBoardAndFree(*board, i-1, j-2)) (*board)[i-1][j-2] = 1;
}

void placeKnights(Board *board,
    int k1, int k2, int k3, int k4, int k5, int k6,
    int k7, int k8, int k9, int k10, int k11, int k12
){
    placeKnight(board, k1/BOARD_SIZE, k1%BOARD_SIZE);
    placeKnight(board, k2/BOARD_SIZE, k2%BOARD_SIZE);
    placeKnight(board, k3/BOARD_SIZE, k3%BOARD_SIZE);
    placeKnight(board, k4/BOARD_SIZE, k4%BOARD_SIZE);
    placeKnight(board, k5/BOARD_SIZE, k5%BOARD_SIZE);
    placeKnight(board, k6/BOARD_SIZE, k6%BOARD_SIZE);
    placeKnight(board, k7/BOARD_SIZE, k7%BOARD_SIZE);
    placeKnight(board, k8/BOARD_SIZE, k8%BOARD_SIZE);
    placeKnight(board, k9/BOARD_SIZE, k9%BOARD_SIZE);
    placeKnight(board, k10/BOARD_SIZE, k10%BOARD_SIZE);
    placeKnight(board, k11/BOARD_SIZE, k11%BOARD_SIZE);
    placeKnight(board, k12/BOARD_SIZE, k12%BOARD_SIZE);
}

int main () {
    Board board;
    unsigned long long tries = 0;
    
    for (int k1 = 0; k1 < BOARD_SIZE*BOARD_SIZE; k1++)
    {
        for (int k2 = 0; k2 < BOARD_SIZE*BOARD_SIZE; k2++)
        {
            for (int k3 = 0; k3 < BOARD_SIZE*BOARD_SIZE; k3++)
            {
                for (int k4 = 0; k4 < BOARD_SIZE*BOARD_SIZE; k4++)
                {
                    for (int k5 = 0; k5 < BOARD_SIZE*BOARD_SIZE; k5++)
                    {
                        for (int k6 = 0; k6 < BOARD_SIZE*BOARD_SIZE; k6++)
                        {
                            for (int k7 = 0; k7 < BOARD_SIZE*BOARD_SIZE; k7++)
                            {
                                for (int k8 = 0; k8 < BOARD_SIZE*BOARD_SIZE; k8++)
                                {
                                    for (int k9 = 0; k9 < BOARD_SIZE*BOARD_SIZE; k9++)
                                    {
                                        for (int k10 = 0; k10 < BOARD_SIZE*BOARD_SIZE; k10++)
                                        {
                                            for (int k11 = 0; k11 < BOARD_SIZE*BOARD_SIZE; k11++)
                                            {
                                                for (int k12 = 0; k12 < BOARD_SIZE*BOARD_SIZE; k12++)
                                                {
                                                    tries++;
                                                    memset(board, 0, BOARD_SIZE * BOARD_SIZE * sizeof(char));
                                                    placeKnights(&board, k1, k2, k3, k4, k5, k6, k7, k8, k9, k10, k11, k12);
                                                    if (checkBoard(board)) printBoard(board);

                                                    if (tries % 10000000 == 0) // Print every million tries
                                                    printf("Tries: %llu\n", tries);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }    
}