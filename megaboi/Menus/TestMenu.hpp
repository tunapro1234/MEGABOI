#ifndef __MENU_H
#define __MENU_H

#include "../header.hpp"

class TestMenu {
   public:
    inline static void print(MCUFRIEND_kbv& tft) {
        // bunu da ayrı güzel bir fonksiyona çıkarmak lazım da üşendim

        // tft.setCursor((tft.width() / 2) - 42, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
        // tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);
        tft.setTextColor(BLACK);
        tft.setTextSize(2);

        tft.setCursor((tft.width() / 2) - 42, (((tft.height()) / (MAX_MENU_NUM * 2))) - 5);
        tft.print(F("GAME OVER"));

        tft.setCursor((tft.width() / 2) - 42, (((tft.height()) / (MAX_MENU_NUM * 2)) * 3) - 5);
        tft.print(F("ESP8266"));

        tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * 5) - 5);
        tft.print(F("SD TEST"));

        tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * 7) - 5);
        tft.print(F("SNAKE-L"));

        tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * (((MAX_MENU_NUM - 1) * 2) + 1)) - 5);
        tft.print(F("EXIT"));

        for (int i = 0; i <= MAX_MENU_NUM; i++) {
            tft.drawFastHLine(0, (tft.height() / MAX_MENU_NUM) * i, tft.width(), BLACK);
        }
    }

    inline static void open(MCUFRIEND_kbv& tft) {
        tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);

        byte cursor = 0;
        TestMenu::print(tft);
        printCursor(tft, cursor, DEFAULT_MAIN_MENU_COLOR);

        while (true) {
            byte key = getKey();

            // Aşağı tuşuna basıldıysa
            if (key == KEY_DOWN) {
                // En alta geldiysek geri yukarı attır
                if (cursor == (MAX_MENU_NUM - 1))
                    printCursor(tft, cursor = 0, DEFAULT_MAIN_MENU_COLOR);

                // değilse imleci arttır
                else
                    printCursor(tft, ++cursor, DEFAULT_MAIN_MENU_COLOR);
            }

            // yukarı tuşuna basıldıysa
            else if (key == KEY_UP) {
                // en üste geldiysek en alta at
                if (cursor == 0)
                    printCursor(tft, cursor = (MAX_MENU_NUM - 1), DEFAULT_MAIN_MENU_COLOR);

                // değilse imleci düşür
                else
                    printCursor(tft, --cursor, DEFAULT_MAIN_MENU_COLOR);
            }

            else if (key == KEY_NEXT) {
                // tft.print(F("GAME OVER"));
                // tft.print(F("ESP8266"));
                // tft.print(F("SD TEST"));
                // tft.print(F("SNAKE-L"));
                // tft.print(F("EXIT"));

                switch (cursor) {
                    case 0:
                        // tamamen test için
                        printCursor(tft, cursor = (MAX_MENU_NUM - 1), DEFAULT_MAIN_MENU_COLOR);

                        // GamesMenu::open(tft);
                        break;

                    case 1:
                        // EspMenu::open(tft);
                        break;

                    case 2:
                        // SdMenu::open(tft);
                        break;

                    case 3:
                        // SnakeGame::open(tft);
                        break;

                    case MAX_MENU_NUM - 1:
                        return;
                }

                tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);
                TestMenu::print(tft);
                printCursor(tft, cursor, DEFAULT_MAIN_MENU_COLOR);
            }

            delay(wait_time);
        }
    }

   private:
    // obje yok
    inline TestMenu() {}
};

#endif