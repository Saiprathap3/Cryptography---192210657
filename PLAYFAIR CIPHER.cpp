#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MX 5

void playfair(char ch1, char ch2, char key[MX][MX]) {
    int i, j, w = -1, x = -1, y = -1, z = -1;
    FILE *out;

    if ((out = fopen("cipher.txt", "a+")) == NULL) {
        printf("File Corrupted.");
        return;
    }

    // Find positions of ch1 and ch2 in the key matrix
    for (i = 0; i < MX; i++) {
        for (j = 0; j < MX; j++) {
            if (ch1 == key[i][j]) {
                w = i; x = j;
            }
            if (ch2 == key[i][j]) {
                y = i; z = j;
            }
        }
    }

    if (w == y) { // Same row
        x = (x + 1) % 5;
        z = (z + 1) % 5;
    } else if (x == z) { // Same column
        w = (w + 1) % 5;
        y = (y + 1) % 5;
    } else { // Rectangle swap
        int temp = x;
        x = z;
        z = temp;
    }

    printf("%c%c", key[w][x], key[y][z]);
    fprintf(out, "%c%c", key[w][x], key[y][z]);
    fclose(out);
}

int main() {
    int i, j, k = 0, m = 0, n;
    char key[MX][MX], keyminus[25], keystr[10], str[25] = {0};
    char alpa[25] = {'A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    printf("\nEnter key: ");
    fgets(keystr, sizeof(keystr), stdin);
    keystr[strcspn(keystr, "\n")] = '\0';  // Remove trailing newline

    printf("\nEnter the plain text: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  // Remove trailing newline

    // Convert the key to uppercase and replace 'J' with 'I'
    n = strlen(keystr);
    for (i = 0; i < n; i++) {
        if (keystr[i] == 'j') keystr[i] = 'i';
        else if (keystr[i] == 'J') keystr[i] = 'I';
        keystr[i] = toupper(keystr[i]);
    }

    // Convert the plaintext to uppercase and replace 'J' with 'I'
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == 'j') str[i] = 'i';
        else if (str[i] == 'J') str[i] = 'I';
        str[i] = toupper(str[i]);
    }

    // Fill keyminus with the remaining letters of the alphabet
    j = 0;
    for (i = 0; i < 25; i++) {
        for (k = 0; k < n; k++) {
            if (keystr[k] == alpa[i]) break;
        }
        if (k == n) {
            keyminus[j++] = alpa[i];
        }
    }

    // Construct the key matrix
    k = 0;
    for (i = 0; i < MX; i++) {
        for (j = 0; j < MX; j++) {
            if (k < n) {
                key[i][j] = keystr[k++];
            } else {
                key[i][j] = keyminus[m++];
            }
            printf("%c ", key[i][j]);
        }
        printf("\n");
    }

    printf("\n\nEntered text: %s\nCipher Text: ", str);
    for (i = 0; i < strlen(str); i += 2) {
        if (str[i + 1] == '\0') {
            playfair(str[i], 'X', key);
        } else {
            if (str[i] == str[i + 1]) {
                playfair(str[i], 'X', key);
                i--;
            } else {
                playfair(str[i], str[i + 1], key);
            }
        }
    }

   
    return 0;
}
