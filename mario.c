#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int height, i, j, k;
    do
    {
        height = get_int("(1-8) Enter the height= ");
    }
    while (height < 1 || height > 8);
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < height - (i + 1); j++)
        {
            printf(" "); // spaces
        }
        for (k = 0; k < i + 1; k++)
        {
            printf("#"); // backslashes
        }
        printf("\n");
    }
}
