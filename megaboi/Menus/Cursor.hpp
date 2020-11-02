#ifndef __CURSOR_H
#define __CURSOR_H

#include "../header.hpp"

inline void printCursor(MCUFRIEND_kbv& tft, const byte cursor, const int menuColor) {
    for (int i = 0; i <= MAX_MENU_NUM; i++) {
        tft.drawRect(0, ((tft.height() / MAX_MENU_NUM) * i) + 1, tft.width(), (tft.height() / MAX_MENU_NUM) - 1, menuColor);
        tft.drawRect(1, ((tft.height() / MAX_MENU_NUM) * i) + 2, tft.width() - 2, (tft.height() / MAX_MENU_NUM) - 3, menuColor);
    }

    tft.drawRect(0, ((tft.height() / MAX_MENU_NUM) * cursor) + 1, tft.width(), (tft.height() / MAX_MENU_NUM) - 1, MAROON);
    tft.drawRect(1, ((tft.height() / MAX_MENU_NUM) * cursor) + 2, tft.width() - 2, (tft.height() / MAX_MENU_NUM) - 3, RED);
}

#endif