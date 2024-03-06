#ifndef ERROR_H
#define ERROR_H


#define ERROR(Try, fName, Message, Approach)\
if (Try)\
{\
    printf ("\nIn function \'" #fName "\': \033[31merror:\033[m " Message "\n");\
    Approach;\
}

#define ERROR_V(Try, fName, Message, Approach, ...)\
if (Try)\
{\
    printf ("\nIn function \'" #fName "\': \033[31merror:\033[m " Message "\n", __VA_ARGS__);\
    Approach;\
}

#endif