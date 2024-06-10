#include <stdio.h>
#include <string.h>
#include <ctype.h>

void main() {
    char plain[100], cipher[100];
    int key, i, length;

    // Input plain text
    printf("\nEnter the plain text: ");
    scanf("%s", plain);

    // Input key value
    printf("\nEnter the key value: ");
    scanf("%d", &key);

    printf("\n\n\tPLAIN TEXT: %s", plain);

    // Encrypt the plain text
    printf("\n\n\tENCRYPTED TEXT: ");
    for (i = 0, length = strlen(plain); i < length; i++) {
        if (isalpha(plain[i])) {
            if (isupper(plain[i])) {
                cipher[i] = (plain[i] - 'A' + key) % 26 + 'A';
            } else if (islower(plain[i])) {
                cipher[i] = (plain[i] - 'a' + key) % 26 + 'a';
            }
        } else {
            cipher[i] = plain[i]; // Non-alphabetical characters remain unchanged
        }
        printf("%c", cipher[i]);
    }
    cipher[length] = '\0'; // Null-terminate the cipher text

    // Decrypt the cipher text
    printf("\n\n\tAFTER DECRYPTION: ");
    for (i = 0; i < length; i++) {
        if (isalpha(cipher[i])) {
            if (isupper(cipher[i])) {
                plain[i] = (cipher[i] - 'A' - key + 26) % 26 + 'A';
            } else if (islower(cipher[i])) {
                plain[i] = (cipher[i] - 'a' - key + 26) % 26 + 'a';
            }
        } else {
            plain[i] = cipher[i]; // Non-alphabetical characters remain unchanged
        }
        printf("%c", plain[i]);
    }
    plain[length] = '\0'; // Null-terminate the decrypted text

    getchar(); // Wait for user input before closing (for some environments)
    getchar(); // To consume the newline character left in the buffer
}
