#ifndef BOX_H
#define BOX_H
#if defined(__cplusplus)
extern "C"
{
#endif

    extern char str_arr_[12][8];
    void _set_box_str_arr (const char *_str_arr[]);
    const char *_box ();

#if defined(__cplusplus)
}
#endif
#endif