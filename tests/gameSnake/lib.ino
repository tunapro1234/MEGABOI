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

Tüm ekranı şey yapma olmuyor deliriyorum

sakat mali hg
boş bulduk kardeşim

Yukardaki todoyu boşver:
    1) Apple generator
    2) Durdurup ters yöne gidebiliyoruz

*/
const int apple_id = 0;
const int snake_id = 1;
const int empty_id = 2;

#define wait_time_snake 200 // snake fps düzenlemesi için

const int SNAKEX_NUM = 18; // yılan oyununda dikey çizgilerin sayısı -2 (dinamik)
const int SNAKEY_NUM = 24; // yılan oyununda yatay çizgilerin sayısı -2 (dinamik)
#define SNAKESLIDEX 3 // Ekranın kenarlarındaki boşluk
#define DEFAULT_SNAKE_MENU_COLOR 0x0000

#define DARKCYAN 0x03EF
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define CYAN 0x07FF
#define RED 0xF800

class Snake;
class Pixel;
class Apple;

// snake fonksiyonları
void openSnakeMenu(MCUFRIEND_kbv);
void printSnakeMenu(MCUFRIEND_kbv);
void printSnakePixel(int, int, String, MCUFRIEND_kbv);
void printGameOver(MCUFRIEND_kbv);
// Pixel generate_apple(Snake, MCUFRIEND_kbv);

// Pixel classı
class Pixel{
    public:
        int x;
        int y;
        int state;
        MCUFRIEND_kbv tft;

    Pixel(){}  
    Pixel(int x, int y, int state, MCUFRIEND_kbv tft){
        this->x = x;
        this->y = y;
        this->state = state;
        this->tft = tft;
    }  
    void update(int x, int y){
        this->x = x;
        this->y = y;
    } void draw(){
        printSnakePixel(this->x, this->y, this->state, tft);
    } void erase(){
        printSnakePixel(this->x, this->y, empty_id, tft);
    }
};

enum Direction {
    STOP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    UP = 4
};


class Apple{
    public:
        Pixel cur_apple;
        Pixel* snakeParts;
        int snakeLength;
        MCUFRIEND_kbv tft;

    Apple(){}
    Apple(Pixel* snakeParts, int snakeLength, MCUFRIEND_kbv tft){
        this->snakeLength = snakeLength;
        this->snakeParts = snakeParts;
        this->tft = tft;
    }
    void update(Pixel* snakeParts, int snakeLength){
        this->snakeLength = snakeLength;
        this->snakeParts = snakeParts;
    }
    void generate(){
        int rand_x;
        int rand_y;
        bool isSuitable;
        
        while(true){
            randomSeed(analogRead(A8));
            rand_x = (int)random(0, SNAKEX_NUM-2);
            rand_y = (int)random(0, SNAKEY_NUM-2);
            Serial.println("RANDOM: " + String(rand_x) + " " + String(rand_y));
            isSuitable = true;
            
            for(int i = 0; i < this->snakeLength; i++){
                if (rand_x == this->snakeParts[i].x && rand_x == this->snakeParts[i].x){
                    isSuitable = false;        
                }
            } if(isSuitable == true) break;
        }
        Pixel generated_apple = Pixel(rand_x, rand_y, apple_id, this->tft);
        this->cur_apple = generated_apple;
        this->cur_apple.draw();
    }
};


class Snake{
    public:
        int oldSnakeLength = 1;
        int snakeLength = 1;
        
        Pixel* snakeParts = new Pixel[snakeLength];
        
        Pixel headPixel;
        Pixel tailPixel;
        Pixel oldTailPixel;
        
        Direction next_dir = STOP;
        Direction cur_dir = STOP;

        MCUFRIEND_kbv tft;

    Snake(){} // boş iş
    Snake(Pixel startingSnakePixel, MCUFRIEND_kbv tft){
        this->headPixel = startingSnakePixel;
        this->tailPixel = startingSnakePixel;
        this->oldTailPixel = startingSnakePixel;
        
        this->snakeParts[0] = this->headPixel;
        this->tft = tft;
    }
    
