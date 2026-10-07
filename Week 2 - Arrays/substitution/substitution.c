#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        // Check if character is a letter
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        }

        // Check for duplicate characters
        for (int j = i + 1; j < 26; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Key must not contain duplicate characters.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext:  ");

    printf("ciphertext: ");

    // Encrypt each character of the text
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isupper(plaintext[i]))
        {
            // Calculate index (0 to 25) and print corresponding uppercase key letter
            int index = plaintext[i] - 'A';
            printf("%c", toupper(key[index]));
        }
        else if (islower(plaintext[i]))
        {
            // Calculate index lowercase key letter
            int index = plaintext[i] - 'a';
            printf("%c", tolower(key[index]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}
