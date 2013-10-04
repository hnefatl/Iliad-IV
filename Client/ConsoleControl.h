#ifndef _CONSOLECONTROL_H
#define _CONSOLECONTROL_H

#include <iostream>
#include <windows.h>

enum CONSOLECOLOUR
{
    BLACK       = 0,
    DARK_BLUE   = 1,
    DARK_GREEN  = 2,
    TEAL        = 3,
    DARK_RED    = 4,
    DARK_PURPLE = 5,
    GOLD        = 6,
    GREY        = 7,
    DARK_WHITE  = 8,
    BLUE        = 9,
    GREEN       = 10,
    CYAN        = 11,
    RED         = 12,
    PURPLE      = 13,
    YELLOW      = 14,
    WHITE       = 15
};

extern void SetColour(CONSOLECOLOUR foreground, CONSOLECOLOUR background);

extern void SetCursor(int x, int y);

extern void Clear();

extern void EnableCursor(bool Shown);

#endif