    void extend(){
        this->snakeLength++;
        // this->oldSnakeLength = this->snakeLength;
        Pixel* new_array = new Pixel[snakeLength];          // Yeni uzunlukta yeni bir array oluştur
        
        for (int i = 0; i < this->oldSnakeLength; i++) {    // Eski arraydeki her eleman için
            new_array[i] = this->snakeParts[i];             // Elemanı yeni listeye ata
        }
        new_array[snakeLength-1] = this->oldTailPixel;  // Yeni arrayin sonuna kuyruğun sonunu ekle
        this->tailPixel = this->oldTailPixel;           // Eklenen eski kuyruk yeni kuyruk haline geldi
        delete [] this->snakeParts;                     // eski arrayi temizle
        this->snakeParts = new_array;                   // snakeParts uzatıldı
    }

    void go(int x_change, int y_change, Apple apple1){ 
        this->oldTailPixel = this->tailPixel;
        // sağa shift
        for (int i = snakeLength-1; 0 < i; i--){
            this->snakeParts[i] = this->snakeParts[i-1];
        }
        this->snakeParts[0].update(snakeParts[0].x + x_change, snakeParts[0].y + y_change);

        this->tailPixel = this->snakeParts[snakeLength-1];
        this->headPixel = this->snakeParts[0];


        for (int i = 1; i < snakeLength; i++){
            // Serial.print("(" + String(this->snakeParts[i].x) + ", " + String(this->snakeParts[i].y) + "), ");
            
            if (this->snakeParts[0].x == this->snakeParts[i].x && this->snakeParts[0].y == this->snakeParts[i].y){
                printGameOver(tft);
                return;
            }
        }
        // Serial.println("");
        
        Serial.println("APPLE: (" + String(apple1.cur_apple.x) + ", " + String(apple1.cur_apple.y) + ")");
        if(apple1.cur_apple.x == this->headPixel.x && apple1.cur_apple.y == this->headPixel.y){ // Eğer elma yersek uza
            // Serial.println("APPLE: (" + String(apple1.cur_apple.x) + ", " + String(apple1.cur_apple.y) + ")");
            this->extend();
            apple1.update(this->snakeParts, this->snakeLength);
            apple1.generate();
        }
        // for (int i = 0; i < SNAKEX_NUM-2; i++){ // snake pixeller temizleniyor 
        //     for (int j = 0; j < SNAKEX_NUM-2; j++){ // çok sıkıntı yarattı be
        //         if(allPixels[i][j] == snake_id){
        //             allPixels[i][j] = empty_id;
        //         }
        //     }
        // } for (int i = 0; i < snakeLength; i++){ // snake pixeller baştan çiziliyor
        //     allPixels[this->snakeParts[snakeLength].x][this->snakeParts[snakeLength].y] = snake_id;
        //     // Serial.println(String(allPixels[this->snakeParts[snakeLength].x][this->snakeParts[snakeLength].y]) + " " + this->snakeParts[snakeLength].x + " " + this->snakeParts[snakeLength].y);
        // } if (allPixels[this->headPixel.x][this->headPixel.y] == apple_id) this->snakeLength++;
        
        // else if (allPixels[this->headPixel.x][this->headPixel.y] == snake_id){
        //     Serial.println("SNAKE EATS HIS OWN TAIL..." + String(millis()));
        // }
        // if (this->headPixel.x == 2 && this->headPixel.y == 2) this->snakeLength++;
    }

