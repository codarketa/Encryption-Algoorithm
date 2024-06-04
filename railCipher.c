#include <stdio.h>
#include <string.h>

int main()
{
    int i, j, len, rail, count, code[100][100];
    char str[100];
    printf("Enter a plaintext:");
    gets(str);
    len = strlen(str);
    printf("Enter the value of rails:");
    scanf("%d", &rail);

    for (i = 0; i < rail; i++)
    {
        for (j = 0; j < len; j++)
        {
            code[i][j] = 0;
        }
    }
    count = 0;
    j = 0;
    while (j < len)
    {
        if (count % 2 == 0)
        {
            for (i = 0; i < rail; i++)
            {
                code[i][j] = str[j];
                j++;
            }
        }
        else
        {
            for (i = rail - 2; i > 0; i--)
            {
                code[i][j] = (int)str[j];
                j++;
            }
        }
        count++;
    }
    printf("Encrypted message is:");

    for (i = 0; i < rail; i++)
    {
        for (j = 0; j < len; j++)
        {
            if (code[i][j] != 0)
            {
                printf("%c", code[i][j]);
            }
        }
    }
    printf("\n");
    // For decryption
    printf("Decrypted message:");
    count = 0;
    j = 0;
    while (j < len)
    {
        if (count % 2 == 0)
        {
            for (i = 0; i < rail; i++)
            {
                printf("%c", code[i][j]);
                j++;
            }
        }
        else
        {
            for (i = rail - 2; i > 0; i--)
            {
                printf("%c", code[i][j]);
                j++;
            }
        }
        count++;
    }

    return 0;
}