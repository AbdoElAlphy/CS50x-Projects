#include <stdio.h>

int main(void)
{
    int cents;

    do
    {
        printf("Change owed: ");

        if (scanf("%d", &cents) != 1)
        {
            while (getchar() != '\n')
                 ;
            cents = -1;
        }
    }
    while (cents < 0);

    int quarters = cents / 25;
    cents = cents % 25;

    int dimes = cents / 10;
    cents = cents % 10;

    int nickels = cents / 5;
    cents = cents % 5;

    int pennies = cents;

    printf("%d\n", quarters + dimes + nickels + pennies);

    return 0;
}
