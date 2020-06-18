#include "MCUFRIEND_kbv.h"
// #include "get_key.h"
// #include "Terminal.h"

#define wait_time 160       // Tuş hassasiyeti için bekleme süresi
#define BLACK 0x0000 
#define WHITE 0xFFFF

// void esp_server_test(Term);
// void openESPTestMenu(MCUFRIEND_kbv);

void esp_server_test(Term terminal){
    String gelen = "";
    char serialdenokunan;

    while(Serial.available()>0){
        serialdenokunan = Serial.read();
        gelen += serialdenokunan;
    }

    Serial.println(gelen);
    if((gelen.indexOf(":GET /?color=white")>1)){  
        terminal.print("WHITE");
    }

    if((gelen.indexOf(":GET /?color=black")>1)){ 
        terminal.print("BLACK");
        
    }
}

void openESPTestMenu(MCUFRIEND_kbv tft){
    Term terminalESP(1, tft);
    terminalESP.init();
    terminalESP.print("ESP CONFIG STARTING");
    
    const char* ssid = "raspi-mainboard";
    const char* passphrase =  "tunapro1234";

    Serial.begin(115200);
    Serial.println("AT"); 
    delay(3000);
        
    if(Serial.find("OK")){
        terminalESP.print("AT OK");

        Serial.println("AT+CWMODE=1");
        delay(2000);

        String baglantiKomutu = String("AT+CWJAP=\"") + ssid + "\",\"" + passphrase + "\"";
        Serial.println(baglantiKomutu);
        delay(5000);
    }
    
    else {    
        terminalESP.print("AT FAIL");        
        
        while (true){
            if (key_get().compareTo("back") == 0)
                return;
            
            delay(wait_time);
        }
    }

    Serial.print("AT+CIPMUX=1\r\n");
    delay(200);

    Serial.print("AT+CIPSERVER=1,80\r\n");
    delay(1000);

    terminalESP.print("SANIRIM CONNECTED");

    while(true){
        if(Serial.available() > 0){
            key = key_get();
            
            if (key.compareTo("back") == 0)
                return;
            
            else if(Serial.find("+IPD,")){
                String metin = "<head> TUNAPRO1234 </head>";
                metin += "<br><a href=\" ?color=white\"><button type='button'>WHITE</button></a>"; 
                metin += "<br><a href=\" ?color=black\"><button type='button'>BLACK</button></a>";      

                String cipsend = "AT+CIPSEND=";
                cipsend +="0";
                cipsend +=",";
                cipsend += metin.length();
                cipsend += "\r\n";

                Serial.print(cipsend);
                delay(500);
                Serial.println(metin);
                esp_server_test(terminal);
                Serial.println("AT+CIPCLOSE=0");
            }            
            
            // delay(wait_time); // ne yapsam emin değilim tuşları okumuyor pff
        }
    }
}
