#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Assign a user input called height and assign it to integer variable called "n"
    int n;
    do
    {
        //get input from user for the height of the pyramid
        n = get_int("Height: ");
    }
    //Keep asking the user for an input if the user types a number that is below 1 or above 8
    while (n < 1 || n > 8);
    //use the user input i in a loop starting with 1
    for (int i = 1; i < n + 1 ; i++)
    {
        //print spaces in front of the hash marks equal to the user input minus i + 1
        for (int k = 0; k < n - i ; k++)
        {
            printf(" ");
        }
        //print hash equal to the row that it is on
        for (int j = 0; j < i ; j++)
        {
            printf("#");
        }
        //print double space after hashes
        printf("  ");
        //print hashes in pyramid equal to the row number
        for (int l = 0; l < i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}