    void update(Apple apple1){
        // Serial.println("HEAD: " + String(this->headPixel.x) + " " + String(this->headPixel.y));
        // Serial.println("TAIL: " + String(this->tailPixel.x) + " " + String(this->tailPixel.y));
        // Serial.println("OLDTAIL: " + String(this->oldTailPixel.x) + " " + String(this->oldTailPixel.y));
        this->oldSnakeLength = this->snakeLength;
        
        switch (next_dir){
        case RIGHT:
            if (this->headPixel.x <= (SNAKEX_NUM - 4)) this->go(1, 0, apple1); // sağa çarpmıyorsak yürü
            else {
                printGameOver(tft);
                return;
            } break;

        case DOWN:
            if (this->headPixel.y <= (SNAKEY_NUM - 4)) this->go(0, 1, apple1); // aşağı çarpmıyorsak yürü
            else {
                printGameOver(tft);
                return;
            } break;

        case LEFT:
            if (this->headPixel.x != 0) this->go(-1, 0, apple1); // sola çarpmıyorsak yürü
            else {
                printGameOver(tft);
                return;
            } break;

        case UP:
            if (this->headPixel.y != 0) this->go(0, -1, apple1); // yukarı çarpmıyorsak yürü
            else {
                printGameOver(tft);
                return;
            } break;
        } // yemek yiyip gelcem
        
        // if (this->oldSnakeLength != this->snakeLength){         // Eğer uzunluk değişmişse
            // this->oldSnakeLength = this->snakeLength;
            // Pixel* new_array = new Pixel[snakeLength];          // Yeni uzunlukta yeni bir array oluştur
            
            // for (int i = 0; i < this->oldSnakeLength; i++) {    // Eski arraydeki her eleman için
            //     new_array[i] = this->snakeParts[i];             // Elemanı yeni listeye ata
            // }
            // new_array[snakeLength-1] = this->oldTailPixel;  // Yeni arrayin sonuna kuyruğun sonunu ekle
            // this->tailPixel = this->oldTailPixel;           // Eklenen eski kuyruk yeni kuyruk haline geldi
            // delete [] this->snakeParts;                     // eski arrayi temizle
            // this->snakeParts = new_array;                   // snakeParts uzatıldı
        // } // gereksiz fazla karmaşıklaşıyor delircem
        // else if (this->next_dir != STOP){ // Uzunluk değişmemişse
        //     this->oldTailPixel.erase();
        // }

        if (this->oldSnakeLength == this->snakeLength && this->next_dir != STOP)         // Eğer uzunluk değişmişse
            this->oldTailPixel.erase();
        
        this->headPixel.draw();
    }
};


// Pixel generate_apple(Snake snake, MCUFRIEND_kbv tft){
//     int rand_x;
//     int rand_y;
//     bool isSuitable;
    
//     while(true){
//         rand_x = (int)random(0, SNAKEX_NUM-2);
//         rand_y = (int)random(0, SNAKEY_NUM-2);
//         isSuitable = true;
        
//         for(int i = 0; i < snake.snakeLength; i++){
//             if (rand_x == snake.snakeParts[i].x && rand_x == snake.snakeParts[i].x){
//                 isSuitable = false;        
//             }
//         } if(isSuitable == true) break;
//     }
//     Pixel generated_apple(rand_x, rand_y, apple_id, tft);
//     generated_apple.draw();
//     return generated_apple;
// }

void openSnakeMenu(MCUFRIEND_kbv tft){
    tft.fillScreen(DEFAULT_SNAKE_MENU_COLOR);

    String r_key = ""; // bilmiyorum
    
    // for (int i = 0; i < SNAKEX_NUM-2; i++){
    //     for (int j = 0; j < SNAKEX_NUM-2; j++){
    //         allPixels[i][j] = empty_id;
    //     }
    // }

    Pixel startingSnakePixel(5, 5, snake_id, tft);
    Snake snake(startingSnakePixel, tft);
    // current_apple = generate_apple(snake, tft);
    // Pixel current_apple = generate_apple(snake, tft);
    Apple apple1(snake.snakeParts, snake.snakeLength, tft);
    apple1.generate();
    Serial.println("APPLE: (" + String(apple1.cur_apple.x) + ", " + String(apple1.cur_apple.y) + ")");


    printSnakeMenu(tft); // mavi çizgiler
    printSnakePixel(snake.headPixel.x, snake.headPixel.x, snake_id, tft);
    
    String key;

    while (true){
        // hatırlamıyorum ve karıştırma
        long start_key = millis();
        while (true){
            key = key_get();
            if (key != "")
                r_key = key;
            long elapsed = millis() - start_key;

            if (elapsed >= wait_time_snake){
                if (r_key != "")
                    key = r_key;
                break;
            }
        }
        ////////////////////////////////////////////////////
        snake.cur_dir = snake.next_dir;

        if (key.compareTo("right") == 0 && snake.cur_dir != LEFT)
            snake.next_dir = RIGHT;
        else if (key.compareTo("down") == 0 && snake.cur_dir != UP)
            snake.next_dir = DOWN;
        else if (key.compareTo("left") == 0 && snake.cur_dir != RIGHT)
            snake.next_dir = LEFT;
        else if (key.compareTo("up") == 0 && snake.cur_dir != DOWN)
            snake.next_dir = UP;
        else if (key.compareTo("next") == 0)
            snake.next_dir = STOP;

        if (key.compareTo("back") == 0)
            return;

        snake.update(apple1);
    }
}


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

void printGameOver(MCUFRIEND_kbv tft){
    tft.fillScreen(RED);
    while(1){}
}
