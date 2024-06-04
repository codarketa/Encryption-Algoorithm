#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

void lowercase(char plain[], int s)
{
	int i;
	for (i = 0; i < s; i++)
	{
		if (plain[i] > 64 && plain[i] < 91)
			plain[i] += 32;
	}
}
int removeSpaces(char *plain, int s)
{
	int i, count = 0;
	for (i = 0; i < s; i++)
		if (plain[i] != ' ')
			plain[count++] = plain[i];
	plain[count] = '\0';
	return count;
}
void generateKeyTable(char key[], int d, char keyT[5][5])
{
	int i, j, k, flag = 0, *dicty;
	dicty = (int *)calloc(26, sizeof(int));
	for (i = 0; i < d; i++)
	{
		if (key[i] != 'j')
			dicty[key[i] - 97] = 2;
	}

	dicty['j' - 97] = 1;

	i = 0;
	j = 0;

	for (k = 0; k < d; k++)
	{
		if (dicty[key[k] - 97] == 2)
		{
			dicty[key[k] - 97] -= 1;
			keyT[i][j] = key[k];
			j++;
			if (j == 5)
			{
				i++;
				j = 0;
			}
		}
	}

	for (k = 0; k < 26; k++)
	{
		if (dicty[k] == 0)
		{
			keyT[i][j] = (char)(k + 97);
			j++;
			if (j == 5)
			{
				i++;
				j = 0;
			}
		}
	}
}
void search(char keyT[5][5], char a, char b, int arr[])
{
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';

	for (i = 0; i < 5; i++)
	{

		for (j = 0; j < 5; j++)
		{

			if (keyT[i][j] == a)
			{
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyT[i][j] == b)
			{
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}

int mod5(int a) { return (a % 5); }
int prepare(char str[], int ptrs)
{
	if (ptrs % 2 != 0)
	{
		str[ptrs++] = 'z';
		str[ptrs] = '\0';
	}
	return ptrs;
}
void encrypt(char str[], char keyT[5][5], int s)
{
	int i, a[4];

	for (i = 0; i < s; i += 2)
	{

		search(keyT, str[i], str[i + 1], a);

		if (a[0] == a[2])
		{
			str[i] = keyT[a[0]][mod5(a[1] + 1)];
			str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
		}
		else if (a[1] == a[3])
		{
			str[i] = keyT[mod5(a[0] + 1)][a[1]];
			str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
		}
		else
		{
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

void encryptByPlayfairCipher(char str[], char key[])
{
	char s, d, keyT[5][5];
	d = strlen(key);
	d = removeSpaces(key, d);
	lowercase(key, d);
	s = strlen(str);
	lowercase(str, s);
	s = removeSpaces(str, s);

	s = prepare(str, s);

	generateKeyTable(key, d, keyT);

	encrypt(str, keyT, s);
}

int main()
{
	char str[SIZE], key[SIZE];
	strcpy(key, "Monarchy");
	printf("Keyword: %s\n", key);
	strcpy(str, "cryptography");
	printf("Plain text is: %s\n", str);

	encryptByPlayfairCipher(str, key);

	printf("Cipher text is: %s\n", str);

	return 0;
}