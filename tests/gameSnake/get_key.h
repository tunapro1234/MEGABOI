#define BUTTON_TOLERANCE 80 // Butonların töleransı
#define BUTTON_NEXT A9      // Butonların bağlı olduğu pinler
#define BUTTON_UP A10
#define BUTTON_DOWN A11
#define BUTTON_LEFT A12
#define BUTTON_BACK A13
#define BUTTON_RIGHT A14

String key_get(){
    String key = "";
    while (true)
    {
        if (analogRead(BUTTON_DOWN) < BUTTON_TOLERANCE) key = "down";
        
        else if (analogRead(BUTTON_UP) < BUTTON_TOLERANCE) key = "up";
        
        else if (analogRead(BUTTON_RIGHT) < BUTTON_TOLERANCE) key = "right";
        
        else if (analogRead(BUTTON_LEFT) < BUTTON_TOLERANCE) key = "left";

        else if (analogRead(BUTTON_NEXT) < BUTTON_TOLERANCE) key = "next";
        
        else if (analogRead(BUTTON_BACK) < BUTTON_TOLERANCE) key = "back";
        
        return key;
    }
}
