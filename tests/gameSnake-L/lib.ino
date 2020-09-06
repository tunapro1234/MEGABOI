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
 

class snakePart;
class Snake;
class Pixel;

void openSnakeMenu(MCUFRIEND_kbv);
void printSnakeMenu(MCUFRIEND_kbv);
void printSnakePixel(int, int, String, MCUFRIEND_kbv);


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

class snakePart{
    public:
        Pixel pixel;
        snakePart* next;
        snakePart* prev;
    
    snakePart(){}
    snakePart(int x, int y, snakePart* prev, snakePart* next, MCUFRIEND_kbv tft){
        pixel = Pixel(x, y, snake_id, tft);
        this->next = next;
        this->prev = prev;
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
        snakePart head;
        snakePart* tail = new snakePart();
        snakePart* counter = new snakePart();
        
        Direction next_dir = STOP;
        Direction cur_dir = STOP;
        
        Pixel deletingPixel;
        Pixel apple;

        int oldSnakeLength = 1;
        int snakeLength = 1;   
        bool doesLenChanged = 0;

        MCUFRIEND_kbv tft;

        Snake(){}
        Snake(int x, int y, MCUFRIEND_kbv tft){
            head = snakePart(x, y, NULL, NULL, tft);
            counter = &head; while(counter->next != NULL) counter = counter->next; tail = counter; // tail elemanı hesaplanıyor 
            generateApple();
        }

        void generateApple(){
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
                
                counter = &head;
                while(counter = NULL){
                    if (rand_x == this->counter->pixel.x && rand_x == this->counter->pixel.x){
                        isSuitable = false;
                    }
                    counter = counter->next;
                } if(isSuitable == true) break;
            }
            // return Pixel(rand_x, rand_y, apple_id, tft);
            this->apple = Pixel(2, 2, apple_id, tft);
            // apple.draw();
        }

        void extend(){
            // counter = &head; while(counter->next != NULL) counter = counter->next; tail = counter; // tail elemanı hesaplanıyor 

            // this->printSnake();
            snakePart* new_part = new snakePart(); // Yeni bir parça oluşturuldu
            new_part->pixel.x = deletingPixel.x;
            new_part->pixel.y = deletingPixel.y;
            new_part->next = NULL;
            new_part->prev = tail;
            
            this->tail->next = new_part; // eski kuyruğun next elemanı yeni parçanın adresine ayarlandı
            this->tail = new_part;
            // counter = &head; while(counter->next != NULL) counter = counter->next; tail = counter; // tail elemanı hesaplanıyor 
            
            this->snakeLength++;    
            // this->printSnake();
        }
        
        int go(int x_change, int y_change){
            // counter = &head; while(counter->next != NULL) counter = counter->next; tail = counter; // tail elemanı hesaplanıyor 
            deletingPixel = tail->pixel;
            
            // Sağa shift
            counter = tail;
            while(counter->prev != NULL){
                counter->pixel = counter->prev->pixel;
                counter = counter->prev;
            }
            head.pixel.update(head.pixel.x + x_change, head.pixel.y + y_change);            
            
            counter = &head;
            while (counter = NULL){
                if (head.pixel.x == counter->pixel.x && head.pixel.y == counter->pixel.y) return 1;
                counter = counter->next;
            }
        
            this->printSnake();
            // Serial.println("CURRENT APPLE: (" + String(apple.x) + ", " + String(apple.y) + ") ");
            
            if (head.pixel.x == apple.x && head.pixel.y == apple.y){ 
                extend();
                this->doesLenChanged = true;
                generateApple();
            } // elma yersek uzat

            // Serial.println(String(oldSnakeLength) + " " + String(snakeLength));
            if (doesLenChanged == 0) // Eğer uzunluk değişmemişse
                deletingPixel.erase(); // son pixelin eski halini sil
            
            head.pixel.draw();
            return 0;
        }

        int update(){
            counter = &head; while(counter->next != NULL) counter = counter->next; tail = counter; // tail elemanı hesaplanıyor 
            doesLenChanged = 0;

            int rv = 0;
            switch (next_dir){
                case RIGHT:
                    if (head.pixel.x <= (SNAKEX_NUM - 4)) rv = this->go(1, 0); // sağa çarpmıyorsak yürü
                    else return 1;
                    break;

                case DOWN:
                    if (head.pixel.y <= (SNAKEY_NUM - 4)) rv = this->go(0, 1); // aşağı çarpmıyorsak yürü
                    else return 1;
                    break;

                case LEFT:
                    if (head.pixel.x != 0) rv = this->go(-1, 0); // sola çarpmıyorsak yürü
                    else return 1;
                    break;

                case UP:
                    if (head.pixel.y != 0) rv = this->go(0, -1); // yukarı çarpmıyorsak yürü
                    else return 1;
                    break;
            }
            // this->printSnake();            
            if(rv == 1) return 1; // go fonksiyonu hata verdiyse biz de verelim
            return 0;
        }
        
        void printSnake(){
            Serial.print("tail: (" + String(tail->pixel.x) + " " + String(tail->pixel.y) + ") \ndeletingPixel: (" + String(deletingPixel.x) + " " + String(deletingPixel.y) + ") \n[");
            counter = &head;
            while(counter != NULL){
                Serial.print("(" + String(counter->pixel.x) + ", " + String(counter->pixel.y) + "), ");
                counter = counter->next;
            }
            Serial.println("]\n " + String(freeMemory()) +  " BYTE FREE MEMORY LEF\n" + String(doesLenChanged));

        }
};

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

void openSnakeMenu(MCUFRIEND_kbv tft){
    tft.fillScreen(DEFAULT_SNAKE_MENU_COLOR);

    String r_key = ""; // bilmiyorum

    Snake snake(5, 5, tft);

    printSnakeMenu(tft); // mavi çizgiler
    printSnakePixel(snake.head.pixel.x, snake.head.pixel.x, snake_id, tft);
    
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
        
        if(snake.update() == 1) return;
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
