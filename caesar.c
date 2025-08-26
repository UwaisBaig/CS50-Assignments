#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2) // return and input validation checks if key is greater than 1
    {
        printf("Usage : ./caesar key \n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++) // checks for if key is digit or not
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage : ./caesar key \n");
            return 1;
        }
    }

    if (argc == 0) // message for no key provided
    {
        printf("Usage : ./caesar key \n");
        return 0;
    }

    int key = atoi(argv[1]) % 26;                 // key varibale indication
    string plaintext = get_string("plaintext: "); // plaintext formation and passing

    printf("ciphertext: ");

    int plaintext_length = strlen(plaintext);
    for (int i = 0; i < plaintext_length; i++)
    {
        printf("%c", rotate(plaintext[i], key)); // call  to rotate function
    }
    printf("\n");
}

// rotate function
char rotate(char c, int key)
{
    if (isupper(c)) // calculations for uppercase char
    {
        c = ((c - 'A' + key) % 26) + 'A';
    }
    else if (islower(c)) // calculations for lowercase char
    {
        c = ((c - 'a' + key) % 26) + 'a';
    }
    return c;
}
