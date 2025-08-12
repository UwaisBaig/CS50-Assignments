#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennys(int cents);

int main(void)
{
    int cents;
    do
    {
        cents = get_int("Change Owed: ");
    }
    while (cents < 0);

    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);

    int dimes = calculate_dimes(cents);
    cents = cents - (dimes * 10);

    int nickels = calculate_nickels(cents);
    cents = cents - (nickels * 5);

    int pennys = calculate_pennys(cents);
    cents = cents - (pennys * 1);

    int coins = quarters + dimes + nickels + pennys;
    printf("minimum coins=%i\n", coins);
}

int calculate_quarters(int cents) //function for quarters

{
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents = cents - 25;
    }
    return quarters;
}

int calculate_dimes(int cents) //function for dimes

{
    int dimes = 0;
    while (cents >= 10)
    {
        dimes++;
        cents = cents - 10;
    }
    return dimes;
}

int calculate_nickels(int cents) //function for nickels

{
    int nickels = 0;
    while (cents >= 5)
    {
        nickels++;
        cents = cents - 5;
    }
    return nickels;
}

int calculate_pennys(int cents)  //function for pennys

{
    int pennys = 0;
    while (cents >= 1)
    {
        pennys++;
        cents = cents - 1;
    }
    return pennys;
}
