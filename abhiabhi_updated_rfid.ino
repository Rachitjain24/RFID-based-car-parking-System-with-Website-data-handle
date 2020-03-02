#include <ezTime.h>
#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Timezone myLocalTime;

#define SS_PIN D4
#define RST_PIN D3
#define SCK_PIN D5  //connect the relay to number 2 pin
#define MOSI_PIN D7 // connect the buzzer to 3 pin
#define MISO_PIN D6
#define RELAY D0
#define BUZZER D8
#define ACCESS_DELAY 500
#define DENIED_DELAY 500
 
  // wifi and fire base credentials
  
#define FIREBASE_HOST "rfid-6fe7a.firebaseio.com"
#define FIREBASE_AUTH "0ZuOjHmWZGUVOJVuoh3Et2WxVTbJ8izJLGi3nR0A"
#define WIFI_SSID "RACHIT'S WIFI"
#define WIFI_PASSWORD "rachitjain24" 

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);
  Serial.println("Put your card to the reader for scanning ...");
  Serial.println();
  //connection to wifi
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
   delay(500);
   }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(WiFi.localIP());
   Firebase.begin(FIREBASE_HOST);

    // Set desired time zone for Timezone object declared in the beginning
  myLocalTime.setLocation(F("IN")); // set your time zone

  // Sync NTP time for ezTime library
  waitForSync(); 

  delay(2000);
}
void loop() 
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

   String Ctime,Cdate;
  Ctime = myLocalTime.dateTime("H:i:s");
  Cdate = myLocalTime.dateTime("d.m.Y");

  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cardsM
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "19 77 A7 8B") // CARD1
  { 
    Serial.println("Authorized access");
    Serial.println();
    ////delay(500);
    
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    display.println("WELCOME RACHIT");
    display.println("AUTHORISED");
    display.display();
    String User = "AKASH GUPTA";
    //Serial.println("Chal rha h");
    Firebase.pushString("Name",User);
    Firebase.pushString("Date",Cdate);
   Firebase.pushString("Time",Ctime);
    if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
      
    return;
  }
    
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}
   }
  else if (content.substring(1) == "19 A4 9B 6E") // KEY_RING
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}
   
  }
  else if (content.substring(1) == "DB 4C 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   

    String User = "HARDIC JAIN";
    Firebase.pushString("Name",User);
    Firebase.pushString("Date",Cdate);
   Firebase.pushString("Time",Ctime);
    if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());  
    return;
  }
    
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}
  }
  
  
 else if (content.substring(1) == "8B 51 F2 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "AB 51 FF 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "EB 8B 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "3B 87 EB 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "FB B0 EC 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "0B C8 FB 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "9B 40 F8 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "5B 5B F4 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "8B 68 FF 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "2B DE EE 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "7B B6 F7 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "1B C9 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "CB 80 F2 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "DB 57 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "FB C2 F9 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "7B C6 0E 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "2B 05 ED 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "0B 89 EB 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  
 else   {
    Serial.println(" Access denied");
    display.println(" NOT AUTHORISED");
  display.display();
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    noTone(BUZZER);
    
  }
}
