#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define SDA_PIN 12  //GPIO12 / 6
#define SCL_PIN 14  //GPIO14 / 5
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCL_PIN, SDA_PIN, U8X8_PIN_NONE);
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  u8g2.begin();
}
void loop() {
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  bool hidden;
  int scanResult;
  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);
  if (scanResult == 0) {
    Serial.println(F("Keine WiFi-Netzwerke gefunden"));
  } else if (scanResult > 0) {
    //Zwischenspeicher und Display leeren
    u8g2.clearBuffer();
    //Schriftgröße setzen
    u8g2.setFont(u8g2_font_ncenB08_tr);
    
    for (int8_t i = 0; i < scanResult; i++) {
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
      printWiFiNetworkData(i, ssid.c_str());
      Serial.printf(PSTR("  %02d: %s\n"), i + 1, ssid.c_str());
      yield();
    }
    //Absenden der Daten vom Zwischenspeichern an das Display
    u8g2.sendBuffer();
  } else {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
  //5 Sekunden Pause zwischen den Scans
  delay(5000);
}
//Ausgeben der Daten zum WiFi Netzwerk auf dem OLED Display
void printWiFiNetworkData(int idx, String name) {
  String msg = String(idx, DEC) + " " + name;
  u8g2.drawStr(0, idx * 15, msg.c_str());
}