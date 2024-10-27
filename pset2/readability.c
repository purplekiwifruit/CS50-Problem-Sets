#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int compute_data(string input, int type);
int main(void)
{
    // Prompt the user for some text
    string input = get_string("Text: ");

    // Count the number of letters[0], words[1], and sentences[2] in the text
    int letterCount = compute_data(input, 0);
    int wordCount = compute_data(input, 1);
    int senCount = compute_data(input, 2);

    // Compute the Coleman-Liau index
    float index = 0.0588 * ((float) letterCount / wordCount * 100) -
                  0.296 * ((float) senCount / wordCount * 100) - 15.8;

    // Print the grade level
    if (index > 16.0)
    {
        printf("Grade 16+\n");
    }
    else if (index > 1)
    {
        printf("Grade %i\n", (int) round(index));
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

int compute_data(string input, int type)
{

    int count = 0;

    if (type == 0)
    {
        for (int i = 0, n = strlen(input); i < n; i++)
        {
            if ((input[i] >= 'A') && (input[i] <= 'z'))
            {
                count++;
            }
        }
        return count;
    }
    else if (type == 1)
    {
        for (int i = 0, n = strlen(input); i < n; i++)
        {

            if (input[i] == 32)
            {
                count++;
            }
        }
        return count + 1;
    }
    else
    {
        for (int i = 0, n = strlen(input); i < n; i++)
        {

            if (input[i] == '!' || input[i] == '.' || input[i] == '?')
            {
                count++;
            }
        }
        return count;
    }
}
