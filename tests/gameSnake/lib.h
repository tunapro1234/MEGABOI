#include "MCUFRIEND_kbv.h"
// #include "printGameOver.h"
// #include "get_key.h"

/* 

***KAYRA KÖLESİNE YAPTIRILACAK İŞLER***
1) 2 TANE PİXEL ARRAY OLUŞTURULACAK (SNAKE VE EKRAN İÇİN)
1) Snake için LinkedList oluşturabiliriz (x, y, next) 

2) 3 PİXEL DURUMU OLUŞTURULACAK (EMPTY, SNAKE, FOOD)

3) SNAKE PİXEL ARRAYİNİN İÇİNDE YILANIN ŞU AN KAPSADIĞI TÜM PİXELLER VE KAFANIN VE KUYRUĞUN PİXEL DEĞERİ TUTULACAK

4) YILANLA KESİŞMEYEN BİR PİKSEL BULUNANA KADAR RANDOM FONKSİYONU İLE RASTGELE ELMA OLUŞTURCAZ

5) YILAN ELMAYI YEMEDİĞİNDE KUYRUK SİLİNECEK


*/

const int apple_id = 0;
const int snake_id = 1;
const int empty_id = 2;

#define wait_time_snake 200 // snake fps düzenlemesi için

#define SNAKEX_NUM 18 // yılan oyununda dikey çizgilerin sayısı -2 (dinamik)
#define SNAKEY_NUM 24 // yılan oyununda yatay çizgilerin sayısı -2 (dinamik)
#define SNAKESLIDEX 3 // Ekranın kenarlarındaki boşluk
#define DEFAULT_SNAKE_MENU_COLOR 0x0000

#define DARKCYAN 0x03EF
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define CYAN 0x07FF

// snake fonksiyonları
void openSnakeMenu(MCUFRIEND_kbv);
void printSnakeMenu(MCUFRIEND_kbv);
void printSnakePixel(int, int, String, MCUFRIEND_kbv);


// Pixel classı
class Pixel{
    public:
        int x;
        int y;
        int state;
    
    Pixel(int x, int y, int state){
        this->x = x;
        this->y = y;
        this->state = state;
    }  
};

enum Direction {
    STOP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    UP = 4
};


class Snake{
    public:
        // int max_snake = (SNAKEX_NUM-2)*(SNAKEY_NUM-2);
        int oldSnakeLength = 1;
        int snakeLength = 1;
        
        Pixel snakeParts [snakeLength];
        
        Direction next_dir = STOP;
        Direction cur_dir = STOP;


    Snake(Pixel startPixel, MCUFRIEND_kbv tft){
        this->headPixel = startPixel;
        this->tailPixel = startPixel;
        this->tft = tft;
    }
    
    void go(){}

    void update(){
        switch (next_dir){
        case RIGHT:
            if (this->headPixel.x <= (SNAKEX_NUM - 4)){ // sağa çarpıyor muyuz
                head->x++; // sadece kafanın değil listemizdeki tüm pixellerin değerlerinin artması gerrekiyor gelince yazcam
            } 
            else tft.fillScreen(WHITE);
            break;

        case DOWN:
            if (this->headPixel.y <= (SNAKEY_NUM - 4)){ // aşağı çarpıyor muyuz
                head->y++;
            }
            else tft.fillScreen(WHITE)
            break;

        case LEFT:
            if (this->headPixel.x != 0){ // sola çarpıyor muyuz
                head->x--;
            }
            else tft.fillScreen(WHITE)
            break;

        case UP:
            if (this->headPixel.y != 0){ // yukarı çarpıyor muyuz
                head->y--; 
            }
            else tft.fillScreen(WHITE)            
            break;
        }

        if (this->oldSnakeLength != this->snakeLength){         // Eğer uzunluk değişmişse
            Pixel new_array [this->snakeLength];                // Yeni uzunlukta array oluştur
            for (int i = 0; i < this->oldSnakeLength; i++){     // Eski elemanların her biri için
                new_array[i] = this->snakeParts[i];             // Eski elemanı yeni elemana ata
            }
            this->snakeParts = new_array;                       // Yeni arrayi classa yaz
            this->oldSnakeLength = this->snakeLength;           // Eski değeri yenile

            this->snakeParts[snakeLength] = ;//gelcem bekle
        }

        else{ // Uzunluk değişmemişse
            printSnakePixel(this->tailPixel.x, this->tailPixel.y, empty_id, tft);   // Eski pixeli sil

        }



        printSnakePixel(head->x, head->y, snake_id, tft); // yeni pixeli yaz
    }

};


