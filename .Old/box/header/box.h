#ifndef BOX_H
#define BOX_H

/** 
Nomenclature:
1)based on Weight:
    L=Light;H=Heavy
2)based on Direction:
    H=Horizontal;V=vertical
    L=Left;R=Right
    U=Up;D=Down

Format: [HorizontalProperty][VerticalProperty]
Property=[Weight][Direction]

Examples:
"┨"=LLHV=[Light][Left][Heavy][Vertical]
"┏"=HRHD=[Heavy][Right][Heavy][Down]
*/

/* all strings must render in one terminal cell */
// /** SET(L,L): */
// #define LH      "─"
// #define LV      "│"
// #define LLLD    "┐"
// #define LRLD    "┌"
// #define LRLV    "├"
// #define LLLV    "┤"
// #define LHLD    "┬"
// #define LHLU    "┴"
// #define LHLV    "┼"
// #define LRLU    "└"
// #define LLLU    "┘"
// /** SET(L,L): */
// #define LH      "─"
// #define LV      "│"
// #define LLLD    "┐"
// #define LRLD    "┌"
// #define LRLV    "├"
// #define LLLV    "┤"
// #define LHLD    "┬"
// #define LHLU    "┴"
// #define LHLV    "┼"
// #define LRLU    "└"
// #define LLLU    "┘"

/** SET(L,L): */
#define LH      "─"
#define LV      "│"
#define LLLD    "╮"
#define LRLD     "╭"
#define LRLV    "├"
#define LLLV     "┤"
#define LHLD    "┬"
#define LHLU     "┴"
#define LHLV     "┼"
#define LRLU    "╰"
#define LLLU    "╯"


/** set(H,H) :*/
# define HH "━"
# define HV "┃"
# define HLHD "┓"
# define HRHD "┏"
# define HRHV  "┣"
# define HLHV "┫"
# define HHHD "┳"
# define HHHU  "┻"
# define HHHV "╋"
# define HRHU  "┗"
# define HLHU "┛"

/* ** set(L,H) :*/
# define LH "─"
# define HV "┃"
# define LLHD "┒"
# define LRHD "┎"
# define LRHV  "┠"
# define LLHV "┨"
# define LHHD "┰"
# define LHHU  "┸"
# define LHHV "╂"
# define LRHU  "┖"
# define LLHU "┚"

/* ** set(H,L) :*/
# define HH    "━"
# define LV    "│"
# define HLLD  "┑"
# define HRLD  "┍"
# define HRLV  "┝"
# define HLLV  "┥"
# define HHLD  "┯"
# define HHLU  "┷"
# define HHLV  "┿"
# define HRLU  "┕"
# define HLLU  "┙"


/**
StringArray:
char ARRAY[][8] = {"┌", "┐", "├", "┤", "└", "┘", "┬", "┴", "─", "│", "┼", " "};
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
*/


#define Fill " "

#define SET(W1,W2)\
    W1 ## R ## W2 ## D, W1 ## L ## W2 ## D,\
    W1 ## R ## W2 ## V, W1 ## L ## W2 ## V,\
    W1 ## R ## W2 ## U, W1 ## L ## W2 ## U,\
    W1 ## H ## W2 ## D, W1 ## H ## W2 ## U,\
    W1 ## H, W2 ## V,\
    W1 ## H ## W2 ## V, Fill





#endif