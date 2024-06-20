#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Function prototypes
void initializeBoard(char board[3][3]);  // Initializes the tic-tac-toe board with empty spaces
void printBoard(char board[3][3]);       // Prints the current state of the tic-tac-toe board
bool makeMove(char board[3][3], int row, int col, char mark);  // Places a mark on the board
bool checkWin(char board[3][3], char mark);  // Checks if a player has won
bool checkDraw(char board[3][3]);            // Checks if the game is a draw
void printInstructions();                   // Prints the game instructions
void printMoveHistory(int moveHistory[][2], int moveCount);  // Prints the move history

int main() {
    char board[3][3];                       // 3x3 board for tic-tac-toe
    char player1[50], player2[50], currentPlayerName[50];
    char currentPlayerMark;
    int row, col, moveCount;
    int moveHistory[9][2];                  // Stores history of moves (row, column)
    bool gameWon, draw, replay;

    // Input player names
    printf("Enter the name of Player 1 (X): ");
    fgets(player1, sizeof(player1), stdin);
    player1[strcspn(player1, "\n")] = '\0'; // Remove newline character

    printf("Enter the name of Player 2 (O): ");
    fgets(player2, sizeof(player2), stdin);
    player2[strcspn(player2, "\n")] = '\0'; // Remove newline character

    do {
        currentPlayerMark = 'X';            // Player 1 starts with 'X'
        strcpy(currentPlayerName, player1);
        gameWon = false;
        draw = false;
        moveCount = 0;
        initializeBoard(board);             // Initialize the board for a new game

        while (!gameWon && !draw) {         // Game loop continues until someone wins or it's a draw
            printBoard(board);              // Print current board state
            printf("%s (%c), enter your move (row and column): ", currentPlayerName, currentPlayerMark);
            if (scanf("%d %d", &row, &col) != 2) {
                while (getchar() != '\n'); // Clear invalid input
                printf("Invalid input, please enter two numbers.\n");
                continue;                 // Restart the loop to get valid input
            }

            // Check if move is valid and make the move
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && makeMove(board, row - 1, col - 1, currentPlayerMark)) {
                moveHistory[moveCount][0] = row;
                moveHistory[moveCount][1] = col;
                moveCount++;

                gameWon = checkWin(board, currentPlayerMark); // Check if the current player has won
                if (gameWon) {
                    printBoard(board);
                    printf("%s wins!\n", currentPlayerName);
                    printMoveHistory(moveHistory, moveCount); // Print move history
                } else {
                    draw = checkDraw(board);  // Check if the game is a draw
                    if (draw) {
                        printBoard(board);
                        printf("The game is a draw!\n");
                        printMoveHistory(moveHistory, moveCount); // Print move history
                    } else {
                        // Switch player turn
                        if (currentPlayerMark == 'X') {
                            currentPlayerMark = 'O';
                            strcpy(currentPlayerName, player2);
                        } else {
                            currentPlayerMark = 'X';
                            strcpy(currentPlayerName, player1);
                        }
                    }
                }
            } else {
                printf("Invalid move, try again.\n");
            }
        }

        printf("Do you want to play again? (y/n): ");
        while (getchar() != '\n'); // Clear the input buffer
        replay = getchar() == 'y';

    } while (replay);

    printf("Thanks for playing!\n");

    return 0;
}

// Initializes the tic-tac-toe board with empty spaces
void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Prints the current state of the tic-tac-toe board
void printBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Places a mark on the board if the position is valid
bool makeMove(char board[3][3], int row, int col, char mark) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = mark;
        return true;    // Move successful
    }
    return false;       // Invalid move
}

// Checks if the given player has won
bool checkWin(char board[3][3], char mark) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)) {
            return true;    // Found a winning row or column
        }
    }
    // Check diagonals
    if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)) {
        return true;    // Found a winning diagonal
    }
    return false;       // No winning condition found
}

// Checks if the board is full (draw condition)
bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;   // Found an empty space, game is not a draw yet
            }
        }
    }
    return true;    // All spaces are filled, game is a draw
}

// Prints the game instructions
void printInstructions() {
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Players take turns to place their marks (X or O) on the board.\n");
    printf("The first player to get three marks in a row, column, or diagonal wins.\n");
    printf("If the board is full and no player has three in a row, the game is a draw.\n");
    printf("To make a move, enter the row and column numbers (1-3) separated by a space.\n\n");
}

// Prints the move history
void printMoveHistory(int moveHistory[][2], int moveCount) {
    printf("Move history:\n");
    for (int i = 0; i < moveCount; i++) {
        printf("Move %d: Row %d, Column %d\n", i + 1, moveHistory[i][0], moveHistory[i][1]);
    }
}
