#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char color;
    char pieceType;
} grid;

grid pos[8][8];

void showBoard(void);
void startGame(void);

int main(void)
{
    // pos, num ==> arr[8 - numPos][charPos - 'a']

    // to clear the screen
    system("clear");

    printf("\nTo move any piece please specify the Piece, it's Present Co-ordinate and To Co-ordinate\n");
    printf("1st specify the Piece type & then From Co-ordinates & then To Co-ordinate\n");
    printf("\nEg., To move White Knight to f3\n\n");
    printf("Give the input as:\n");
    printf("\tPiece-type: WN\n");
    printf("\tFrom Co-ords: f3\n");
    printf("\tTo Co-ords: f3\n");
    printf("\n\n");
    startGame();
    showBoard();

    printf("\n\n");
    return 0;
}

void showBoard(void)
{
    int x = 0, y = 0;
    char charac = 97, num = 8;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if ((i % 2 != 0) && (j % 2 != 0))
            {
                if (i == 17 && j == 1)
                    printf("    ");
                else if (i == 17 && j != 1)
                    printf(" %c  ", charac++);
                else if (i != 17 && j == 1)
                    printf(" %i  ", num--);
                else if (i != 17 && j != 1)
                {
                    x = (i - 1) / 2;
                    y = (j - 3) / 2;
                    printf(" %c%c ", pos[x][y].color, pos[x][y].pieceType);
                }
            }
            else if ((i % 2 != 0) && (j % 2 == 0))
            {
                printf("|");
            }
            else if ((i % 2 == 0) && (j % 2 != 0))
            {
                printf("----");
            }
            else if ((i % 2 == 0) && (j % 2 == 0))
            {
                printf("+");
            }
        }
        printf("\n");
    }
}

void startGame(void)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i == 0 || i == 1)
            {
                pos[i][j].color = 'B';
            }
            else if (i == 6 || i == 7)
            {
                pos[i][j].color = 'W';
            }
            else
            {
                pos[i][j].color = ' ';
            }

            if ((i == 0 && (j == 0 || j == 7)) || (i == 7 && (j == 0 || j == 7)))
            {
                pos[i][j].pieceType = 'R';
            }
            else if ((i == 0 && (j == 1 || j == 6)) || (i == 7 && (j == 1 || j == 6)))
            {
                pos[i][j].pieceType = 'N';
            }
            else if ((i == 0 && (j == 2 || j == 5)) || (i == 7 && (j == 2 || j == 5)))
            {
                pos[i][j].pieceType = 'B';
            }
            else if ((i == 0 || i == 7) && j == 3)
            {
                pos[i][j].pieceType = 'Q';
            }
            else if ((i == 0 || i == 7) && j == 4)
            {
                pos[i][j].pieceType = 'K';
            }
            else
            {
                pos[i][j].pieceType = ' ';
            }

            if (i == 1 || i == 6)
            {
                pos[i][j].pieceType = j + '1';
            }
        }
    }
}
