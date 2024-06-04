
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function to find the modular inverse
int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1;
}
// Function to find the determinant of a 2x2 matrix
int determinant(int matrix[2][2])
{
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}
// Function to find the adjoint of a 2x2 matrix
void adjoint(int matrix[2][2], int adj[2][2])
{
    adj[0][0] = matrix[1][1];
    adj[0][1] = -matrix[0][1];
    adj[1][0] = -matrix[1][0];
    adj[1][1] = matrix[0][0];
}
// Function to multiply two matrices
void multiplyMatrices(int a[2][2], int b[2][1], int result[2][1])
{
    for (int i = 0; i < 2; i++)
    {
        result[i][0] = 0;
        for (int j = 0; j < 2; j++)
        {
            result[i][0] += a[i][j] * b[j][0];
        }
        result[i][0] %= 26;
        if (result[i][0] < 0)
        {
            result[i][0] += 26;
        }
    }
}
// Hill cipher encryption
void encrypt(char *plaintext, int key[2][2], char *ciphertext)
{
    int plaintextMatrix[2][1];
    int ciphertextMatrix[2][1];
    int length = strlen(plaintext);
    for (int i = 0; i < length; i += 2)
    {
        plaintextMatrix[0][0] = plaintext[i] - 'A';
        plaintextMatrix[1][0] = plaintext[i + 1] - 'A';
        multiplyMatrices(key, plaintextMatrix, ciphertextMatrix);
        ciphertext[i] = ciphertextMatrix[0][0] + 'A';
        ciphertext[i + 1] = ciphertextMatrix[1][0] + 'A';
    }
    ciphertext[length] = '\0';
}
// Hill cipher decryption
void decrypt(char *ciphertext, int key[2][2], char *plaintext)
{
    int det = determinant(key);
    int detInv = modInverse(det, 26);
    if (detInv == -1)
    {
        printf("Key matrix is not invertible\n");
        return;
    }
    int adj[2][2];
    adjoint(key, adj);
    int inverseKey[2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            inverseKey[i][j] = (adj[i][j] * detInv) % 26;
            if (inverseKey[i][j] < 0)
            {
                inverseKey[i][j] += 26;
            }
        }
    }
    int ciphertextMatrix[2][1];
    int plaintextMatrix[2][1];
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i += 2)
    {
        ciphertextMatrix[0][0] = ciphertext[i] - 'A';
        ciphertextMatrix[1][0] = ciphertext[i + 1] - 'A';
        multiplyMatrices(inverseKey, ciphertextMatrix, plaintextMatrix);
        plaintext[i] = plaintextMatrix[0][0] + 'A';
        plaintext[i + 1] = plaintextMatrix[1][0] + 'A';
    }
    plaintext[length] = '\0';
}
int main()
{
    char plaintext[] = "ILOVEPARTY";
    char ciphertext[5];
    char decryptedtext[5];
    int key[2][2] = {{3, 3}, {2, 5}};
    printf("Plaintext: %s\n", plaintext);
    // Encryption
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    // Decryption
    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    return 0;
}