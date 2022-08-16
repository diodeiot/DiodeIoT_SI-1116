/**
  @file mqtt_relay_control.ino

  @brief MQTT protokolü ile röle kontrol uygulaması.

  @details Bu örnekte kartın üzerindeki röleleri MQTT protokolü ile uzaktan kontrol edeceğiz.

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
  Bu örnekte MQTT ile kartın üzerindeki röleleri uzaktan kontrol ediyoruz.
  1. "WIFI_SSID" değişkenine WiFi'ınızın adını, "WIFI_PASSWORD" değişkenine WiFi'ınızın şifresini yazın.
  2. Örnek kodu derleyip karta yükleyin.
  3. Araçlar->Seri Port Ekranı ile seri konsolu açın.
  4. Seri konsolun sağ alt köşesinden haberleşme hızını "115200" bps yapın.
  5. Bilgisayarınıza herhangi bir MQTT client programı indirin.
  6. İndirdiğiniz MQTT client programında MQTT broker olarak test.mosquitto.org, MQTT broker port olarak 1883 girin.
  7. İndirdiğiniz MQTT client programından topic olarak SI1116-[mac adresi]/relay yazın. [mac adresi] alanı seri konsoldan görebileceğiz ESP32'nin mac adresi
  olmalıdır. Örneğin SI1116-4C11AECCB9D0/relay
  8. Topic mesajı olarakta:
    -> Herhangi bir röleyi açmak için "open" ve hemen yanına açmak istediğiniz rölenin kanal numarasını yazıp enter yapın. Örneğin "open1".
    -> Herhangi bir röleyi kapatmak için "close" ve hemen yanına kapatmak istediğiniz rölenin kanal numarasını yazıp enter yapın. Örneğin "close1".
*/
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <esp_system.h>

// Kartımız için gerekli olan kütüphane headerını ekliyoruz.
#include "si1116.h"

// WiFi'ınızın adı.
const char* WIFI_SSID = "ssid";
// WiFi'ınızın şifresi.
const char* WIFI_PASSWORD = "password";

// MQTT client.
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Bu fonksiyon ile ESP32'nin mac adresini alıyoruz.
String getMacAddress(void)
{
  uint8_t base_mac[6];
  char base_mac_str[13];

  esp_read_mac(base_mac, ESP_MAC_WIFI_STA);
  snprintf(base_mac_str, sizeof(base_mac_str), "%02X%02X%02X%02X%02X%02X", base_mac[0], base_mac[1], base_mac[2], base_mac[3], base_mac[4], base_mac[5]);
  return String(base_mac_str);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  String str = "";
  for(int i = 0; i < length; i++)
  {
    str += (char)payload[i];
  }

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

void mqttConnect(void)
{
  Serial.printf("[Info] Connecting to MQTT Broker...\n");
  while(!mqttClient.connected())
  {
    Serial.print("[Warning] Reconnecting to MQTT Broker...\n");
    String clientId = "SI1116-" + getMacAddress();

    if(mqttClient.connect(clientId.c_str()))
    {
      Serial.printf("[Info] Connected\n");
      mqttClient.subscribe((clientId + String("/relay")).c_str());
    }
  }
}

void setup(void)
{
  // Seri haberleşmeyi 115200 bps ile başlatıyoruz.
  Serial.begin(115200);

  Serial.printf("example started\n");
  Serial.printf("ESP32 mac address: %s\n", getMacAddress().c_str());

  // Kartımızın gerekli olan başlangıç ayarlarını yapıyoruz.
  si1116.init();

  // WiFi'a bağlanıyoruz.
  Serial.printf("[Info] Connecting to \"%s\":", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.printf("->");
    delay(1000);
  }
  Serial.printf("\n[Info] Connected\n");

  // MQTT client'ı ayarlıyoruz.
  mqttClient.setServer("test.mosquitto.org", 1883);
  mqttClient.setCallback(mqtt_callback);

  // MQTT broker'ına bağlanıyoruz.
  mqttConnect();
}

void loop(void)
{
  // Eğer MQTT bağlantımız koparsa yeniden bağlanmayı deniyoruz.
  if(!mqttClient.connected())
  {
    Serial.printf("[Error] MQTT client disconnected!\n");
    mqttConnect();
  }

  // PubSubClient sınıfı senkron olduğundan gelen MQTT mesajlarından haberimizin olması için loop fonksiyonunu bir döngü içinde çağırıyoruz.
  mqttClient.loop();
}