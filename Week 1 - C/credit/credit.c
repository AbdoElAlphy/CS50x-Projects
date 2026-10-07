#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");

    // Variables for Luhn's Algorithm
    int sum_multiplied = 0;
    int sum_other = 0;
    long temp = number;
    int length = 0;
    int first_two_digits = 0;
    bool is_alternate_digit = false;

    while (temp > 0)
    {
        int digit = temp % 10;

        if (is_alternate_digit)
        {
            int multiplied = digit * 2;

            // Add the digits of the products together
            sum_multiplied += (multiplied % 10) + (multiplied / 10);
        }
        else
        {
            sum_other += digit;
        }

        // Store the first two digits to identify the card brand later
        if (temp > 9 && temp < 100)
        {
            first_two_digits = temp;
        }

        // Toggle the alternate flag for the next digit
        is_alternate_digit = !is_alternate_digit;

        temp /= 10;

        length++;
    }

    int total_sum = sum_multiplied + sum_other;

    // Check if the total modulo 10 is not 0 (Invalid card)
    if (total_sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    int first_digit = first_two_digits / 10;

    // Check card type based on length and starting digits
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        // If it passes Luhn's algorithm but doesn't match any card format
        printf("INVALID\n");
    }

    return 0;
}
