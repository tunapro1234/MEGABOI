#include "MCUFRIEND_kbv.h"
// #include "get_key.h"
#include "Terminal.h"

#include <SPI.h>
#include <SD.h>

#define wait_time 160       // Tuş hassasiyeti için bekleme süresi

Term terminalSD(1, tft);

void openSDTestMenu(MCUFRIEND_kbv tft){
    termianlSD.init();
    
    termianlSD.print("SD INIT STARTING");

    File myFile;

    if (!SD.begin(10, 11, 12, 13)) {
        termianlSD.print("SD INIT FAIL");
        
        while (true){
            if (key_get().compareTo("back") == 0)
                return;

            delay(wait_time);
        }
    }
    // SD librarysinin read-write örneği
    myFile = SD.open("test.txt", FILE_WRITE);
    
    if (myFile) {
        termianlSD.print("Writing to test.txt...");
        
        myFile.println("testing 1, 2, 3.");
        
        myFile.close();
        termianlSD.print("done.");
    } else {
        termianlSD.print("error opening test.txt");
    }
    
    myFile = SD.open("test.txt");
    if (myFile) {
        termianlSD.print("test.txt:");
        
        while (myFile.available()) {
            termianlSD.print(myFile.read());
        }
        myFile.close();
    } 
    else {
        termianlSD.print("error opening test.txt");
    }

}
