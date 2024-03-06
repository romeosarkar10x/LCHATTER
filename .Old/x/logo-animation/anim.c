#include <stdio.h>
#include <locale.h>
// const char colour_sequence[][] = {"\e[30m"};
void print_column (void *_mat, size_t rows, size_t cols, int _column)
{
    
}
void animate (void *_mat, size_t _rows, size_t _cols)
{
    char (*m)[_cols] = _mat;

}
int rows, cols;
void scan_logo ()
{
    FILE *fptr = fopen ("logo.txt", "r");
    char tmp;
    int r = 0, c = 0;
    while ((tmp = fgetc (fptr)) != EOF)
    {
        if (tmp == '\n')
        {
            r++;
            c = 0;

        }
        c++;
    }
}
int main ()
{
    
    return 0;
}