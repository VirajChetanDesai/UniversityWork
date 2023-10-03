#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BOARD_SIZE 3

// Function to display the Tic-Tac-Toe board
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the game is over
int isGameOver(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return 1;
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
        return 1;
    }

    // Check for a draw
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }

    return -1; // Game is a draw
}

int main() {
    key_t key = ftok("tic_tac_toe", 65); // Generate a unique key for shared memory
    int shmid = shmget(key, sizeof(char[BOARD_SIZE][BOARD_SIZE]), 0666 | IPC_CREAT); // Create shared memory segment

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    char (*board)[BOARD_SIZE] = shmat(shmid, NULL, 0); // Attach shared memory
    if ((int)board == -1) {
        perror("shmat");
        exit(1);
    }
    // Initialize the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    int currentPlayer = 1;
    int row, col;
    int gameState = 0;
    while (1) {
        displayBoard(board);
        if (currentPlayer == 1)
            printf("Player 1's turn (X): ");
        else
            printf("Player 2's turn (O): ");
        scanf("%d %d", &row, &col);
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }
        if (currentPlayer == 1)
            board[row][col] = 'X';
        else
            board[row][col] = 'O';
        gameState = isGameOver(board);
        if (gameState == 1) {
            displayBoard(board);
            printf("Player %d wins!\n", currentPlayer);
            break;
        } else if (gameState == -1) {
            displayBoard(board);
            printf("It's a draw!\n");
            break;
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
    // Detach and remove shared memory
    shmdt(board);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
