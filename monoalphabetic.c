#include <stdio.h>
#include <string.h>
void encrypt(char pt[], char k[], char ci[])
{
    int i;
    for (i = 0; pt[i] != '\0'; ++i)
    {
        if (pt[i] >= 'a' && pt[i] <= 'z')
        {
            ci[i] = k[pt[i] - 'a'];
        }
        else if (pt[i] >= 'A' && pt[i] <= 'Z')
        {
            ci[i] = k[pt[i] - 'A'];
        }
        else
        {
            ci[i] = pt[i];
        }
    }
    ci[i] = '\0';
}

void decrypt(char ci[], char k[], char pt[])
{
    int i, j;
    char ivn_k[26];
    for (i = 0; i < 26; ++i)
    {
        ivn_k[k[i] - 'A'] = 'A' + i;
    }

    for (i = 0; ci[i] != '\0'; ++i)
    {
        if (ci[i] >= 'a' && ci[i] <= 'z')
        {
            pt[i] = ivn_k[ci[i] - 'a'];
        }
        else if (ci[i] >= 'A' && ci[i] <= 'Z')
        {
            pt[i] = ivn_k[ci[i] - 'A'];
        }
        else
        {
            pt[i] = ci[i];
        }
    }
    pt[i] = '\0';
}

int main()
{
    char pt[100], ci[100];
    char k[27] = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

    printf("Enter plaintext: ");
    fgets(pt, sizeof(pt), stdin);

    pt[strcspn(pt, "\n")] = '\0';

    encrypt(pt, k, ci);

    printf("Ciphertext is: %s\n", ci);

    decrypt(ci, k, pt);

    printf("Plain text after decryption is:%s\n", pt);

    return 0;
}