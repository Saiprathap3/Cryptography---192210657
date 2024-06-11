#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    unsigned int a[3][3] = { {6, 24, 1}, {13, 16, 10}, {20, 17, 15} };
    unsigned int b[3][3] = { {8, 5, 10}, {21, 8, 21}, {21, 12, 8} };
    unsigned int c[20], d[20];
    char msg[20];
    int i, j, k, t;

    printf("Enter plain text (3 letters):\n");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;  // Remove the trailing newline character

    if (strlen(msg) != 3) {
        printf("Error: Please enter exactly 3 characters.\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        c[i] = toupper(msg[i]) - 'A';
        printf("%d ", c[i]);
    }

    // Encrypt
    for (i = 0; i < 3; i++) {
        t = 0;
        for (j = 0; j < 3; j++) {
            t += a[i][j] * c[j];
        }
        d[i] = t % 26;
    }

    printf("\nEncrypted Cipher Text: ");
    for (i = 0; i < 3; i++) {
        printf("%c", d[i] + 'A');
    }

    // Decrypt
    for (i = 0; i < 3; i++) {
        t = 0;
        for (j = 0; j < 3; j++) {
            t += b[i][j] * d[j];
        }
        c[i] = t % 26;
    }

    printf("\nDecrypted Cipher Text: ");
    for (i = 0; i < 3; i++) {
        printf("%c", c[i] + 'A');
    }

    return 0;
}
