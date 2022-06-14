#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define servo1Pin D4
Servo servo;

//char ssid[] = "COVID19";
//char pass[] = "13131313";
char ssid[] = "FtechAI";
char pass[] = "Ft3ch#20@).DN";
char auth[] = "CUTYUFpdmQ21rByDrCtqw7dP6x_KPH4w"; // Nhập AuthToken

void setup()
{
  Serial.begin(9600);
  servo.attach(servo1Pin); // NodeMCU D4 pin
  servo.write(0);
  Blynk.begin(auth, ssid, pass);
  servo.write(5);
  delay(100);
  servo.write(0);
}

BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V4);

  // Alternatively, you could override server state using:
  //Blynk.virtualWrite(V2, ledState);
}


void loop()
{

  Blynk.syncVirtual(V4);
  Blynk.run();

}
BLYNK_WRITE(V1)
{
  servo.write(param.asInt());
  //Serial.println(param.asInt());
}

BLYNK_WRITE(V2)
{
  servo.write(0);
  //Serial.println(param.asInt());
}

BLYNK_WRITE(V3)
{
  servo.write(90 * 2);
  //Serial.println(param.asInt());
}

BLYNK_WRITE(V4)
{
  Serial.println(param.asInt());
  if ( param.asInt() == 1 )
  {
    servo.write(36 * 2);
    delay ( 1500 );
    servo.write(0);
    Blynk.virtualWrite(V4, 0);
    //Serial.println(param.asInt());
  }
}

BLYNK_WRITE(V5)
{
  Serial.println(param.asInt());
  if ( param.asInt() == 1 )
  {
    servo.write(36 * 2);
    delay ( 1500 );
    servo.write(0);
    Blynk.virtualWrite(V5, 0);
    //Serial.println(param.asInt());
  }
}

///* Servo */
//#define servo1Pin D4
//#include <Servo.h>
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
//
//Servo servo1;
//// Comment this out to disable prints and save space
//#define BLYNK_PRINT Serial
//
//
//// Your WiFi credentials.
//// Set password to "" for open networks.
//char ssid[] = "COVID19";
//char pass[] = "13131313";
//char auth[] = "CUTYUFpdmQ21rByDrCtqw7dP6x_KPH4w"; // Nhập AuthToken
//
//void setup ()
//{
//
//  Serial.begin(9600);
//  Blynk.begin(auth, ssid, pass);
//  servo1.attach(servo1Pin);
//  servo1.write(90);
//}
//void loop()
//{
//  Blynk.run();
////  servo1.write(0);
////  delay(500);
////  servo1.write(90) ;
////  delay(500);
////  Serial.println("OK");
//}
