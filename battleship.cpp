#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int BS = 7; // Board Size

struct Player
{
    string playerName;
    int shots;
};

void printBoard(const char board[][BS]);
bool isValidMove(int row, int col, const char board[][BS]);
bool isShipHit(int row, int col, const char board[][BS], int &hits);
bool isShipSunk(int hits, int length);
bool isGameOver(const char board[][BS]);
void placeShips(char board[][BS]);
void updateBoard(int row, int col, char board[][BS], int &hits);
void displayResults(const char board[][BS], int shots, const Player leaderboard[]);

int main()
{
    srand(time(NULL));

    Player leaderboard[5];
    leaderboard[0] = {" " , 0};
    leaderboard[1] = {" " , 0};
    leaderboard[2] = {" " , 0};
    leaderboard[3] = {" " , 0};
    leaderboard[4] = {" " , 0};
    char board[BS][BS];
    char playerBoard[BS][BS];
    int row, col, counter = 0;
    ;

    do
    {
        char playerName[12];
        cout << "Enter your name: ";
        cin >> playerName;
        cout << "Hello " << playerName << "!" << endl;
        placeShips(board);
        int shots = 0;

        do
        {
            printBoard(board);

            cout << playerName << ", enter your guess (row col): ";
            cin >> row >> col;
            row--;
            col--;
            system("cls");

            if (isValidMove(row, col, board))
            {
                updateBoard(row, col, board, shots);
                shots++;

                if (isGameOver(board))
                {
                    leaderboard[counter] = {playerName, shots};
                    displayResults(board, shots, leaderboard);
                    break;
                }
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }

        } while (true);

        char playAgain;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        if (playAgain != 'y' && playAgain != 'Y')
        {
            break;
        }
        counter++;
    } while (true);
    cout << "Leaderboard: " << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << leaderboard[i].playerName << ": " << leaderboard[i].shots << endl;
    }
}

void printBoard(const char board[][BS])
{
    cout << "  1 2 3 4 5 6 7" << endl;
    for (int i = 0; i < BS; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < BS; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
bool isValidMove(int row, int col, const char board[][BS])
{
    if (row < 0 || row >= BS || col < 0 || col >= BS)
    {
        cout << "Out of bounds. Try again." << endl;
        return false;
    }

    if (board[row][col] == 'X' || board[row][col] == 'O')
    {
        cout << "You've already shot there. Try again." << endl;
        return false;
    }

    return true;
}

bool isShipHit(int row, int col, const char board[][BS], int &hits)
{
    if (board[row][col] == 'S')
    {
        cout << "Hit!" << endl;
        return true;
    }

    cout << "Miss!" << endl;
    return false;
}

bool isShipSunk(int hits, int length)
{
    return hits == length;
}

bool isGameOver(const char board[][BS])
{
    for (int i = 0; i < BS; ++i)
    {
        for (int j = 0; j < BS; ++j)
        {
            if (board[i][j] == 'S')
            {
                return false;
            }
        }
    }

    return true;
}

void placeShips(char board[][BS])
{
    for (int i = 0; i < BS; ++i)
    {
        for (int j = 0; j < BS; ++j)
        {
            board[i][j] = ' ';
        }
    }

    for (int i = 0; i < 1; ++i)
    {
        int row, col;
        int random = rand() % 10;
        if (random > 4)
        {
            do
            {
                row = rand() % BS;
                col = rand() % BS;
            } while (row > 4);

            board[row][col] = 'S';
            board[row + 1][col] = 'S';
            board[row + 2][col] = 'S';
        }
        else
        {
            do
            {
                row = rand() % BS;
                col = rand() % BS;
            } while (col > 4);

            board[row][col] = 'S';
            board[row][col + 1] = 'S';
            board[row][col + 2] = 'S';
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        int random = rand() % 10;
        if (random > 4)
        {
            int row, col;
            do
            {
                row = rand() % BS;
                col = rand() % BS;
            } while (col > 5 ||
                     board[row][col] != ' ' ||
                     board[row][col + 1] != ' ' ||
                     board[row][col - 1] != ' ');

            board[row][col] = 'S';
            board[row][col + 1] = 'S';
        }
        else
        {
            int row, col;
            do
            {
                row = rand() % BS;
                col = rand() % BS;
            } while (row > 5 ||
                     board[row][col] != ' ' ||
                     board[row][col + 1] != ' ' ||
                     board[row][col - 1] != ' ' ||
                     board[row][col + 2] != ' ');

            board[row][col] = 'S';
            board[row + 1][col] = 'S';
        }
    }

    for (int k = 0; k < 4; ++k)
    {
        int row, col;
        do
        {
            row = rand() % BS;
            col = rand() % BS;
        } while (board[row][col] != ' ' ||
                 board[row][col + 1] != ' ' ||
                 board[row][col - 1] != ' ' ||
                 board[row + 1][col] != ' ' ||
                 board[row + 1][col + 1] != ' ' ||
                 board[row - 1][col] != ' ' ||
                 board[row - 1][col + 1] != ' ');

        board[row][col] = 'S';
    }
}

void updateBoard(int row, int col, char board[][BS], int &hits)
{
    if (isShipHit(row, col, board, hits))
    {
        board[row][col] = 'X';
    }
    else
    {
        board[row][col] = 'O';
    }
}

void displayResults(const char board[][BS], int shots, const Player leaderboard[])
{
    printBoard(board);
    cout << "Congratulations! You've sunk all the ships in " << shots << " shots." << endl;
}