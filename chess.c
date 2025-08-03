#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char color;
    char pieceType;
} grid;

typedef struct
{
    int row;
    int col;
} coords;

// typedef struct
// {
//     char color;
//     char pieceType;
//     int x;
//     int y;
//     bool isEliminated;
// } piece;

grid pos[8][8];

void takeInput(coords *fromLoc, coords *toLoc, char playerColor);
void showBoard(void);
void startGame(void);
void printInstructions(void);
bool isValidRookMove(const coords fromLoc, const coords toLoc);
bool isValidKnightMove(const coords fromLoc, const coords toLoc);

int main(void)
{
    // pos, num ==> arr[8 - numPos][charPos - 'a']

    // to clear the screen
    system("clear");

    printInstructions();
    startGame();
    
    char playerTurn = 'W';
    coords fromLoc, toLoc;
    do
    {
        showBoard();
        printf("\t\t%s's turn\n\n", (playerTurn == 'W') ? "White" : "Black");
        takeInput(&fromLoc, &toLoc, playerTurn);
        // validate the move of that piece
    } while (0);
    // printf("From index: (%i, %i)\nTo index: (%i, %i)\n", fromRow, fromCol, toRow, toCol);
    
    /*
    1. from position should not be empty
        eg., if there's no piece ==> nothing to move
    2. the piece at from postion should not be of the opposite color assigned to the player
        eg., black player should not be able to move the white piece (black can only move black piece)
    3. 
    */
   // VALIDATE the move of the piece
   /* 
   1. find the 'from' piece
   2. validate according to the pieces valid movement's rule
   eg., for rook ==> either to's location i should be same as previous i position or 
                    to's j should be same as previous j position,            
        for knight ==> the to's location should belong the set of the specified co-ords
                        (kinda, the formulas defined by me)
        for bishop ==> 
   */
    switch(pos[fromLoc.row][fromLoc.col].pieceType)
    {
        case 'R':
            // call rook
            isValidRookMove(fromLoc, toLoc);
            break;
        case 'N':
            // call knight
            isValidKnightMove(fromLoc, toLoc);           
            break;
        case 'B':
            // call bishop
            break;
        case 'Q':
            // call queen
            break;
        case 'K':
            // call king
            break;
    }
    
    return 0;
}

