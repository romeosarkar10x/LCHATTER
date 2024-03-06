#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../header/anim.h"
#include "../header/error.h"
#include "../header/dim.h"
#include "../../wstr/include/wstr.h"

#define BUF_SIZ (16 * 1024)
static char buffer_[BUF_SIZ];
static bool flag_; /* =false */
static int buffer_idx_; /* =0 */


/* considering a max of 256 lines to load */
#define SIZ 256
wstr str_[SIZ];
static int str_idx_; /* =0 */


/* loads data from a file to buffer_*/
dim2 load_ (const char *_fname)
{
    dim2 d = {0, 0};
    FILE *fptr = fopen (_fname, "r");
    FATAL_ERROR (NULL == fptr, load_, "could not open file \'%s\'", exit (0), _fname);
    int lvc /* last valid character */ = EOF, p /* previous */ = EOF, c /* current */, cnt = 0, nlcnt /* newline count*/ = 0;
    for (; (c = getc (fptr)) != EOF; p = c)
    {
        if (c == '\n')
        {
            if (p != '\n' && p != EOF)
            {
                str_[str_idx_++] = wrap_str (buffer_ + (buffer_idx_ - cnt), cnt);
                d.x = ((d.x < cnt) ? cnt : d.x);
                buffer_[buffer_idx_++] = '\0';
                d.y++;
            }
            else
            {
                if (lvc != EOF)
                {
                    nlcnt++;
                }
            }
            cnt = 0;
        }
        else
        {
            for (int i = 0; i < nlcnt; i++)
            {
                str_[str_idx_++] = wrap_str (buffer_ + (buffer_idx_ - cnt), cnt);
                buffer_[buffer_idx_++] = '\0';
                d.y++;
            }
            cnt++;
            lvc = c;
            nlcnt = 0;
            buffer_[buffer_idx_++] = ((char) (c));
        }

        for (int i = 0; i < 100; i++)
        {
            if (buffer_[i] == 0)
            {
                printf ("\e[90m!\e[m");
            }
            else if (buffer_[i] == 1)
            {
                printf ("|");
            }
            else
            {
                printf ("\e[32m%c\e[m", buffer_[i]);
            }
        }
        printf ("\n");


    }
    if (cnt)
    {
        str_[str_idx_++] = wrap_str (buffer_ + (buffer_idx_ - cnt), cnt);
        d.x = ((d.x < cnt) ? cnt : d.x);
        buffer_[buffer_idx_++] = '\0';
        d.y++;

        for (int i = 0; i < 100; i++)
        {
            if (buffer_[i] == 0)
            {
                printf ("\e[90m!\e[m");
            }
            else if (buffer_[i] == 1)
            {
                printf ("|");
            }
            else
            {
                printf ("\e[32m%c\e[m", buffer_[i]);
            }
        }
        printf ("\n");

        printf ("here\n");

    }
    fclose (fptr);
    printf ("\e[31m%d,%d\e[m\n", str_idx_, d.y);
    for (int i = 0; i < d.y; i++)
    {
        printf ("[%s]:%d\n", str_[i].p, str_[i].siz);
    }
    flag_ = 1;
    return d;
}




