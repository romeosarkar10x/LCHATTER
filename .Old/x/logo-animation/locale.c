#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
// #include <localcharset.h>
// #include <
int main ()
{
    // printf ("%s\n", locale_charset ());
    char *locale;
    // threadLo
    // localeinfo_struct linfo;
    system ("chcp");
    printf("The current locale is %s\n");
    // getloca
    locale = setlocale (LC_ALL, "en_US.UTF-8");
    system ("chcp 65001");
    printf("The current locale is %s\n",locale);
    printf ("%s", "😨🤣");

    return 0;
}