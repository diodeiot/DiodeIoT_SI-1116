/**
  @file button_relay_control.ino

  @brief Buton ile röle kontrol uygulaması.

  @details Bu örnekte kartın üzerinde bulunan buton ile röleleri sırası ile
  açacağız.

  @authors Diode IoT Inc. <info@diodeiot.com>

  @authors Kadir Sevil <kadir.sevil@diodeiot.com>

  @copyright Copyright (c) 2021-2022 Diode Iot Inc. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
  Kartın üzerindeki BOOT butonunu program içinde kendi amaçlarınız için kullanabilirsiniz.
  Bu örnekte kartın üzerindeki BOOT butonuna her bastığınızda sırası ile röleler açılmaktadır.
*/
#include <Arduino.h>

// Kartımız için gerekli olan kütüphane headerını ekliyoruz.
#include "si1116.h"

// Bu değer o anda açık olan rölenin kanal numarasını tutmaktadır.
// Rölelerin kanal numaralarını kartın ön yüzünde görebilirsiniz.
int current_button = 0;

void setup(void)
{
  // Kartımızın gerekli olan başlangıç ayarlarını yapıyoruz.
  si1116.init();
}

void loop(void)
{
  // Buton debounce için loop() fonksiyonunu bir döngü içerisinde çağırmalıyız.
  // Eğer buton kullanılmayacaksa bu fonksiyonu kullanmayabilirsiniz.
  si1116.loop();

  // Butona basılma durumunu isButtonPressed() fonsiyonu ile kontrol ediyoruz.
  // Eğer fonksiyon true döndürüyorsa butona basılmış demektir.
  // Eğer butona basıldıysa önceki röleyi bırak ve bir sonraki röleyi aç.
  if(si1116.isButtonPressed())
  {
    si1116.ledOn();
    delay(10);
    si1116.ledOff();

    //önceki röleyi bırak
    si1116.setRelay(current_button, 0);

    if(current_button == 16)
    {
      current_button = 0;
    }
    else
    {
      current_button++;
    }

    // Sonraki röleyi aç.
    si1116.setRelay(current_button, 1);
  }
}