void printInstructions(void)
{
    printf("\nTo move any piece please specify the Piece, it's Present Co-ordinate and To Co-ordinate\n");
    printf("1st specify the Piece type & then From Co-ordinates & then To Co-ordinate\n");
    printf("\nEg., To move White Knight to f3\n\n");
    printf("Give the input as:\n");
    // printf("\tPiece-type: WN\n");
    printf("\tFrom Co-ords: f3\n");
    printf("\tTo Co-ords: f3\n");
    printf("\n\n");
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
    printf("\n\n");
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

void takeInput(coords *fromLoc, coords *toLoc, char playerColor)
{
    // take input from user
    // 1st define how u want to take the input
    /* 1. piece type, from location, to location
       2. from location, to location
       Maybe i'll go with 2nd option */
    /* checklist:
       1. take user input in the 2nd format (from location & to location) [done]
       2. validate if both the locations are valid or not [done]
       3. if valid convert it into the 8x8 checkboard array indices [done] 
       4. store those from locations & to locations into the appropriate args */
    bool invalidNotation = false, emptyPiece = false, wrongPiece = false;
    char fromPos[3], toPos[3]; // 1 byte extra for \0
    do
    {
        printf("From Co-ords: ");
        scanf("%2s", fromPos);
        invalidNotation = (!(fromPos[0] >= 'a' && fromPos[0] <= 'h') || !(fromPos[1] >= '1' && fromPos[1] <= '8'));
        if (invalidNotation)
            printf("\nInvalid From Co-ords!! TRY AGAIN\n\n");
        else // ==> valid input notation
        {
            // converting chess notations ==> 8x8 array indices
            // formula: charPos, numPos ==> arr[8 - (numPos - '0')][charPos - 'a']
            // row & col indices of from position
            fromLoc->row = 8 - (fromPos[1] - '0');
            fromLoc->col = fromPos[0] - 'a';
        
            if (pos[fromLoc->row][fromLoc->col].pieceType == ' ') // ==> empty, no piece is there
            {
                printf("No, piece to be moved!! TRY AGAIN\n\n");
                emptyPiece = true;
            }
            else if (pos[fromLoc->row][fromLoc->col].color != playerColor)
            {
                printf("You are not allowed to move %s's piece!! TRY AGAIN\n\n", (playerColor == 'W') ? "Black" : "White");
                wrongPiece = true;
            }
        }
    } while (invalidNotation || emptyPiece || wrongPiece);
    printf("\n");
    bool noPosChange = false;
    do
    {
        printf("To Co-ords: ");
        scanf("%2s", toPos);
        invalidNotation = (!(toPos[0] >= 'a' && toPos[0] <= 'h') || !(toPos[1] >= '1' && toPos[1] <= '8'));
        if (invalidNotation)
            printf("\nInvalid To Co-ords!! TRY AGAIN\n\n");
        else // ==> valid input notation
        {
            // converting chess notations ==> 8x8 array indices
            // formula: charPos, numPos ==> arr[8 - (numPos - '0')][charPos - 'a']
            // row & col indices of to position
            toLoc->row = 8 - (toPos[1] - '0');
            toLoc->col = toPos[0] - 'a';
            
            /* when would i ask for to pos's again even after right notation is given
            1. if to's pos is same as it's own player color (i.e., black can't occupy it's own piece
            or white can't occupy it's own piece)
            2. final & initial positions can't be the same 
            */
            
            // 
            if (fromLoc->row == toLoc->row && fromLoc->col == toLoc->col)
            {
                printf("You need to make a move, From and To Co-ords can't be the same!! TRY AGAIN\n\n");
                noPosChange = true;
            }
            else if (pos[toLoc->row][toLoc->col].color == playerColor)
            {
                printf("You cannot occupy your existing pieces square!! TRY AGAIN\n\n");
                wrongPiece = true;
            }
        }
    } while (invalidNotation || wrongPiece || noPosChange);
}

bool isValidRookMove(const coords fromLoc, const coords toLoc)
{
    bool validRookMove = false;
    if (toLoc.row == fromLoc.row) // same row
    {
        validRookMove = true;
        if (toLoc.col < fromLoc.col) // leftwards
        {
            for (int j = (fromLoc.col - 1); j >= (toLoc.col + 1); j--)
            {
                // if any of the position is not empty ==> invalid move for rook (blocked)
                if (pos[fromLoc.row][j].pieceType != ' ')
                {
                    printf("Blocked Path for Rook\n\n");
                    return false;
                }
            }
        }
        else if (toLoc.col > fromLoc.col) // rightwards
        {
            for (int j = (fromLoc.col + 1); j <= (toLoc.col - 1); j++)
            {
                // if any of the position is not empty ==> invalid move for rook (blocked)
                if (pos[fromLoc.row][j].pieceType != ' ')
                {
                    printf("Blocked Path for Rook\n\n");
                    return false;
                }
            }
        }
    }
    else if (toLoc.col == fromLoc.col)
    {
        validRookMove = true;
        if (toLoc.row < fromLoc.row) // upwards
        {
            for (int i = (fromLoc.row - 1); i >= (toLoc.row  + 1); i--)
            {
                if (pos[i][fromLoc.col].pieceType != ' ')
                {
                    printf("Blocked Path for Rook\n\n");
                    return false;
                }
            }
        }
        else if (toLoc.row > fromLoc.row) // downwards
        {
            for (int i = (fromLoc.row + 1); i <= (toLoc.row - 1); i++)
            {
                if (pos[i][fromLoc.col].pieceType != ' ')
                {
                    printf("Blocked Path for Rook\n\n");
                    return false;
                }
            }
        }
    }
    return validRookMove;
}

bool isValidKnightMove(const coords fromLoc, const coords toLoc)
{
    bool validKnight = false;
    coords move[8];
    move[0].row = fromLoc.row - 2;
    move[0].col = fromLoc.col - 1;

    move[1].row = fromLoc.row - 2;
    move[1].col = fromLoc.col + 1;

    move[2].row = fromLoc.row - 1;
    move[2].col = fromLoc.col - 2;
    
    move[3].row = fromLoc.row - 1;
    move[3].col = fromLoc.col + 2;

    move[4].row = fromLoc.row + 1;
    move[4].col = fromLoc.col - 2;
    
    move[5].row = fromLoc.row + 1;
    move[5].col = fromLoc.col + 2;

    move[6].row = fromLoc.row + 2;
    move[6].col = fromLoc.col - 1;

    move[7].row = fromLoc.row + 2;
    move[7].col = fromLoc.col + 1;

    for (int i = 0; i < 8; i++)
    {
        if (toLoc.row == move[i].row && toLoc.col == move[i].col);
            return true;
    }
}