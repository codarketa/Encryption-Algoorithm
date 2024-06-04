#include <stdio.h>
#include <string.h>

int encrpyt(char text[], int key)
{
    int textLen = strlen(text), i, j, k = -1, row = 0, col = 0;
    char railMatrix[key][textLen];

    for (i = 0; i < key; ++i)
        for (j = 0; j < textLen; ++j)

            railMatrix[i][j] = '\0';

    for (i = 0; i < textLen; ++i)
    {
        railMatrix[row][col++] = text[i];

        if (row == 0 || row == key - 1)
            k = k * (-1);
        row = row + k;
    }

    printf("\n encrypted message:");

    for (i = 0; i < key; ++i)
        for (j = 0; j < textLen; j++)
            if (railMatrix[i][j] != '\0')
                printf("%c", railMatrix[i][j]);
}
void decrypt(char enc[], int key)
{
    int textLen = strlen(enc), i, j, k = -1, row = 0, col = 0, m = 0;
    char railMatrix[key][textLen];
    for (i = 0; i < key; ++i)
        for (j = 0; j < textLen; ++j)
            railMatrix[i][j] = '\n';
    for (i = 0; i < textLen; ++i)
    {
        railMatrix[row][col++] = '*';

        if (row == 0 || row == key - 1)
            k = k * (-1);
        row = row + k;
    }

    for (i = 0; i < key; ++i)
        for (j = 0; j < textLen; ++i)
            if (railMatrix[i][j] == '*')
                railMatrix[i][j] = enc[m++];
    row = col = 0;
    k = -1;

    printf("\n decrypted message:");

    for (i = 0; i < textLen; ++i)
    {
        printf("%c", railMatrix[row][col++]);
        if (row == 0 || row == key - 1)
            k = k * (-1);
        row = row + k;
    }
}

int main()
{
    char text[] = "CRYPTOGRAPHYWORLDISMORESECURE";
    char enc[] = "CGWSERORYOIMSCYTAHRDOEUEPPLRR";
    int key = 2;
    printf("Plaintext:%s", text);
    encrpyt(text, key);
    decrypt(enc, key);
}