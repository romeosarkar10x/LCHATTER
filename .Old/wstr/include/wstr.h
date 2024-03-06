#ifndef STR_H
#define STR_H

typedef struct wstr
{
    int siz;
    char *p;
} wstr;

wstr wrap_str (char *_str, int _siz);





#endif