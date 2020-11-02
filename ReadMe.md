# Kod konusunda yardıma sonuna kadar açığım 

lib klasörü içinde ekran için gerekli libraryler var onları Arduino IDE Sketch > Include Library > Add .ZIP Library... yaparak ekleyebilirsiniz.

1. Gereksinimler
    * 2.4" TFT LCD Dokunmatik Ekran Shield Sd kart dahil
    * 6 buton
    * esp8266 (Serial0'a bağlı)
    * Fat32 formatlı sd kart

SPI arayüzü şeyleri yüzünden sd kart olayı direkt olarak megada çalışmıyor biraz modifiye lazım, shield da serial0 pinlerini yiyor onlar için de modifiye gerekli.
Taşınabilirliği arttırmak için lion + düşürücü arttırıcı devre filan taktım bir ara şemaları paylaşırım (sanmıyorum).

Şimdi bu megada 4 tane filan serial var neden ekranın yediğini (serial0) kullandın diyebilirsiniz cevap çok basit bilmiyorum. ekran olmadan esp ile serial1 biraz sıkıntı çıkardı. Ayrıca ekranın büyüklüğü yüzünden sadece serial1 açık kalıyor ona da muhtemelen bluetooth takarım.

Akıllı ev tarzı projeler için biraz daha kumanda şeklinde eğlenceli bir şey olur diye düşünmüştüm ama oyun filan da eklemeyi düşünüyorum.


Kodun en başında hangi butonun hangi pine bağlandığı tanımlanıyor. Butonlar input pullup olarak tanımlanıyor dirence gerek yok ama vcc yerine gnd bağlayın.

Sd kart olayı megada işkence gibi modifiye ettim ama çalışmadı o yüzden sanal spi tarzında bir şey yapmak gerekiyor [buradan](https://learn.adafruit.com/adafruit-data-logger-shield/for-the-mega-and-leonardo) nasıl yapıldığına bakabilirsiniz.


Şu an en çopk istediğim şey oyunlardan ziyade [RSP](https://github.com/RSP-tk/RSP)'yi buna özel bir sürümle getirebilmek, evet internete bağlanmak çok zor ve herhangi bir şekilde mesaj yazmamı sağlayacak bir arayüz de yok, tuşlar da yeterli değil, ama zaten tuşlar değiştirilebilmek için tasarlandı o yüzden belki klavye bağlamamızı sağlayacak bir usb eklentisi yapabilirim. Ama üniversite sınavı :-(

### Proje açık kaynak ve başka insanların da yararlanmasını çok isterdim ama böyle bir şeyin neredeyse imkansız olduğunu biliyorum o yüzden rahat davranıyorum (şemaları paylaşmamak gibi davranışlardan söz ediyorum)
Herhangi biri rica ederse severek yapmalarına yardımcı olurum.