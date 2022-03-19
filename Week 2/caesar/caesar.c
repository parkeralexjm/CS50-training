#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

bool only_digits(string s);
char rotate(char c, int i);

int main(int argc, string argv[])
{

//close the program if the key input is more than a single argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

//check that the key is in the correct format
    bool digit_check = only_digits(argv[1]);

    if (digit_check == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

//get an input called plaintext from the user
    string plaintext = get_string("plaintext: ");

//change the key to an int
    int key = atoi(argv[1]);

//print ciphertext by running through array plaintext and change each char by the rotate function
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char j = rotate(plaintext[i], key);
        printf("%c", j);
    }
    printf("\n");
}

//check the input string is only a digit
bool only_digits(string s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
//function rotate changes char by positions equal to the key
char rotate(char c, int i)
{
    //if the char input is "a" add "i" to its integer then divide by 26 and return the remainder
    int d = 0;
    int e = 0;
    if (islower(c) && isalpha(c))
    {
        d = c - 'a';
        e = (d + i) % 26;
        return e + 'a';
    }
    else if (isupper(c) && isalpha(c))
    {
        d = c - 'A';
        e = (d + i) % 26;
        return e + 'A';
    }
    else
    {
        return c;
    }

}







//print ciphertext by running through array plaintext and change each char by the rotate function

