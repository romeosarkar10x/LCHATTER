#include <stdio.h>
#include <wchar.h>
int main ()
{
    // wchar_t c = 'abc';
    // wchar
    freopen ("output.txt", "w", stdout);
    char arr[] = {'1', '2', '2', '3', '4'};
    printf ("[%lc]", *((int *) (arr)));
    // // wprintf ("%c", )
    // printf ("\e[1;31mhello world🤣😨\e[m\n");
    
    return 0;
}