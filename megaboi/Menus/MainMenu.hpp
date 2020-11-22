#ifndef __MAINMENU_H
#define __MAINMENU_H

#include "../header.hpp"
#include "TestMenu.hpp"

class MainMenu {
   public:
    inline static void print(MCUFRIEND_kbv& tft) {
        // bunu da ayrı güzel bir fonksiyona çıkarmak lazım da üşendim

        // tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);
        tft.setTextColor(BLACK);
        tft.setTextSize(2);

        // tft.setCursor((tft.width() / 2) - 40, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);

        // GAMES -> len(5), location -> 0
        tft.setCursor((tft.width() / 2) - 20, (tft.height() / (MAX_MENU_NUM * 2)) - 5);
        tft.print(F("GAMES"));

        // TESTS -> len(5) * 4, location -> 1
        tft.setCursor((tft.width() / 2) - 20, ((tft.height()) / (MAX_MENU_NUM * 2)) * 3 - 5);
        tft.print(F("TESTS"));

        // SETTINGS -> len(8) * 4, location -> 2
        tft.setCursor((tft.width() / 2) - 40, (((tft.height()) / (MAX_MENU_NUM * 2)) * (((MAX_MENU_NUM - 1) * 2) + 1)) - 5);
        // tft.setCursor((tft.width() / 2) - 32, (((tft.height()) / (MAX_MENU_NUM * 2)) * 5 - 5));
        tft.print(F("SETTINGS"));

        for (int i = 0; i <= MAX_MENU_NUM; i++) {
            tft.drawFastHLine(0, (tft.height() / MAX_MENU_NUM) * i, tft.width(), BLACK);
        }
    }

    inline static void open(MCUFRIEND_kbv& tft) {
        byte cursor = 0;
        tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);

        MainMenu::print(tft);
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
                switch (cursor) {
                    case 0:
                        // tamamen test için
                        printCursor(tft, cursor = (MAX_MENU_NUM - 1), DEFAULT_MAIN_MENU_COLOR);

                        // GamesMenu::open(tft);
                        break;

                    case 1:
                        // şimdi cursorı referans olarak yollabilirim, normal verebilirim, ya da hiç vermem
                        // normal vermenin hiç vermemeden farkı yok.

                        //  cursor 1 byte yer kaplıyor, pointerlar 2. Sanırım referans olarak verdikten sonra
                        // verilen pointer yok ediliyor umarım öyledir.

                        // ama ben yine de yeni bir cursor oluşturacağım
                        TestMenu::open(tft);
                        break;

                        // case MAX_MENU_NUM-1:
                        //     openSettingsMenu();
                        //     cursor = MAX_MENU_NUM-1;
                        //     break;
                }

                tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);
                MainMenu::print(tft);
                printCursor(tft, cursor, DEFAULT_MAIN_MENU_COLOR);
            }

            delay(wait_time);
        }
    }

   private:
    // obje yok
    inline MainMenu() {}
};

#endif