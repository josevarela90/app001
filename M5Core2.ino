#include <M5Core2.h>
#include <DHT.h>

#include <WiFi.h>
#include <ThingSpeak.h>
#define nombreRed "XYZ" 
#define claveRed "***" 

#define Canal 1786076
#define Clave "5ZYKJ1C0PC9COFVD"

WiFiClient cliente;
DHT Sensorth(19,DHT22);
int puertoH=35;
int rele=27;
long tiempo;
int relethingspeak,lectura=0,lecturaA=0;
int b=0;
void setup() {
  Sensorth.begin();
  M5.begin();
  M5.lcd.clear();
  M5.Lcd.fillScreen(BLACK);https://github.com/josevarela90/app001/tree/main
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.setTextSize(3);
  pinMode(rele,OUTPUT);
  M5.begin();
  ConectarWiFi();
  ThingSpeak.begin(cliente);
  tiempo=millis();

}
void loop() {
  
 if (millis()-tiempo > 5005)
 {
  int HS=analogRead(puertoH)/40.95;
  M5.lcd.clear();

   M5.Lcd.setTextColor(RED);
   M5.Lcd.setCursor(45,0);
  M5.Lcd.print("CONTROL DEL ");
   M5.Lcd.setTextColor(RED);
   M5.Lcd.setCursor(10,30);
  M5.Lcd.print("CULTIVO DE FRESA");

 M5.Lcd.setTextColor(BLUE);
   M5.Lcd.setCursor(0,70);
  M5.Lcd.print("Temp:");
   M5.Lcd.setCursor(160,70);
   float TA=Sensorth.readTemperature();
  M5.Lcd.print(TA);
   M5.Lcd.setCursor(250,70);
  M5.Lcd.print("oC");


   M5.Lcd.setCursor(0,115);
  M5.Lcd.print("H.Aire:");
M5.Lcd.setCursor(160,115);
int HA=Sensorth.readHumidity();
  M5.Lcd.print(HA);
   M5.Lcd.setCursor(250,115);
  M5.Lcd.print("%");
 
  M5.Lcd.setCursor(0,165);
  M5.Lcd.print("H.suelo:");
  M5.Lcd.setCursor(160,165);
  M5.Lcd.print(HS);
   M5.Lcd.setCursor(250,165);
  M5.Lcd.print("%");

    M5.Lcd.setTextColor(GREEN);
   M5.Lcd.setCursor(10,210);
  M5.Lcd.print("Bomba      Apagar");
  

   if (HS<100 && HA<100 && TA<50) 
   {
  ThingSpeak.setField(1,HS);
  ThingSpeak.setField(2,TA);
  ThingSpeak.setField(3,HA);
  ThingSpeak.writeFields(Canal,Clave);
  //relethingspeak = ThingSpeak.readIntField(Canal,4);
  //digitalWrite(rele,relethingspeak);
  }
  
  tiempo=millis();
  }

   M5.update();

 lectura = ThingSpeak.readIntField(Canal, 4);
 if (lectura!=lecturaA)
 {
    lecturaA=lectura;
    b=lecturaA;
    digitalWrite(rele,b);    
 }
 if (M5.BtnA.wasPressed())
 {  
  if (b==0)
    b=1;
  else
    b=0;
  digitalWrite(rele,b);
  ThingSpeak.setField(4,b);
  ThingSpeak.writeFields(Canal,Clave);
 }
  if (M5.BtnC.wasPressed())
    M5.shutdown();
  
}
void ConectarWiFi(){
  WiFi.begin(nombreRed,claveRed);
  M5.lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    M5.Lcd.print(".");
    delay(500);
    //WiFi.begin(nombreRed,claveRed);
  }
  M5.Lcd.print("OK");
}
