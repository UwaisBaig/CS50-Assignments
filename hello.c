#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Whats Your Name ? \n");
    printf("hello, %s\n", name);
}
