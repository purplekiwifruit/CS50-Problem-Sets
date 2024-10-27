#include <cs50.h>
#include <stdio.h>
#include <string.h>

int getSum(long input);
int getTotal(int sum, long input);
string getCard(long input);
int getLength(long input);
int getFirstTwo(long input);

int main(void)
{
    long input = get_long("Number: ");
    int length = getLength(input);

    // check length
    if (length != 13 && length != 14 && length != 15 && length != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        // check last digit to be zero
        int sum = getSum(input);
        int total = getTotal(sum, input);

        if (total % 10 == 0)
        {
            printf("%s\n", getCard(input));
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

int getSum(long input)
{
    int sum = 0;
    while (input / 10 > 0)
    {
        input = input / 10;
        int remainder = input % 10;

        int multiply = remainder * 2;

        while (multiply > 9)
        {
            int a = multiply % 10;
            sum += a;
            multiply = multiply / 10;
        }

        sum += multiply;

        input = input / 10;
    }

    return sum;
}

int getTotal(int sum, long input)
{
    int total = sum;

    while (input > 0)
    {
        total += input % 10;
        input = input / 100;
    }

    return total;
}

string getCard(long input)
{
    int length = getLength(input);

    int first2Digits = getFirstTwo(input);

    while (input > 9)
    {
        input = input / 10;
    }

    int lastDigit = input;

    if (lastDigit == 5 && length == 16 &&
        (first2Digits == 51 || first2Digits == 52 || first2Digits == 53 || first2Digits == 54 ||
         first2Digits == 55))
    {
        return "MASTERCARD";
    }
    else if ((lastDigit == 4 && length == 13) || (lastDigit == 4 && length == 16))
    {
        return "VISA";
    }
    else if (lastDigit == 3 && length == 15 && (first2Digits == 32 || first2Digits == 37))
    {
        return "AMEX";
    }
    else
    {
        return "INVALID";
    }
}

int getLength(long input)
{
    int count = 0;
    while (input > 0)
    {
        input = input / 10;
        count++;
    }

    return count;
}

int getFirstTwo(long input)
{
    while (input > 100)
    {
        input = input / 10;
    }

    return input;
}
