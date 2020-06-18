#include "MCUFRIEND_kbv.h"
#define MAROON 0x7800
#define RED 0xF800

void printCursor(int, int, int, MCUFRIEND_kbv);

void printCursor(int cursor, int menu_color, int menu_num, MCUFRIEND_kbv tft){
    for (int i = 0; i <= menu_num; i++){
        tft.drawRect(0, ((tft.height() / menu_num) * i) + 1, tft.width(), (tft.height() / menu_num) - 1, menu_color);
        tft.drawRect(1, ((tft.height() / menu_num) * i) + 2, tft.width() - 2, (tft.height() / menu_num) - 3, menu_color);
    }

    tft.drawRect(0, ((tft.height() / menu_num) * cursor) + 1, tft.width(), (tft.height() / menu_num) - 1, MAROON);
    tft.drawRect(1, ((tft.height() / menu_num) * cursor) + 2, tft.width() - 2, (tft.height() / menu_num) - 3, RED);
}
