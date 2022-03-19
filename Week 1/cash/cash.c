#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);

}

int get_cents(void)
{
    int cents = 0; // initialise variable
    // Get user input for how many cents
    do
    {
        cents = get_int("How many cents is the customer owed? ");
    }
    //reject anything other than a positive number
    while (cents < 1);
    return (cents);
}

int calculate_quarters(int cents)
{
    int quarters = 0; // initialise variable
    //if remaining cents are over 24 then increase the number of quarters by cents/25
    if (cents > 24)
    {
        quarters += cents / 25;
    }
    return (quarters);
}

int calculate_dimes(int cents)
{
    int dimes = 0; // initialise variable
    //if remaining cents are over 9 then increase the number of dimes by cents/10
    if (cents > 9)
    {
        dimes += cents / 10;
    }
    return (dimes);
}

int calculate_nickels(int cents)
{
    int nickels = 0; // initialise variable
    //if remaining cents over 24 then increase the number of nickels by cents/5
    if (cents > 4)
    {
        nickels += cents / 5;
    }
    return (nickels);
}

int calculate_pennies(int cents)
{
    int pennies = 0; // initialise variable
    // increase pennies by any remaining cents
    if (cents > 0)
    {
        pennies += cents;
    }
    return (pennies);
}
