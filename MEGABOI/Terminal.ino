#include "MCUFRIEND_kbv.h"

#define GREEN 0x07E0
#define BLACK 0x0000 

class Term{
    public:
        int font_size;
        int line_counter = 0;
        String lines [64];
        int w_menu = 0;
        MCUFRIEND_kbv tft;
        
        Term(int font_size, MCUFRIEND_kbv tft){
            this->font_size = font_size;
            this->tft = tft;
        }
    
    // Acilen pythona dönmem gerekiyor
    void init(){
        this->tft.fillScreen(BLACK);
        this->tft.setTextColor(GREEN);
        this->tft.setTextSize(this->font_size);
        
        this->tft.setCursor(0, this->w_menu * 10);
    }

    void print(String msg){
        this->tft.setCursor(0, this->w_menu++ * 10);
        
        // Kaydedilen çok fazla yazı varsa baştan başlayarak sil 
        if (this->line_counter >= 64){
            // String temp = this->lines[0];
            for (int i = 0; i < 64; i++){ // Bütün yazıların kaydedildiği arraydeki elemanları sola kaydır
                this->lines[i] = this->lines[i+1]; // Sola kaydırma işte
            }
            this->line_counter = 63; // Yeni elemanın sona geleceğini söylemek için
            this->lines[63] = ""; // Yazıların kaydedildiği arrayde kaydırdıktan sonra son elemanı sil
        }
        
        // Ekranda çok fazla yazı varsa son 16 satırı yazdır
        if (this->w_menu > 32){
            this->tft.fillScreen(BLACK); // Ekranı temizle
            this->w_menu = 0; // ekrandaki imleci sıfırla
            for(int i = 0; i <= 16; i++){ // 16 kere dön
                this->tft.setCursor(0, this->w_menu++ * 10); // Ekrandaki imleci ayarla
                this->tft.print(this->lines[(this->line_counter-16) + i]); // son 16 satır yazdır
            }
        }

        this->lines[this->line_counter++] = msg; // Yazıyı yazdır daha sonra yazıların kaydedildiği arrayin imlecini 1 arttır
        this->tft.print(msg); // Yazdır
    }
};
