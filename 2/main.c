#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_SIZE 8
#define EMPTY_TILE 0
#define ATTACKED_TILE 1
#define KNIGHT_TILE 2
typedef char Board[BOARD_SIZE][BOARD_SIZE];

struct Tile
{
    int i, j;
};

typedef struct Tile Tile;

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
            for(int dx = -2; dx <= 2; dx++)
            {
                for(int dy = -2; dy <= 2; dy++)
                {
                    if((dx*dx + dy*dy) == 5) // Defined by the way knights move
                    {
                        if (inBoard(i+dx, j+dy)) (*board)[i+dx][j+dy] += 1;
                    }
                }
            }
        }
    }
}

Tile getLowestAttackabilityTile(Board board, Board attackMap){
    Tile tile;
    int lowest = 0xFFFF;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_TILE && attackMap[i][j] < lowest)
            {
                lowest = attackMap[i][j];
                tile.i = i;
                tile.j = j;
            }
        }
    }

    return tile;
}

int main(){
    Board attackMap;
    memset(attackMap, 0, BOARD_SIZE*BOARD_SIZE*sizeof(char));
    generateAttackMap(&attackMap);
    printBoard(attackMap);
    Board board;
    memset(board, 0, BOARD_SIZE*BOARD_SIZE*sizeof(char));
    Tile lowestTile = getLowestAttackabilityTile(board, attackMap);

    printf("Lowest i: %d j:%d\n", lowestTile.i, lowestTile.j);
}