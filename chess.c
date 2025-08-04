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
bool isValidPawnMove(const coords fromLoc, const coords toLoc);
bool validateAndMakeMove(const coords fromLoc, const coords toLoc);
void makeMove(const coords fromLoc, const coords toLoc);
bool areKingsAlive(void);

int main(void)
{
    // to clear the screen
    system("clear");

    printInstructions();
    startGame();
    coords fromLoc, toLoc;
    char playerTurn = 'W';
    do
    {
        showBoard();
        printf("\t\t%s's turn\n\n", (playerTurn == 'W') ? "White" : "Black");
        takeInput(&fromLoc, &toLoc, playerTurn);
        if (!validateAndMakeMove(fromLoc, toLoc))
        {
            printf("going to continue in the do-while\n\n");
            continue;
        }
        playerTurn = (playerTurn == 'W') ? 'B' : 'W';
        // system("clear");
    } while (areKingsAlive());
    return 0;
}

void printInstructions(void)
{
    printf("\nTo move any piece please specify the Piece, it's Present Co-ordinate and To Co-ordinate\n");
    printf("1st specify the Piece type & then From Co-ordinates & then To Co-ordinate\n");
    printf("\nEg., To move White Knight from g1 to f3\n\n");
    printf("Give the input as:\n");
    printf("\tFrom Co-ords: g1\n");
    printf("\tTo Co-ords: f3\n");
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
    bool invalidNotation, emptyPiece, wrongPiece; 
    char fromPos[3], toPos[3]; // 1 byte extra for \0
    do
    {
        invalidNotation = false;
        emptyPiece = false;
        wrongPiece = false;
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
                printf("\nNo, piece to be moved!! TRY AGAIN\n\n");
                emptyPiece = true;
            }
            else if (pos[fromLoc->row][fromLoc->col].color != playerColor)
            {
                printf("\nYou are not allowed to move %s's piece!! TRY AGAIN\n\n", (playerColor == 'W') ? "Black" : "White");
                wrongPiece = true;
            }
        }
    } while (invalidNotation || emptyPiece || wrongPiece);
    printf("\n");
    bool noPosChange;
    do
    {
        invalidNotation = false;
        wrongPiece = false;
        noPosChange = false;
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
                printf("\nYou need to make a move, From and To Co-ords can't be the same!! TRY AGAIN\n\n");
                noPosChange = true;
            }
            else if (pos[toLoc->row][toLoc->col].color == playerColor)
            {
                printf("\nYou cannot occupy your existing pieces square!! TRY AGAIN\n\n");
                wrongPiece = true;
            }
        }
    } while (invalidNotation || wrongPiece || noPosChange);
}

bool validateAndMakeMove(const coords fromLoc, const coords toLoc)
{
    switch(pos[fromLoc.row][fromLoc.col].pieceType)
    {
        case 'R':
        {
            // call rook
            if (isValidRookMove(fromLoc, toLoc))
            {
                makeMove(fromLoc, toLoc);
                printf("\nRook Moved!!\n\n");
            }
            else
            {
                printf("\nInvalid Rook Move!! Try Again\n\n");
                return false;
            }
            break;
        }
        case 'N':
        {
            // call knight
            if (isValidKnightMove(fromLoc, toLoc))
            {
                makeMove(fromLoc, toLoc);
                printf("\nKnight Moved!!\n\n");
            }
            else
            {
                printf("\nInvalid Knight Move!! Try Again\n\n");
                return false;
            }
            break;
        }
        case 'B':
        {
            // call bishop
            // if (isValidBishopMove(fromLoc, toLoc))
            // {
            //     makeMove(fromLoc, toLoc);
            //     printf("\nBishop Moved!!\n\n");
            // }
            // else
            // {
            //     printf("\nInvalid Bishop Move!! Try Again\n\n");
            //     return false;
            // }
            break;
        }
        case 'Q':
        {
            // call queen
            // if (isValidQueenMove(fromLoc, toLoc))
            // {
            //     makeMove(fromLoc, toLoc);
            //     printf("\nQueen Moved!!\n\n");
            // }
            // else
            // {
            //     printf("\nInvalid Queen Move!! Try Again\n\n");
            //     return false;
            // }
            break;
        }
        case 'K':
        {
            // call king
            // if (isValidKingMove(fromLoc, toLoc))
            // {
            //     makeMove(fromLoc, toLoc);
            //     printf("\nKing Moved!!\n\n");
            // }
            // else
            // {
            //     printf("\nInvalid King Move!! Try Again\n\n");
            //     return false;
            // }
            break;
        }
        default: // it would be pawn
        {
            // call pawn
            if (isValidPawnMove(fromLoc, toLoc))
            {
                makeMove(fromLoc, toLoc);
                printf("\nPawn Moved!!\n\n");
            }
            else
            {
                printf("\nInvalid Pawn Move!! Try Again\n\n");
                return false;
            }
        }
    }
    return true;
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
                    printf("\nBlocked Path for Rook\n\n");
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
                    printf("\nBlocked Path for Rook\n\n");
                    return false;
                }
            }
        }
    }
    else if (toLoc.col == fromLoc.col) // same col
    {
        validRookMove = true;
        if (toLoc.row < fromLoc.row) // upwards
        {
            for (int i = (fromLoc.row - 1); i >= (toLoc.row  + 1); i--)
            {
                if (pos[i][fromLoc.col].pieceType != ' ')
                {
                    printf("\nBlocked Path for Rook\n\n");
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
                    printf("\nBlocked Path for Rook\n\n");
                    return false;
                }
            }
        }
    }
    return validRookMove;
}

