#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string p);

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; //points for scrabble

int main(void)
{
    string p1 = get_string("Player 1's Word =  ");   //getting the string from player 1
    string p2 = get_string("Player 2's Word =  ");   //getting the string form player 2

    int sc1 = calculate_score(p1);
    int sc2 = calculate_score(p2);

    if (sc1 > sc2)                            //the return on the result
    {
        printf("The Player1 wins! \n");
    }
    else if (sc2 > sc1)
    {
        printf("The Player2 wins! \n");
    }
    else
    {
        printf("Tie ! \n");
    }
}

int calculate_score(string p)          //function to calculate the scores, the words to points
{
    int sc = 0, len = strlen(p);

    for (int i = 0; i < len; i++)
    {
        char ch = toupper(p[i]);       //convert every word to uppercase

        if (ch >= 'A' && ch <= 'Z')
        {
            sc += POINTS[ch - 'A'];
        }
    }
    return sc;
}
