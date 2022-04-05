#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_SIZE 8
#define EMPTY_TILE 0
#define ATTACKED_TILE 1
#define KNIGHT_TILE 2
#define MAX_KNIGHTS 12

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
    int lowest = 0xFFFF; // Some big number
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

void placeKnight(Board *board, Tile tile){
    (*board)[tile.i][tile.j] = KNIGHT_TILE;
    for(int dx = -2; dx <= 2; dx++)
    {
        for(int dy = -2; dy <= 2; dy++)
        {
            if((dx*dx + dy*dy) == 5)
            {
                if (inBoard(tile.i+dx, tile.j+dy) && (*board)[tile.i+dx][tile.j+dy] != KNIGHT_TILE)
                    (*board)[tile.i+dx][tile.j+dy] = ATTACKED_TILE;
            }
        }
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

void backtrack(Board *board, Board attackMap, int *knightCount){
    Tile lowestTile = getLowestAttackabilityTile(*board, attackMap);
    for(int dx = -2; dx <= 2; dx++)
    {
        for(int dy = -2; dy <= 2; dy++)
        {
            if((dx*dx + dy*dy) == 5) 
            {
                if (inBoard(lowestTile.i+dx, lowestTile.j+dy)){
                    Board boardState;
                    memcpy(&boardState, board, BOARD_SIZE*BOARD_SIZE*sizeof(char));

                    Tile knightTile = {lowestTile.i+dx, lowestTile.j+dy};
                    placeKnight(board, knightTile);
                    (*knightCount)++;

                    if ((*knightCount) == MAX_KNIGHTS){
                        if (checkBoard(*board)){
                            printf("\nFound a solution:\n");
                            printBoard(*board);
                        }

                        memcpy(board, &boardState, BOARD_SIZE*BOARD_SIZE*sizeof(char));
                        (*knightCount)--;

                        // Don't move deeper into the backtracking tree, since we're out of knights
                        continue;
                    }

                    backtrack(board, attackMap, knightCount);

                    memcpy(board, &boardState, BOARD_SIZE*BOARD_SIZE*sizeof(char));
                    (*knightCount)--;
                }
            }
        }
    }
}

int main(){
    Board attackMap;
    memset(attackMap, 0, BOARD_SIZE*BOARD_SIZE*sizeof(char));
    generateAttackMap(&attackMap);
    Board board;
    memset(board, 0, BOARD_SIZE*BOARD_SIZE*sizeof(char));
    int knightCount = 0;
    backtrack(&board, attackMap, &knightCount);
}