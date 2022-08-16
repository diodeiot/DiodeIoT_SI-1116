# SI-1116 - ESP32 16 Kanal Röle Geliştirme Modülü

![Build Status](https://github.com/diodeiot/DiodeIoT_SI-1116/workflows/Arduino%20Library%20CI/badge.svg)

![top](https://user-images.githubusercontent.com/100811304/159191696-64baa4ca-0a0f-46b5-a1e3-64587b23d128.png)

## SI-1116 Nedir?
SI-1116, üzerinde ESP32 mikrodenetleyicisi bulunan 16 kanal röle geliştirme modülüdür. \
Geliştiriciler, zengin örnek kodlara sahip bu kütüphaneyi kullanarak kendi uygulamalarını kolayca geliştirebilirler.

Bu geliştirme modülü:

* Akıllı Evler
* Ev Otomasyonu
* Endüstriyel Otomasyon
* Araç İçi Otomasyon
* Güç Anahtarlama

başta olmak üzere amatör ve profesyonel herhangi bir amaç için kullanılabilir.

## Dökümantasyon
[<img alt="github-pages" width="150px" src="https://user-images.githubusercontent.com/100811304/184258420-58ed4a45-29ce-4329-9260-c54ae8973690.png" />](https://diodeiot.github.io/DiodeIoT_SI-1116)

Kaynak kodların dökümantasyonuna [buradan](https://diodeiot.github.io/DiodeIoT_SI-1116) ulaşabilirsiniz.

## Teknik Özellikler

### Pin Bağlantıları

Eleman | Pin Numarası | Lojik Seviye
-- | :--: | --
BOOT Butonu | 0 | Active Low
LED | 2 | Active Low
Röle 1 | 22 | Active High
Röle 2 | 21 | Active High
Röle 3 | 19 | Active High
Röle 4 | 18 | Active High
Röle 5 | 5 | Active High
Röle 6 | 17 | Active High
Röle 7 | 16 | Active High
Röle 8 | 4 | Active High
Röle 9 | 23 | Active High
Röle 10 | 13 | Active High
Röle 11 | 32 | Active High
Röle 12 | 33 | Active High
Röle 13 | 25 | Active High
Röle 14 | 26 | Active High
Röle 15 | 27 | Active High
Röle 16 | 14 | Active High

### Elektriksel Karakteristikler

Parametre | Minimum | Nomimal | Maximum | Birim
-- | :--: | :--: | :--: | --
Giriş Gerilimi | 4.75 | 5 | 5.5 | V
Giriş Akımı | | 1.1 | | A
Röle Anahtarlama Akımı | | | 10 | A
Röle Anahtarlama Gerilimi | | | 250 | VAC

> :warning: **Uyarı**\
> Sadece 5V güç kaynağı ile kullanın.

> :warning: **Uyarı**\
> Güç kaynağını doğru polaritede bağlayın.

### Termal Bilgiler

Parametre | Minimum | Nomimal | Maximum | Birim
-- | :--: | :--: | :--: | --
Çalışma Sıcaklığı | -40 | | 85 | °C

### Mekanik Bilgiler

Parametre | Minimum | Nomimal | Maximum | Birim
-- | :--: | :--: | :--: | --
Genişlik | | 80 | | mm
Uzunluk | | 160 | | mm
Yükseklik | | 19.1 | | mm

## Gerekenler

## 1. SI-1116 Geliştirme Modülü
SI-1116 geliştirme modülünü aşağıdaki online marketlerden edinebilirsiniz:

[direnc.net](https://www.direnc.net/)

## 2. USB-UART Dönüştürücü
SI-1116 geliştirme modülünü bilgisayara bağlamak için 3.3V usb-uart dönüştürcü kullanmanız gerekmektedir. 
Dönüştürücünün `RX` `TX` `GND` pinlerini modülün `TX` `RX` `GND` pinlerine bağlayın.

> :warning: **Uyarı**\
> Modülü bilgisayarınıza bağlamak için modüle harici güç kaynağı bağlamanız gerekmektedir.

## 3. 5V Güç kaynağı
SI-1116 geliştirme modülüne 5V minimun 1A güç kaynağı bağlamalısınız.

> :warning: **Uyarı**\
> Güç kaynağını doğru polaritede bağlayın.

## 4. SI-1116 Kütüphanesi
Bu kütüphane SI-1116 geliştirme modülü için yazılmış arduino ESP32 kütüphanesidir. Geliştiriciler, zengin örnek kodlara sahip bu kütüphaneyi kullanarak kendi uygulamalarını kolayca geliştirebilirler.

> :warning: **Uyarı**\
> Bu kütüphane sadece Arduino IDE 1.5.x ve üzeri versiyonları ile uyumludur.

### Arduino IDE Kurulumu
Bu kütüphaneyi kullanmak için ilk olarak Arduino IDE gereklidir. Eğer sisteminizde Arduino IDE yüklü değil ise [burada](https://www.arduino.cc/en/software) anlatıldığı şekilde programın son sürümünü yükleyebilirsiniz.

### ESP32 Arduino Çekirdeğini Yükleme
Arduino IDE'nizi kurduktan sonra ESP32 mcu'nuzda kod geliştirmek için kullanacağınız ESP32 arduino çekirdeğini yüklemelisiniz. Bu yüklemeyi [burada](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) anlatıldığı şekilde arduino ide'nizdeki kütüphane yöneticisi ile kolayca yapabilirsiniz.

### SI-1116 Kütüphanesi Kurulumu

![image](https://user-images.githubusercontent.com/111313342/184769542-895650d1-e4da-48d0-a6c0-76493f08e0a0.png)

SI-1116 kütüphanesini kurmak için yukarıda görüldüğü gibi kütüphaneyi zip halinde bilgisayarınıza indirin.

![image](https://user-images.githubusercontent.com/100811304/159194858-39a47764-ab8b-4f42-8298-798982687959.png)

Daha sonra arduino idenizi açıp yukarıda görülen seçeneğe tıklayıp indirdiğiniz SI-1116 kütüphanesini bilgisayarınıza kurun.

Bu adımları tamamladıktan sonra arduino idenizden dilediğiniz SI-1116 kütüphane örneklerini inceleyebilirsiniz.

## Örnek Kodlar
Örnek kodlara [buradan](./examples) erişebilirsiniz.

* [Buton ile Röle Kontrolü](./examples/button_relay_control/button_relay_control.ino) \
Bu örnekte kartın üzerindeki BOOT butonuna her bastığınızda sırası ile röleler açılmaktadır.

* [MQTT Protokolü ile Röle Kontrolü](./examples/mqtt_relay_control/mqtt_relay_control.ino) \
Bu örnekte mqtt ile kartın üzerindeki röleleri uzaktan kontrol ediyoruz.

* [Seri Konsol ile Röle Kontrolü](./examples/serial_terminal_relay_control/serial_terminal_relay_control.ino) \
Bu örnekte seri konsol ile kartın üzerindeki röleleri kontrol ediyoruz.

## Kütüphaneye Katkıda Bulunma
SI-1116 kütüphanesine katkılarınızı memnuniyetle karşılarız.
Kütüphaneye dilediğiniz katkıyı `Pull Request` ile yapabilirsiniz.

## Lisans
LGPL (GNU Kısıtlı Genel Kamu Lisansı)

![license](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3b/LGPLv3_Logo.svg/200px-LGPLv3_Logo.svg.png)
