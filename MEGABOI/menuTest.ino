#include "MCUFRIEND_kbv.h"
// #include "print_cursor.h"
// #include "get_key.h"
// #include "testESP.h"
// #include "testSD.h"

// Test menüsü fonksiyonları

#define MAX_MENU_NUM 8 // Menüde kaç bölüm açılacağı (dinamik)
#define wait_time 160       // Tuş hassasiyeti için bekleme süresi

#define LIGHTGREY 0xC618
#define BLACK 0x0000 // renkler

void openTestMenu(MCUFRIEND_kbv);
void printTestMenu(MCUFRIEND_kbv);

// int cursor = 0;
// int menu_color = LIGHTGREY;

void openTestMenu(MCUFRIEND_kbv tft){
    int cursor = 0; 
    int menu_color = LIGHTGREY;
    String key;

    tft.fillScreen(LIGHTGREY);

    printTestMenu(tft);
    printCursor(cursor, menu_color, MAX_MENU_NUM, tft);

    while (true){
        key = key_get();

        if (key.compareTo("back") == 0)
            return;
        
        else if (key.compareTo("down") == 0 && cursor >= 0){
            if (cursor == (MAX_MENU_NUM - 1)){
                cursor = 0;
                printCursor(cursor, menu_color, MAX_MENU_NUM, tft);
            }

            else if (cursor < MAX_MENU_NUM)
                printCursor(++cursor, menu_color, MAX_MENU_NUM, tft);
        }

        else if (key.compareTo("up") == 0 && cursor >= 0){
            if (cursor == 0){
                cursor = MAX_MENU_NUM - 1;
                printCursor(cursor, menu_color, MAX_MENU_NUM, tft);
            }

            else if (cursor < MAX_MENU_NUM)
                printCursor(--cursor, menu_color, MAX_MENU_NUM, tft);
        }
    
        else if (key.compareTo("next") == 0){
            switch (cursor){
                case 0:
                    printGameOver(tft);
                    cursor = 0;
                    break;
                
                case 1:
                    openESPTestMenu(tft);
                    cursor = 1;
                    break;

                case 2:
                    openSDTestMenu(tft);
                    cursor = 2;
                    break;
                
                case 3:
                    openSnakeLMenu(tft);
                    cursor = 3;
                    break;

                case MAX_MENU_NUM - 1:
                    return;
            }
            tft.fillScreen(LIGHTGREY);
            printTestMenu(tft);
            printCursor(cursor, LIGHTGREY, MAX_MENU_NUM, tft);
        }   
    delay(wait_time);
    }
}

void printTestMenu(MCUFRIEND_kbv tft){
    // tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);
    int w_menu;
    tft.setTextColor(BLACK);
    tft.setTextSize(2);

    w_menu = 0;
    tft.setCursor((tft.width() / 2) - 42, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("GAME OVER");
    
    w_menu = 1;
    tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("ESP8266");

    w_menu = 2;
    tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("SD TEST");    

    w_menu = 3;
    tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("SNAKE-L");
    
    w_menu = MAX_MENU_NUM - 1;
    tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("EXIT");

    for (int i = 0; i <= MAX_MENU_NUM; i++){
        tft.drawFastHLine(0, (tft.height() / MAX_MENU_NUM) * i, tft.width(), BLACK); // Bölümler arasındaki çizgiler
    }
}
