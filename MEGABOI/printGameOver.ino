#include "MCUFRIEND_kbv.h"
void printGameOver(MCUFRIEND_kbv tft){
    tft.fillScreen(MAROON);
    while (true)
    {
        key = key_get();

        tft.setTextColor(BLACK);
        tft.setTextSize(3);

        tft.setCursor((tft.width() / 4) - 15, (tft.height() / 2) - 15);
        tft.print("GAME OVER");

        if (key.compareTo("back") == 0)
            return;
    }
}
