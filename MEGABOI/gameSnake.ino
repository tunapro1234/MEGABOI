#define wait_time_snake 200 // snake fps düzenlemesi için
#include "MCUFRIEND_kbv.h"
// #include "printGameOver.h"
// #include "get_key.h"

const int apple_id = 0;
const int snake_id = 1;
const int empty_id = 2;

#define SNAKEX_NUM 18 // yılan oyununda dikey çizgilerin sayısı -2 (dinamik)
#define SNAKEY_NUM 24 // yılan oyununda yatay çizgilerin sayısı -2 (dinamik)
#define SNAKESLIDEX 3 // Ekranın kenarlarındaki boşluk
#define DEFAULT_SNAKE_MENU_COLOR 0x0000

#define DARKCYAN 0x03EF
#define YELLOW 0xFFE0
#define CYAN 0x07FF

// snake fonksiyonları
void openSnakeMenu(MCUFRIEND_kbv);
void printSnakeMenu(MCUFRIEND_kbv);
void printSnakePixel(int, int, String, MCUFRIEND_kbv);


class Pixel{
public:
    int x;
    int y;
    String val;
    MCUFRIEND_kbv tft;

    Pixel(MCUFRIEND_kbv tft){
        this->tft = tft;
    }

    void set_pixel(){
        printSnakePixel(this->x, this->y, this->val, this->tft);
    }
};

class snakePart{
public:
    int x;
    int y;
    int num;
    snakePart *next;
};


// yılan şeylerini çizdirme
void printSnakeMenu(MCUFRIEND_kbv tft){
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

    // 1 sağ
    // 2 aşağı
    // 3 sol
    // 4 yukarı
    enum Direction {
        STOP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
        UP = 4
    };

    // snake
    snakePart *head = NULL;
    head = new snakePart();

    head->x = 5;
    head->y = 5;
    head->num = 0;
    head->next = NULL;

    snakePart *old_head = NULL;
    old_head = new snakePart();

    old_head->x = head->x;
    old_head->y = head->y;
    old_head->num = head->num;

    Direction direction;

    String r_key = "";

    int cur_dir = STOP;
    int next_dir = STOP;

    printSnakeMenu(tft); // mavi çizgiler
    printSnakePixel(head->x, head->y, snake_id, tft);

    String key;

    while (true)
    {
        // hatırlamıyorum ve karıştırma
        long start_key = millis();

        while (true)
        {
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
        cur_dir = next_dir;

        if (key.compareTo("right") == 0 && cur_dir != LEFT)
            next_dir = RIGHT;
        else if (key.compareTo("down") == 0 && cur_dir != UP)
            next_dir = DOWN;
        else if (key.compareTo("left") == 0 && cur_dir != RIGHT)
            next_dir = LEFT;
        else if (key.compareTo("up") == 0 && cur_dir != DOWN)
            next_dir = UP;
        else if (key.compareTo("next") == 0)
            next_dir = STOP;

        if (key.compareTo("back") == 0)
            return;
        

        old_head->x = head->x;
        old_head->y = head->y;

        switch (next_dir)
        {
        case RIGHT:
            if (head->x <= (SNAKEX_NUM - 4))
                head->x++;

            else {
                printGameOver(tft);
                return;
            }

            break;
        case DOWN:
            if (head->y <= (SNAKEY_NUM - 4))
                head->y++;

            else {
                printGameOver(tft);
                return;
            }

            break;
        case LEFT:
            if (head->x != 0)
                head->x--;

            else {
                printGameOver(tft);
                return;
            }

            break;
        case UP:
            if (head->y != 0)
                head->y--;

            else {
                printGameOver(tft);
                return;
            }
            
            break;
        }

        // snakePart *n = NULL;
        // n = head;

        // if(n->next != NULL){
        //     while(true){
        //         n->x = n->next->x
        //         n->y = n->next->y
        //         n = n->next

        //         if (n->next == NULL)
        //             break;
        //     }
        // }
        printSnakePixel(old_head->x, old_head->y, empty_id, tft);
        printSnakePixel(head->x, head->y, snake_id, tft);
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
