#ifndef __MHEADER_H
#define __MHEADER_H

#include "Arduino.h"
#include "MCUFRIEND_kbv.h"

#define GREENYELLOW 0xAFE5
#define DARKGREEN 0x03E0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define DARKCYAN 0x03EF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define MAROON 0x7800
#define PURPLE 0x780F
#define ORANGE 0xFD20
#define WHITE 0xFFFF
#define OLIVE 0x7BE0
#define BLACK 0x0000
#define GREEN 0x07E0
#define NAVY 0x000F
#define BLUE 0x001F
#define CYAN 0x07FF
// #define PINK 0xF81F
#define RED 0xF800

#define BUTTON_TOLERANCE 80  // Butonların töleransı
#define BUTTON_NEXT A9       // Butonların bağlı olduğu pinler
#define BUTTON_UP A10
#define BUTTON_DOWN A11
#define BUTTON_LEFT A12
#define BUTTON_BACK A13
#define BUTTON_RIGHT A14

// enum olmadı
#define KEY_NONE 0
#define KEY_DOWN 1
#define KEY_UP 2
#define KEY_RIGHT 3
#define KEY_LEFT 4
#define KEY_NEXT 5
#define KEY_BACK 6

#define DEFAULT_MAIN_MENU_COLOR 0x7BEF

#define MAX_MENU_NUM 8  // Ana menüde kaç bölüm açılacağı (dinamik)

#define gamesMenuValue 0  // Menülerin ana menüde kaçıncı sırada oldukları
#define testMenuValue 1
#define settingsMenuValue MAX_MENU_NUM - 1

#define wait_time 160  // Tuş hassasiyeti için bekleme süresi

inline byte getKey() {
    if (analogRead(BUTTON_DOWN) < BUTTON_TOLERANCE)
        return KEY_DOWN;

    else if (analogRead(BUTTON_UP) < BUTTON_TOLERANCE)
        return KEY_UP;

    else if (analogRead(BUTTON_RIGHT) < BUTTON_TOLERANCE)
        return KEY_RIGHT;

    else if (analogRead(BUTTON_LEFT) < BUTTON_TOLERANCE)
        return KEY_LEFT;

    else if (analogRead(BUTTON_NEXT) < BUTTON_TOLERANCE)
        return KEY_NEXT;

    else if (analogRead(BUTTON_BACK) < BUTTON_TOLERANCE)
        return KEY_BACK;

    return KEY_NONE;
}

inline void printCursor(MCUFRIEND_kbv& tft, const byte cursor, const int menuColor) {
    for (int i = 0; i <= MAX_MENU_NUM; i++) {
        tft.drawRect(0, ((tft.height() / MAX_MENU_NUM) * i) + 1, tft.width(), (tft.height() / MAX_MENU_NUM) - 1, menuColor);
        tft.drawRect(1, ((tft.height() / MAX_MENU_NUM) * i) + 2, tft.width() - 2, (tft.height() / MAX_MENU_NUM) - 3, menuColor);
    }

    tft.drawRect(0, ((tft.height() / MAX_MENU_NUM) * cursor) + 1, tft.width(), (tft.height() / MAX_MENU_NUM) - 1, MAROON);
    tft.drawRect(1, ((tft.height() / MAX_MENU_NUM) * cursor) + 2, tft.width() - 2, (tft.height() / MAX_MENU_NUM) - 3, RED);
}

inline void gameOver(MCUFRIEND_kbv& tft, unsigned int score) {
    tft.fillScreen(RED);
    tft.print(score);
}

#endif