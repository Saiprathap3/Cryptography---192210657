#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Playfair matrix
char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void preprocessText(char* text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (text[i] == 'J') text[i] = 'I'; // Replace J with I
        text[i] = toupper(text[i]); // Convert to uppercase
    }
}

void findPosition(char ch, int* row, int* col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char a, char b, char* encryptedPair) {
    int row1, col1, row2, col2;
    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);

    if (row1 == row2) { // Same row
        encryptedPair[0] = playfairMatrix[row1][(col1 + 1) % SIZE];
        encryptedPair[1] = playfairMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) { // Same column
        encryptedPair[0] = playfairMatrix[(row1 + 1) % SIZE][col1];
        encryptedPair[1] = playfairMatrix[(row2 + 1) % SIZE][col2];
    } else { // Rectangle
        encryptedPair[0] = playfairMatrix[row1][col2];
        encryptedPair[1] = playfairMatrix[row2][col1];
    }
}

void encryptMessage(char* message, char* encryptedMessage) {
    preprocessText(message);
    int len = strlen(message);
    int i, k = 0;

    for (i = 0; i < len; i += 2) {
        char a = message[i];
        char b = (i + 1 < len) ? message[i + 1] : 'X';

        if (a == b) { // If same letters, replace second with X
            b = 'X';
            i--;
        }

        char encryptedPair[2];
        encryptPair(a, b, encryptedPair);

        encryptedMessage[k++] = encryptedPair[0];
        encryptedMessage[k++] = encryptedPair[1];
    }
    encryptedMessage[k] = '\0'; // Null-terminate the string
}

int main() {
    char message[] = "Must see you over Cadogan West Coming at once";
    char encryptedMessage[100];

    encryptMessage(message, encryptedMessage);

    printf("Encrypted Message: %s\n", encryptedMessage);

    return 0;
}