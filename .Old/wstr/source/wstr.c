#include "../header/wstr.h"


/* creates a wrapper on a c-style string */
wstr wrap_str (char *_str, int _siz)
{
    wstr s;
    s.p = _str;
    s.siz = _siz;
    return s;
}
