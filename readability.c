#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string context);
int count_words(string context);
int count_sentence(string context);
int index_grade(int letters, int sentences, int words);

int main(void)
{
    string context = get_string(" Enter the paragraph =");

    int letters = count_letters(context);
    int words = count_words(context);
    int sentences = count_sentence(context);
    int grade = index_grade(letters, sentences, words);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade == 1)
    {
        printf(" Grade 1\n");
    }
    else if (grade == 2)
    {
        printf(" Grade 2\n");
    }
    else if (grade == 3)
    {
        printf(" Grade 3\n");
    }
    else if (grade == 4)
    {
        printf(" Grade 4\n");
    }
    else if (grade == 5)
    {
        printf(" Grade 5\n");
    }
    else if (grade == 6)
    {
        printf(" Grade 6\n");
    }
    else if (grade == 7)
    {
        printf(" Grade 7\n");
    }
    else if (grade == 8)
    {
        printf(" Grade 8\n");
    }
    else if (grade == 9)
    {
        printf(" Grade 9\n");
    }
    else if (grade == 10)
    {
        printf(" Grade 10\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string context)
{
    int l = 0;
    int len = strlen(context);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(context[i]))
        {
            l++;
        }
    }
    return l;
}

int count_words(string context)
{
    int w = 1;
    int len = strlen(context);
    for (int i = 0; i < len; i++)
    {
        if (isspace(context[i]))
        {
            w++;
        }
    }
    return w;
}

int count_sentence(string context)
{
    int s = 0;
    int len = strlen(context);
    for (int i = 0; i < len; i++)
    {
        if (context[i] == '.' || context[i] == '!' || context[i] == '?')
        {
            s++;
        }
    }
    return s;
}

int index_grade(int letters, int sentences, int words)
{
    float L = (letters / (float) words * 100);
    float S = (sentences / (float) words * 100);

    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}
