#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"

MCUFRIEND_kbv tft(A3, A2, A1, A0, A4); // Ekran tanıtımı
#define BUTTON_TOLERANCE 80 // Butonların töleransı
#define BUTTON_NEXT A9      // Butonların bağlı olduğu pinler
#define BUTTON_UP A10
#define BUTTON_DOWN A11
#define BUTTON_LEFT A12
#define BUTTON_BACK A13
#define BUTTON_RIGHT A14

#define WHITE 0xFFFF
#define RED 0xF800

void setup(){
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_NEXT, INPUT_PULLUP);
    pinMode(BUTTON_BACK, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_UP, INPUT_PULLUP);

    Serial.begin(9600);
    uint32_t when = millis();
    uint16_t ID = tft.readID(); 
    
    if (ID == 0xD3D3)
        ID = 0x9481; 
    
    tft.begin(ID);
    
    openSnakeMenu(tft);
}

void loop(){
    tft.fillScreen(RED);
}