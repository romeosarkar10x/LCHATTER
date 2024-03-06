#include <stdio.h>
#include <conio.h>
int main ()
{
    for (; ; )
    {
        int c = getch ();
        printf ("[%hhd;%hhx]", c, c);
    }
    return 0;
}