#include <stdio.h>
#include <string.h>

void encryptRailFence(char *text, char *cipher, int key);
void decryptRailFence(char *cipher, char *text, int key);

int main() {
    char text[100], cipher[100];
    int key;

    printf("Enter the input string: ");
    gets(text);

    printf("Enter the key: ");
    scanf("%d", &key);

    encryptRailFence(text, cipher, key);
    printf("Cipher text after applying rail fence: %s\n", cipher);

    decryptRailFence(cipher, text, key);
    printf("Text after decryption: %s\n", text);

    return 0;
}

void encryptRailFence(char *text, char *cipher, int key) {
    int len = strlen(text);
    char rail[key][len];
    int i, j, dir_down;

    memset(rail, '\n', sizeof(rail));

    dir_down = 0;
    i = 0; j = 0;
    for (int k = 0; k < len; k++) {
        if (i == 0 || i == key-1)
            dir_down = !dir_down;

        rail[i][j++] = text[k];

        dir_down ? i++ : i--;
    }

    int index = 0;
    for (i = 0; i < key; i++) {
        for (j = 0; j < len; j++) {
            if (rail[i][j] != '\n') {
                cipher[index++] = rail[i][j];
            }
        }
    }
    cipher[index] = '\0';
}

void decryptRailFence(char *cipher, char *text, int key) {
    int len = strlen(cipher);
    char rail[key][len];
    int i, j, dir_down;

    memset(rail, '\n', sizeof(rail));

    dir_down = 0;
    i = 0; j = 0;
    for (int k = 0; k < len; k++) {
        if (i == 0 || i == key-1)
            dir_down = !dir_down;

        rail[i][j++] = '*';

        dir_down ? i++ : i--;
    }

    int index = 0;
    for (i = 0; i < key; i++) {
        for (j = 0; j < len; j++) {
            if (rail[i][j] == '*' && index < len) {
                rail[i][j] = cipher[index++];
            }
        }
    }

    dir_down = 0;
    i = 0; j = 0;
    for (int k = 0; k < len; k++) {
        if (i == 0 || i == key-1)
            dir_down = !dir_down;

        if (rail[i][j] != '\n') {
            text[k] = rail[i][j++];
        }

        dir_down ? i++ : i--;
    }
    text[len] = '\0';
}