bool isValidKnightMove(const coords fromLoc, const coords toLoc)
{
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
        if (toLoc.row == move[i].row && toLoc.col == move[i].col)
            return true;
        // printf("from: (%i, %i) --> to: (%i, %i)\n", fromLoc.row, fromLoc.col, move[i].row, move[i].col);
    }
    printf("\n");
    return false;
}

bool isValidPawnMove(const coords fromLoc, const coords toLoc)
{
    // can move crosswards only to kill (i.e., for it to move crossward there should be an opposite color piece)
    // ==> to's location can't be empty &&
    // it should be of the opponent (i.e., not it's own piece which is handled while taking input so no need to consider this)

    if (pos[fromLoc.row][fromLoc.col].color == 'W') // if the pawn is white
    {
        // double square at the 1st row of the white
        // else if (fromLoc.row == 6 && toLoc.row == (fromLoc.row - 2) && toLoc.col == fromLoc.col)
        if (toLoc.row == 4 && toLoc.col == fromLoc.col)
        {
            // checking if both the forward square are empty
            if (pos[fromLoc.row - 1][fromLoc.col].pieceType == ' ' && pos[fromLoc.row - 2][fromLoc.col].pieceType == ' ')
            {
                return true;
            }
        }
        // normal forward move
        else if (toLoc.row == (fromLoc.row - 1) && toLoc.col == fromLoc.col)
        {
            // checking whether to's location for pawn is empty or not
            if (pos[fromLoc.row - 1][fromLoc.col].pieceType == ' ')
            {
                return true;
            }
        }
        // crossward kill move
        else if ((toLoc.row == (fromLoc.row - 1)) && (toLoc.col == fromLoc.col - 1 || toLoc.col == fromLoc.col + 1))
        {
            // the above condition checks if the to's move properly crossward or not
            /* and the below return true (to proceed) only if the to's location is
               not empty (i.e., to's loc has opponent's piece) */
            if (pos[toLoc.row][toLoc.col].pieceType != ' ')
                return true;
        }
    }
    else if (pos[fromLoc.row][fromLoc.col].color == 'B') // else if it is black
    {
        // double square move at the 1st row of black
        // if (fromLoc.row == 1 && toLoc.row == (fromLoc.row + 2) && toLoc.col == fromLoc.col)
        if (toLoc.row == 3 && toLoc.col == fromLoc.col)
        {
            // checking if both the forward square are empty
            if (pos[fromLoc.row + 1][fromLoc.col].pieceType == ' ' && pos[fromLoc.row + 2][fromLoc.col].pieceType == ' ')
            {
                return true;
            }
        }
        // normal forward move
        else if (toLoc.row == (fromLoc.row + 1) && toLoc.col == fromLoc.col)
        {
            // checking whether to's location for pawn is empty or not
            if (pos[fromLoc.row + 1][fromLoc.col].pieceType == ' ')
            {
                return true;
            }
        }
        // crossward kill move
        else if ((toLoc.row == (fromLoc.row + 1)) && (toLoc.col == (fromLoc.col - 1) || toLoc.col == (fromLoc.col + 1)))
        {
            if (pos[toLoc.row][toLoc.col].pieceType != ' ')
                return true;
        }
    }
    printf("\nInvalid Pawn Move!!\n\n");
    return false;
}

void makeMove(const coords fromLoc, const coords toLoc)
{
    // the new toLoc has the fromLoc's color and pieceType
    pos[toLoc.row][toLoc.col].color = pos[fromLoc.row][fromLoc.col].color;
    pos[toLoc.row][toLoc.col].pieceType = pos[fromLoc.row][fromLoc.col].pieceType;
    // the old fromLoc is now empty
    pos[fromLoc.row][fromLoc.col].color = pos[fromLoc.row][fromLoc.col].pieceType = ' ';
}

bool areKingsAlive(void)
{
    bool isBlackKingAlive = false, isWhiteKingAlive = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pos[i][j].color == 'B' && pos[i][j].pieceType == 'K')
            {
                printf("\nBlack King is Alive!!\n\n");
                isBlackKingAlive = true;
            }
            else if (pos[i][j].color == 'W' && pos[i][j].pieceType == 'K')
            {
                printf("\nWhite King is Alive!!\n\n");
                isWhiteKingAlive = true;
            }
        }
    }
    return (isBlackKingAlive && isWhiteKingAlive);
}