/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32
31.01.2017 by Jan Hendrik Berlin
*/

#include <Arduino.h>
#include <WiFi.h>

const char* ssid     = "SCIENCE! (2.4GHz)";
const char* password = "supersecret";

#define ONBOARD_LED 5   //LED connected to digital pin 5

WiFiServer server(80);

int counter = 0;

void blink (int times) {
  int blink_time = 180;
  for (int i=0; i<times; i++) {
    digitalWrite(ONBOARD_LED, 0);
    delay(blink_time);
    digitalWrite(ONBOARD_LED, 1);
    delay(blink_time);
  }
}

void count_down (int starting_number) {
  int delay_time = 2000;
  for (int i=starting_number; i>0; i-- ) {
    blink(i);
    delay(delay_time);
  }
}


void setup() {

  Serial.begin(9600);
  pinMode(ONBOARD_LED, OUTPUT);

  // FIXME - this is just to give you time to connect a serial monitor
  count_down(5);

  delay(2000);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  delay(2000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);
}

void loop() {
  delay(1000);
  Serial.println("Hello World?");
  counter++;
  Serial.println(counter);
}