// yılan şeylerini çizdirme
void printSnakeMenu(MCUFRIEND_kbv tft){ // ızgara çizdirme
    for (int i = 1; i <= (SNAKEY_NUM - 1); i++)
    {
            tft.drawLine(
            ((tft.width() / SNAKEX_NUM) + SNAKESLIDEX),
            ((tft.height() / SNAKEY_NUM) * i),
            (((tft.width() / SNAKEX_NUM) * (SNAKEX_NUM - 1)) + SNAKESLIDEX),
            ((tft.height() / SNAKEY_NUM) * i),
            DARKCYAN);
    }

    for (int i = 1; i <= (SNAKEX_NUM - 1); i++)
    {
        tft.drawLine(
            (((tft.width() / SNAKEX_NUM) * i) + SNAKESLIDEX),
            (tft.height() / SNAKEY_NUM),
            (((tft.width() / SNAKEX_NUM) * i) + SNAKESLIDEX),
            ((tft.height() / SNAKEY_NUM) * (SNAKEY_NUM - 1)),
            DARKCYAN);
    }
}

void openSnakeMenu(MCUFRIEND_kbv tft){
    tft.fillScreen(DEFAULT_SNAKE_MENU_COLOR);

    String r_key = ""; // bilmiyorum

    printSnakeMenu(tft); // mavi çizgiler
    printSnakePixel(head->x, head->y, snake_id, tft);
    
    Pixel startingPixel(5, 5, empty_id);
    Snake snake(startingPixel, tft);
    
    String key;

    while (true){
        // hatırlamıyorum ve karıştırma
        long start_key = millis(); // key alma
        while (true){
            key = key_get();
            if (key != "")
                r_key = key;
            long elapsed = millis() - start_key;

            if (elapsed >= wait_time_snake)
            {
                if (r_key != "")
                    key = r_key;
                break;
            }
        }
        ////////////////////////////////////////////////////
        snake.cur_dir = snake.next_dir;

        if (key.compareTo("right") == 0 && cur_dir != LEFT)
            snake.next_dir = RIGHT;
        else if (key.compareTo("down") == 0 && cur_dir != UP)
            snake.next_dir = DOWN;
        else if (key.compareTo("left") == 0 && cur_dir != RIGHT)
            snake.next_dir = LEFT;
        else if (key.compareTo("up") == 0 && cur_dir != DOWN)
            snake.next_dir = UP;
        else if (key.compareTo("next") == 0)
            snake.next_dir = STOP;

        if (key.compareTo("back") == 0)
            return;
    
        snake.update()

        // printSnakePixel(old_head->x, old_head->y, empty_id, tft); // eski pixeli sil
        // printSnakePixel(head->x, head->y, snake_id, tft); // yeni pixeli yaz
    }
}

void printSnakePixel(int x, int y, int status, MCUFRIEND_kbv tft){
    x++;
    y++;

    if (status == apple_id)
        status = YELLOW;
    else if (status == snake_id)
        status = CYAN;
    else if (status == empty_id)
        status = DEFAULT_SNAKE_MENU_COLOR;

    if (x > 0 && y > 0 && x < (SNAKEX_NUM - 1) && y < (SNAKEY_NUM - 1))
    {
        tft.fillRect(
            (((tft.width() / SNAKEX_NUM) * x) + SNAKESLIDEX) + 1,
            ((tft.height() / SNAKEY_NUM) * y) + 1,
            (tft.width() / SNAKEX_NUM) - 1,
            (tft.height() / SNAKEY_NUM) - 1,
            status);
    }
}


void printGameOver();