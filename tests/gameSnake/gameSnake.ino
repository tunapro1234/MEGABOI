#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "lib.h"

MCUFRIEND_kbv tft(A3, A2, A1, A0, A4); // Ekran tanıtımı

void setup(){
    uint32_t when = millis();
    uint16_t ID = tft.readID(); 
    
    if (ID == 0xD3D3)
        ID = 0x9481; 
    
    tft.begin(ID);
}

void loop(){
    openSnakeMenu(tft);
}