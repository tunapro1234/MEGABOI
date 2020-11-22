#include "Menus/MainMenu.hpp"
// çoğu şeyi enum yapmak isterdim ama PROGMEM olmuyor

// fonksiyon dışında olması ne kadar iyi bilmiyorum
MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);  // Ekran tanıtımı

// CURSORI GLOBAL YAPMIŞIM olamaz

// menü fonksiyonları

void setup() {
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

void loop() {
    MainMenu::open(tft);
}
