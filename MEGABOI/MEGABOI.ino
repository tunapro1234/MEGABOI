#include "MCUFRIEND_kbv.h"
#include "Adafruit_GFX.h"

// #include "print_cursor.h"
// #include "get_key.h"

// #include "menuSettings.h"
// #include "menuGames.h"
// #include "menuTest.h"



MCUFRIEND_kbv tft(A3, A2, A1, A0, A4); // Ekran tanıtımı

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
#define RED 0xF800
//#define PINK 0xF81F

#define BUTTON_TOLERANCE 80 // Butonların töleransı
#define BUTTON_NEXT A9      // Butonların bağlı olduğu pinler
#define BUTTON_UP A10
#define BUTTON_DOWN A11
#define BUTTON_LEFT A12
#define BUTTON_BACK A13
#define BUTTON_RIGHT A14


#define DEFAULT_MAIN_MENU_COLOR 0x7BEF

#define MAX_MENU_NUM 8 // Ana menüde kaç bölüm açılacağı (dinamik)

#define gamesMenuValue 0 // Menülerin ana menüde kaçıncı sırada oldukları
#define testMenuValue 1
#define settingsMenuValue MAX_MENU_NUM-1

#define wait_time 160       // Tuş hassasiyeti için bekleme süresi

// const int lenCurrentMenu = 2; ne olduğunu bilmiyorum

// int currentMenu = mainMenuValue;
int cursor;
int menu_color;
// String key_get();
String key;

// menü fonksiyonları
void openMainMenu();
void printMainMenu();


void setup(){
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_NEXT, INPUT_PULLUP);
    pinMode(BUTTON_BACK, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(SS, OUTPUT);

    uint16_t ID = tft.readID(); 

    if (ID == 0xD3D3)
        ID = 0x9481; 

    tft.begin(ID);
}

void loop(){
    openMainMenu();
}

void openMainMenu(){
    cursor = 0;
    menu_color = DEFAULT_MAIN_MENU_COLOR;
    tft.fillScreen(menu_color);

    printMainMenu();
    printCursor(cursor, menu_color, MAX_MENU_NUM, tft);

    while (true){
        key = key_get();

        if (key.compareTo("down") == 0 && cursor >= 0){
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
                    openGamesMenu(tft);
                    cursor = 0;
                    break;
                
                case 1:
                    openTestMenu(tft);
                    cursor = 1;
                    break;
                
                // case MAX_MENU_NUM-1:
                //     openSettingsMenu();
                //     cursor = MAX_MENU_NUM-1;
                //     break;
            }
            tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);
            printMainMenu();
            printCursor(cursor, DEFAULT_MAIN_MENU_COLOR, MAX_MENU_NUM, tft);
        }

        delay(wait_time);
    }
}

void printMainMenu()
{
    // tft.fillScreen(DEFAULT_MAIN_MENU_COLOR);
    int w_menu;
    tft.setTextColor(BLACK);
    tft.setTextSize(2);

    w_menu = 0;
    tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("GAMES");

    w_menu = 1;
    tft.setCursor((tft.width() / 2) - 20, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("TESTS");
    
    w_menu = MAX_MENU_NUM - 1;
    tft.setCursor((tft.width() / 2) - 40, (((tft.height()) / (MAX_MENU_NUM * 2)) * ((w_menu * 2) + 1)) - 5);
    tft.print("SETTINGS");

    for (int i = 0; i <= MAX_MENU_NUM; i++){
        tft.drawFastHLine(0, (tft.height() / MAX_MENU_NUM) * i, tft.width(), BLACK);
    }
}
