#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_SIZE 8
typedef char Board[BOARD_SIZE][BOARD_SIZE];

bool inBoard(int i, int j){
    return (i >= 0 && i < BOARD_SIZE) && (j >= 0 && j < BOARD_SIZE);
}

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

void generateAttackMap(Board *board){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (inBoard(i-2, j-1)) (*board)[i-2][j-1] += 1;
            if (inBoard(i-2, j+1)) (*board)[i-2][j+1] += 1;
            if (inBoard(i-1, j+2)) (*board)[i-1][j+2] += 1;
            if (inBoard(i+1, j+2)) (*board)[i+1][j+2] += 1;
            if (inBoard(i+2, j+1)) (*board)[i+2][j+1] += 1;
            if (inBoard(i+2, j-1)) (*board)[i+2][j-1] += 1;
            if (inBoard(i+1, j-2)) (*board)[i+1][j-2] += 1;
            if (inBoard(i-1, j-2)) (*board)[i-1][j-2] += 1;
        }
    }
}

int main(){
    Board attackMap;
    memset(attackMap, 0, BOARD_SIZE*BOARD_SIZE*sizeof(char));
    generateAttackMap(&attackMap);
    printBoard(attackMap);
    printf("Hello world!\n");
}