#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool checkValidLength(string key);
bool checkValidPattern(string key);

int main(int argc, string argv[])
{
    // check single CLI argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check if key is valid
    bool isValidLength = checkValidLength(argv[1]);
    if (!isValidLength)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    bool isValidPattern = checkValidPattern(argv[1]);
    if (!isValidPattern)
    {
        printf("Key must contain 26 characters exactly once.\n");
        return 1;
    }

    // prompt user for plain text
    string plainText = get_string("plaintext:  ");

    // convert the plain to ciphertext
    int len = strlen(plainText);
    char ciphertext[len];
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        char c = plainText[i];
        if (isalpha(c))
        {
            if (isupper(c))
            {
                ciphertext[index] = toupper(argv[1][c - 'A']);
            }
            else
            {
                ciphertext[index] = tolower(argv[1][c - 'a']);
            }
        }
        else
        {
            ciphertext[index] = plainText[i];
        }
        index++;
    }

    // return the ciphertext
    printf("ciphertext: ");
    for (int j = 0; j < len; j++)
    {
        printf("%c", ciphertext[j]);
    }
    printf("\n");
}

bool checkValidLength(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    }
    return true;
}

bool checkValidPattern(string key)
{
    bool isValid = true;
    // check key must be letter
    // check key contain each letter exactly once
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha(key[i]))
        {
            for (int j = i + 1; j < n; j++)
            {
                if (tolower(key[i]) == tolower(key[j]))
                {
                    isValid = false;
                    return isValid;
                }
            }
        }
        else
        {
            isValid = false;
            return isValid;
        }
    }

    return isValid;
}
