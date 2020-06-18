#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "Terminal.h"

MCUFRIEND_kbv tft(A3, A2, A1, A0, A4); // Ekran tanıtımı

#define BLACK 0x0000 // renkler
#define GREEN 0x07E0

void setup() {
    uint32_t when = millis();

    uint16_t ID = tft.readID(); 
    // Serial.print("ID = 0x");
    // Serial.println(ID, HEX);
    if (ID == 0xD3D3)
        ID = 0x9481; 
    //    ID = 0x9329;
    tft.begin(ID);
}


void loop() {
    Term terminal(1, tft);
    terminal.init();
    
    for (int i = 0; i < 1000; i++){
        terminal.print(String(i));
        delay(50);
    }
    tft.fillScreen(GREEN);
    tft.fillScreen(BLACK);
    delay(2000);
}
