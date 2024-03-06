#include <stdio.h>
#include "../header/anim.h"
#include "../header/load.h"
void print_column_ ()
{
    
}



void _animate ()
{
    struct dim2 dim = load_ ("source/logo.txt");
    printf ("[%d;%d]\n", dim.x, dim.y);
    return;

}