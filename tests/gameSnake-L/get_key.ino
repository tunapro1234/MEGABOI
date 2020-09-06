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
