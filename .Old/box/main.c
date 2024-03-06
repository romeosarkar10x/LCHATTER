#include <stdio.h>
#include <string.h>
#include "include/box.h"
int main ()
{

    // const char *A[] = {".", ",", "}", "{", "`", "\'", "+", "*", "~", ":", "|", " "};
    const char *B[] = {".", ",", "}", NULL, "`", "\'", "+", "*", "~", ":", "|", " "};
    const char *B2[] = {"+", "+", "+", "+", "+", "+", "+", "+", "~", "|", "|", " "};

    printf ("%s", _box ());

    _set_box_str_arr (B);
    
    printf ("%s", _box ());
    _set_box_str_arr (B2);
    printf ("%s", _box ());



    
    // printf ("\e[102m😫\e[m");

    return 0;
}