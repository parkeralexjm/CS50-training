#include <cs50.h>
#include <stdio.h>
#include <math.h>

void invalid(void)
{
    printf("INVALID\n");
}

int main(void)
{
    long card_number; //declaring variable for credit card number
    long check_number;
    long checksum;
    int count = 0;
    long card_length = 0;
        //get input from user for credit card number

    card_number = get_long("What is your credit card number: ");
    check_number = card_number;
    do
    {
        check_number = check_number / 10;
        count++;
    }
    while (check_number > 100);
    card_length = count + 2;

    // use the card_number to calculate the checksum



    // view the check_number (which is now 2 digits) and assign it to VISA, MASTERCARD, AMEX or invalid
    // parameters for VISA
    if (check_number > 39 && check_number < 50)
    {
        //check length of number
        if (card_length == 13 || card_length == 16)
        {
            printf("VISA\n");
        }
        else
        {
            invalid();
        }
    }
    // parameters for the MASTERCARD
    else if (check_number > 49 && check_number < 56 && card_length == 16)
        {
            printf("MASTERCARD\n");
        }
    // parametes for the AMEX
    else if (check_number == 34 || check_number == 37)
    {
        //check length of number
        if (card_length == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}
