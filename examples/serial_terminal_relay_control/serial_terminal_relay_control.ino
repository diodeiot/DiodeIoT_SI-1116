/**
  @file serial_terminal_relay_control.ino

  @brief Seri port ile röle kontrolü.

  @details Bu örnekte seri konsol ile kartın üzerindeki röleleri kontrol ediyoruz.

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
  Bu örnekte seri konsol ile kartın üzerindeki röleleri kontrol ediyoruz.
  1. Örneği karta yükleyin.
  2. Araçlar->Seri Port Ekranı ile seri konsolu açın.
  3. Seri konsolun sağ alt köşesinden haberleşme hızını "115200" bps yapın.
  4. Seri konsolun sağ alt köşesinden satır sonunu "Yeni Satır" olarak değiştirin.
  5. Herhangi bir röleyi açmak için "open" ve hemen yanına açmak istediğiniz rölenin kanal numarasını yazıp enter yapın. Örneğin "open1".
  6. Herhangi bir röleyi kapatmak için "close" ve hemen yanına kapatmak istediğiniz rölenin kanal numarasını yazıp enter yapın. Örneğin "close1".
*/
#include <Arduino.h>

// Kartımız için gerekli olan kütüphane headerını ekliyoruz.
#include "si1116.h"

void setup(void)
{
  // Seri haberleşmeyi 115200 bps ile başlatıyoruz.
  Serial.begin(115200);

  Serial.printf("example started\n");

  // Kartımızın gerekli olan başlangıç ayarlarını yapıyoruz.
  si1116.init();
}

void loop(void)
{
  // Burada seri konsoldan gelen verileri izliyoruz.
  // Eğer gelen veri uygun formatta ise işlemi yerine getirip seri konsola onay mesajı gönderiyoruz, değil ise hata mesajı gönderiyoruz.
  if(Serial.available() > 0)
  {
    delay(10);
    String str = Serial.readStringUntil('\n');
    str.trim();

    if(str.startsWith(String("open")))
    {
      str.replace(String("open"), String(""));
      str.trim();
      int ch = str.toInt();
      if(ch >= 1 && ch <= 16)
      {
        si1116.setRelay(ch, 1);
        Serial.printf("[Info] Relay %d is opened\n", ch);
      }
      else
      {
        Serial.printf("[Error] Wrong parameter: \"%s\"!\n", str.c_str());
      }
    }
    else if(str.startsWith(String("close")))
    {
      str.replace(String("close"), String(""));
      str.trim();
      int ch = str.toInt();
      if(ch >= 1 && ch <= 16)
      {
        si1116.setRelay(ch, 0);
        Serial.printf("[Info] Relay %d is closed\n", ch);
      }
      else
      {
        Serial.printf("[Error] Wrong parameter: \"%s\"!\n", str.c_str());
      }
    }
    else
    {
      Serial.printf("[Error] Wrong parameter: \"%s\"!\n", str.c_str());
    }
  }
}