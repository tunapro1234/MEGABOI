#include "MCUFRIEND_kbv.h"
// #include "get_key.h"
// #include "Terminal.h"

#include <SPI.h>
#include <SD.h>

#define wait_time 160       // Tuş hassasiyeti için bekleme süresi



void openSDTestMenu(MCUFRIEND_kbv tft){
    Term terminalSD(1, tft);
    terminalSD.init();
    
    terminalSD.print("SD INIT STARTING");

    File myFile;

    if (!SD.begin(10, 11, 12, 13)) {
        terminalSD.print("SD INIT FAIL");
        
        while (true){
            if (key_get().compareTo("back") == 0)
                return;

            delay(wait_time);
        }
    }
    // SD librarysinin read-write örneği
    myFile = SD.open("test.txt", FILE_WRITE);
    
    if (myFile) {
        terminalSD.print("Writing to test.txt...");
        
        myFile.println("testing 1, 2, 3.");
        
        myFile.close();
        terminalSD.print("done.");
    } else {
        terminalSD.print("error opening test.txt");
    }
    
    myFile = SD.open("test.txt");
    if (myFile) {
        terminalSD.print("test.txt:");
        
        while (myFile.available()) {
            terminalSD.print(myFile.read());
        }
        myFile.close();
    } 
    else {
        terminalSD.print("error opening test.txt");
    }

}
