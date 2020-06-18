#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"

MCUFRIEND_kbv tft(A3, A2, A1, A0, A4); // Ekran tanıtımı

#define BLACK 0x0000 // renkler
#define GREEN 0x07E0


class Term{
    public:
    int font_size;
    int line_counter = 0;
    String lines [64];
    int w_menu = 0;

    Term(int font_size){
        this->font_size = font_size;
    }
    
    // Acilen pythona dönmem gerekiyor
    void init(){
        tft.fillScreen(BLACK);
        tft.setTextColor(GREEN);
        tft.setTextSize(this->font_size);
        
        tft.setCursor(0, this->w_menu * 10);
    }

    void print(String msg){
        tft.setCursor(0, this->w_menu++ * 10);
        
        // Kaydedilen çok fazla yazı varsa baştan başlayarak sil 
        if (this->line_counter >= 64){
            // String temp = this->lines[0];
            for (int i = 0; i < 64; i++){
                this->lines[i] = this->lines[i+1];
            }
            this->line_counter = 63;
            this->lines[63] = "";
        }
        
        // Ekranda çok fazla yazı varsa son 16 satırı yazdır
        if (this->w_menu >= 32){
            tft.fillScreen(BLACK);
            this->w_menu = 0;
            for(int i = 0; i <= 16; i++){
                tft.setCursor(0, this->w_menu++ * 10);
                tft.print(this->lines[(this->line_counter-16) + i]);
            }
        }

        this->lines[this->line_counter++] = msg;
        tft.print(msg);
    }
};

Term terminal(1);

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
    terminal.init();
    
    for (int i = 0; i < 1000; i++){
        terminal.print(String(i));
        delay(50);
    }
    tft.fillScreen(GREEN);
    tft.fillScreen(BLACK);
    delay(2000);
}
