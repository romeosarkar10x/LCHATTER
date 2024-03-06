#include <stdio.h>
#include <string.h>
#include "../header/box.h"
#include "../header/error.h"
// #include "../header/warn.h"

/**
TestBox:
┌─┬─┬─┬─┬───────┐
├─┼─┼─┼─┤       │
├─┼─┼─┴─┼───┐   │
├─┼─┤   │   │   │
├─┴─┼───┼─┬─┼───┤
│   │   ├─┼─┤   │
│   └───┼─┴─┘   │
│       │       │
└───────┴───────┘
┌──────────┬───┐
│ARRAY[0x0]│"┌"│
├──────────┼───┤
│ARRAY[0x1]│"┐"│
├──────────┼───┤
│ARRAY[0x2]│"├"│
├──────────┼───┤
│ARRAY[0x3]│"┤"│
├──────────┼───┤
│ARRAY[0x4]│"└"│
├──────────┼───┤
│ARRAY[0x5]│"┘"│
├──────────┼───┤
│ARRAY[0x6]│"┬"│
├──────────┼───┤
│ARRAY[0x7]│"┴"│
├──────────┼───┤
│ARRAY[0x8]│"─"│
├──────────┼───┤
│ARRAY[0x9]│"│"│
├──────────┼───┤
│ARRAY[0xA]│"┼"│
├──────────┼───┤
│ARRAY[0xB]│" "│
└──────────┴───┘
0─6─6─6─6───────1
2─A─A─A─3       │
2─A─A─7─A───1   │
2─A─3   │   │   │
2─7─A───A─6─A───3
│   │   2─A─3   │
│   4───A─7─5   │
│       │       │
4───────7───────5
BoxDimensions = (9Rows) * (17Columns)
i.e [(n)Rows] * [(2n-1)Columns] 
*/
/**/ 

#define N 12
#define STR_SIZ 8
#define STR_LEN (STR_SIZ-1)
char str_arr_[N][STR_SIZ] = {SET(L,L)};


void _set_box_str_arr (const char *_str_arr[])
{
    ERROR (NULL == _str_arr, _set_box_str_arr, "_str_arr is (null)", return);
    for (size_t i = 0; i < N; i++)
    {
        ERROR_V (NULL == _str_arr[i], _set_box_str_arr, "_str_arr[%zd] is (null)", continue, i);
        /* strncpy copies a max of 'n' chars, inc. the '\0' char */
        strncpy (str_arr_[i], _str_arr[i], STR_LEN);
    }
    return;
}


#define REP2(...) __VA_ARGS__, __VA_ARGS__
#define REP3(...) REP2(__VA_ARGS__), __VA_ARGS__
#define REP4(...) REP2(__VA_ARGS__), REP2(__VA_ARGS__)
#define REP5(...) REP2(__VA_ARGS__), REP3(__VA_ARGS__)
#define REP7(...) REP3(__VA_ARGS__), REP4(__VA_ARGS__)

#define ROWS 9
#define COLUMNS 17

#define P(_Offset) (str_arr_[_Offset])
static const char *box_[ROWS][COLUMNS] = 
{
    {P(0x0), REP4(P(0x8), P(0x6)), REP7(P(0x8)), P(0x1)},
    {P(0x2), REP3(P(0x8), P(0xA)), P(0x8), P(0x3), REP7(P(0xB)), P(0x9)},
    {P(0x2), REP2(P(0x8), P(0xA)), P(0x8), P(0x7), P(0x8), P(0xA), REP3(P(0x8)), P(0x1), REP3(P(0xB)), P(0x9)},
    {P(0x2), P(0x8), P(0xA), P(0x8), P(0x3), REP3(REP3(P(0xB)), P(0x9))},
    {P(0x2), P(0x8), P(0x7), P(0x8), P(0xA), REP3(P(0x8)), P(0xA), P(0x8), P(0x6), P(0x8), P(0xA), REP3(P(0x8)), P(0x3)},
    {REP2(P(0x9), REP3(P(0xB))), P(0x2), P(0x8), P(0xA), P(0x8), P(0x3), REP3(P(0xB)), P(0x9)},
    {P(0x9), REP3(P(0xB)), P(0x4), REP3(P(0x8)), P(0xA), P(0x8), P(0x7), P(0x8), P(0x5), REP3(P(0xB)), P(0x9)},
    {REP2(P(0x9), REP7(P(0xB))), P(0x9)},
    {P(0x4), REP7(P(0x8)), P(0x7), REP7(P(0x8)), P(0x5)}
};

static char buf_[1024];
static int idx_; /* =0 */
static void scpy (const char *_str)
{
    ERROR (NULL == _str, scpy, "_str is (null)", return);
    for (int i = 0; _str[i]; )
    {
        buf_[idx_++] = _str[i++];
    }
    buf_[idx_] = '\0';
    return;
}
const char *_box ()
{
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLUMNS; j++)
        {
            scpy (box_[i][j]);
        }
        scpy ("\n");
    }
    idx_ = 0;
    return buf_;
}