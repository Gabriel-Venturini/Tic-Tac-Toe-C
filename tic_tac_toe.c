#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner = ' ';
    int decision;

    do
    {
        winner = ' ';
        decision = 1;
        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();
            playerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
            computerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
        }
    
        printBoard();
        printWinner(winner);

        printf("\nPlay again?(1-Yes/2-No): ");
        scanf("%d", &decision);
    }while(decision == 1);

    printf("\nThank you for playing!\n");
    return 0;
}

void resetBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpaces()
{
    int freeSpaces = 9;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove()
{
    int column = 0, row = 0;
    do
    {
        printf("Choose a line(1-3): ");
        scanf("%d", &row);
        row--;
        printf("Choose a column(1-3): ");
        scanf("%d", &column);
        column--;

        if(board[row][column] != ' ')
        {
            printf("Please choose an empty space!\n");
        }
        else
        {
            board[row][column] = PLAYER;
            break;
        }
    }
    while (board[row][column] != ' ');
}

void computerMove()
{
    //this function uses seed based on time to choose move
    srand(time(0));
    int row = 0, column = 0;
    if(checkFreeSpaces() > 0)
    {
        do
        {
            row = rand() % 3;
            column = rand() % 3;
        } while (board[row][column] != ' ');
        
        board[row][column] = COMPUTER;
    }
    else
    {
        printWinner(' ');
    }
}

char checkWinner()
{
    //this section checks all rows
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
    }
    //this section checks all columns
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    //this section checks right diagonal
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }
    //this section checks left diagonal
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner)
{
    if(winner == PLAYER)
    {
        printf("You win!\n");
    }
    else if(winner == COMPUTER)
    {
        printf("You lose!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
}