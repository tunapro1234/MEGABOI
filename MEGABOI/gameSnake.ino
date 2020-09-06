#include "MCUFRIEND_kbv.h"

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

#ifdef __arm__ // memory ölçme
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

class Snake;
class Pixel;
class Apple;

// snake fonksiyonları
void openSnakeMenu(MCUFRIEND_kbv);
void printSnakeMenu(MCUFRIEND_kbv);
void printSnakePixel(int, int, String, MCUFRIEND_kbv);

int freeMemory() {
    char top;
    #ifdef __arm__
    return &top - reinterpret_cast<char*>(sbrk(0));
    #elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
    return &top - __brkval;
    #else  // __arm__
    return __brkval ? &top - __brkval : &top - __malloc_heap_start;
    #endif  // __arm__
}

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
    } void update(int x, int y){
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

Pixel curr_apple(0, 0, apple_id, tft);

class Apple{
    public:
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
    void print(){
        Serial.println("APPLE VALUES: " + String(curr_apple.x) + ", " + String(curr_apple.y));
    }
    Pixel generate(){
        Serial.println("GENERATE");
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
        Pixel generated_apple = Pixel(rand_x, rand_y, apple_id, tft);
        return generated_apple;
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
            if (this->snakeParts[0].x == this->snakeParts[i].x && this->snakeParts[0].y == this->snakeParts[i].y){
                printGameOver(tft);
                return;
            }
        }
        
        // Serial.println("CURRENT APPLE: (" + String(curr_apple.x) + ", " + String(curr_apple.y) + ") ");

        if(curr_apple.x == this->headPixel.x && curr_apple.y == this->headPixel.y){ // Eğer elma yersek uza
            this->extend();
            apple1.update(this->snakeParts, this->snakeLength);
            /////////////////////////////////////
            curr_apple = apple1.generate();
            curr_apple.draw();
        }
    }

    int update(Apple apple1){
        this->oldSnakeLength = this->snakeLength;
        
        switch (next_dir){
        case RIGHT:
            if (this->headPixel.x <= (SNAKEX_NUM - 4)) this->go(1, 0, apple1); // sağa çarpmıyorsak yürü
            else return 1;
            break;

        case DOWN:
            if (this->headPixel.y <= (SNAKEY_NUM - 4)) this->go(0, 1, apple1); // aşağı çarpmıyorsak yürü
            else return 1;
            break;

        case LEFT:
            if (this->headPixel.x != 0) this->go(-1, 0, apple1); // sola çarpmıyorsak yürü
            else return 1;
            break;

        case UP:
            if (this->headPixel.y != 0) this->go(0, -1, apple1); // yukarı çarpmıyorsak yürü
            else return 1;
            break;
        } // yemek yiyip gelcem

        if (this->oldSnakeLength == this->snakeLength && this->next_dir != STOP)         // Eğer uzunluk değişmişse
            this->oldTailPixel.erase();
        
        this->headPixel.draw();
        return 0;
    }
};

void openSnakeMenu(MCUFRIEND_kbv tft){
    tft.fillScreen(DEFAULT_SNAKE_MENU_COLOR);

    String r_key = ""; // bilmiyorum
    Pixel startingSnakePixel(5, 5, snake_id, tft);
    Snake snake(startingSnakePixel, tft);
    Apple apple1(snake.snakeParts, snake.snakeLength, tft);
    curr_apple = apple1.generate();
    curr_apple.draw();

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
        if (snake.next_dir != STOP)
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

        Serial.println("FREE MEMORY: " + String(freeMemory()));

        apple1.print();
        if (snake.update(apple1) == 1){
            printGameOver(tft);
            return;
        }
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
