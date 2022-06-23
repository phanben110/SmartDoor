#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <Servo.h>
#define servo1Pin D6
#define button D5
Servo servo;


unsigned long now = millis();
unsigned long lastTrigger = 0;
unsigned long lastTrigger1 = 0;
unsigned long triggerTimeout = 0;
boolean startTimer = false;
boolean startTimer1 = false;
#define timeSeconds 1
#define angle 140
#define timeout = 10

int status = WL_IDLE_STATUS;
const char* ssid = "FtechAI"; //  your network SSID (name)
const char* pass = "Ft3ch#20@).DN";      // your network password

unsigned int localPort = 5007;      // local port to listen for UDP packets

byte packetBuffer[512]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  pinMode(button, INPUT_PULLUP);


  servo.attach(servo1Pin); // NodeMCU D4 pin
  attachInterrupt(digitalPinToInterrupt(button), blink1, FALLING);
  servo.write(36);
  delay(100);
  servo.write(36 * 2);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // setting up Station AP
  WiFi.begin(ssid, pass);

  // Wait for connect to AP
  Serial.print("[Connecting]");
  Serial.print(ssid);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries > 30) {
      break;
    }
  }

  Serial.println();


  printWifiStatus();

  Serial.println("Connected to wifi");
  Serial.print("Udp server started at port ");
  Serial.println(localPort);
  Udp.begin(localPort);

  delay(200);
  servo.write(36);
  delay(100);
  servo.write(36 * 2);
}

void loop()
{
  int noBytes = Udp.parsePacket();
  if ( noBytes ) {
    Serial.print(millis() / 1000);
    Serial.print(":Packet of ");
    Serial.print(noBytes);
    Serial.print(" received from ");
    Serial.print(Udp.remoteIP());
    Serial.print(":");
    Serial.println(Udp.remotePort());
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, noBytes); // read the packet into the buffer

    // display the packet contents in HEX
    now = millis();
    for (int i = 1; i <= noBytes; i++) {
      Serial.print(packetBuffer[i - 1], HEX);
      if ( packetBuffer[i - 1] == '1')
      {
        servo.write(angle);
        startTimer1 = true;
        lastTrigger1 = millis();
      }
      else if (startTimer && (now - lastTrigger > (timeSeconds * 1000))) {
        Serial.println("Motion stopped...");
        servo.write(36 * 2);
        startTimer = false;
      }
      else if (startTimer1 && (now - lastTrigger1 > (timeSeconds * 1000))) {
        Serial.println("Motion stopped...");
        servo.write(36 * 2);
        startTimer1 = false;
      }

      if (i % 32 == 0) {
        Serial.println();
      }
      else Serial.print(' ');
    } // end for
    Serial.println();
  } // end if


}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


ICACHE_RAM_ATTR void blink1() {
  if (startTimer1 == false && startTimer == false )
  {
    servo.write(angle);
    startTimer = true;
    lastTrigger = millis();
  }

}
