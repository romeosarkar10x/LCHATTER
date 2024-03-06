#include <stdio.h>
#include <conio.h>
#include <unistd.h>
// #include <windows.h>
int main ()
{
    for (; ; )
    {
        int k = kbhit ();
        if (k)
        {
            printf ("+");
            char tmp = getch ();
            // if ('\r' != tmp)
            // {
                printf ("[%2hhx]", tmp);
            // }
        }
        // Sleep (100);
    }
    return 0;
}