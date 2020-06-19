# Kod konusunda yardıma sonuna kadar açığım 
C++ çok etkin olduğum bir dil değil o yüzden sıkıntı çekmiyorum desem yalan olur

*Bu sefer readme kasmakla uğraşmayacağım*

Libraries klasörü içinde ekran için gerekli libraryler var onları direkt olarak C:/Users/%username%/Documents/Arduino/libraires klasörünün içine atabilirsiniz


    2.4" TFT LCD Dokunmatik Ekran Shield Sd kart dahil
    
    6 buton
    
    esp8266 (Serial0'a bağlı)
    
    Fat32 formatlı sd kart



SPI arayüzü şeyleri yüzünden sd kart olayı direkt olarak megada çalışmıyor biraz modifiye lazım, shield da serial0 pinlerini yiyor onlar için de modifiye gerekli 
Taşınabilirliği arttırmak için lion + düşürücü arttırıcı devre filan taktım bir ara şemaları paylaşırım

Şimdi bu megada 4 tane filan serial var neden ekranın yediğini kullandın diyebilirsiniz cevap çok basit bilmiyorum. ekran olmadan esp ile serial1 biraz sıkıntı çıkardı. Ayrıca ekranın büyüklüğü yüzünden sadece serial1 açık kalıyor ona da muhtemelen bluetooth takarım.

Akıllı ev tarzı projeler için biraz daha kumanda şeklinde eğlenceli bir şey olur diye düşünmüştüm ama oyun filan da eklemeyi düşünüyorum


Kodun en başında hangi butonun hangi pine bağlandığı tanımlanıyor. Butonlar input puluup olarak tanımlanıyor dirence gerek yok ama vcc yerine gnd bağlayın

Sd kart olayı megada işkence gibi modifiye ettim ama çalışmadı o yüzden sanal spi tarzında bir şey yapmak gerekiyor [buradan](https://learn.adafruit.com/adafruit-data-logger-shield/for-the-mega-and-leonardo) nasıl yapıldığına bakabilirsiniz

Snake bitti mario filan gelcek varsa bana ulaşın instagram: @tunapro1234