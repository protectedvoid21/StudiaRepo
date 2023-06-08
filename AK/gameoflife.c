#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

void displayBoard(bool board[10][10]) {
    system("cls");
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(board[i][j]) {
                printf("X");
            } 
            else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main() {
    printf("Game of life\n");

    int beginX;
    int beginY;

    printf("Enter the begin X: ");
    scanf("%d", &beginX);

    printf("Enter the begin Y: ");
    scanf("%d", &beginY);

    bool board[10][10];

    while(true) {
        bool newBoard[10][10];

        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {

                int count = 0;

                for(int k = -1; k <= 1; k++) {
                    for(int l = -1; l <= 1; l++) {
                        if(k == 0 && l == 0) {
                            continue;
                        }

                        if(i + k < 0 || i + k >= 10 || j + l < 0 || j + l >= 10) {
                            continue;
                        }

                        if(board[i + k][j + l]) {
                            count++;
                        }
                    }
                }

                if(board[i][j]) {
                    if(count == 2 || count == 3) {
                        newBoard[i][j] = true;
                    } 
                    else {
                        newBoard[i][j] = false;
                    }
                } 
                else {
                    if(count == 3) {
                        newBoard[i][j] = true;
                    } 
                    else {
                        newBoard[i][j] = false;
                    }
                }
            }
        }
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                board[i][j] = newBoard[i][j];
            }
        }
        displayBoard(board);
        Sleep(500);
    }
}