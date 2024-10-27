#include <cs50.h>
#include <stdio.h>

void printEnd(int level);
void printStart(int level, int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    for (int i = 0; i < height; i++)
    {
        printStart(i, height);
        printf("  ");
        printEnd(i);
        printf("\n");
    }
}

void printEnd(int level)
{
    for (int i = 0; i <= level; i++)
    {
        printf("#");
    }
}

void printStart(int level, int height)
{
    for (int i = height - 1; i >= 0; i--)
    {
        if (i > level)
        {
            printf(" ");
        }
        else
        {
            printf("#");
        }
    }
}
