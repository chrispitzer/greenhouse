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

#define BACKWARDS_ASS_ONBOARD_LED 5   //LED connected to digital pin 5

WiFiServer server(80);

int counter = 0;

void blink (int times) {
  int blink_time = 180;
  for (int i=0; i<times; i++) {
    digitalWrite(BACKWARDS_ASS_ONBOARD_LED, LOW);
    delay(blink_time);
    digitalWrite(BACKWARDS_ASS_ONBOARD_LED, HIGH);
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
  pinMode(BACKWARDS_ASS_ONBOARD_LED, OUTPUT);

  // FIXME - this is just to give you time to connect a serial monitor
  count_down(6);

  delay(2000);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("");
  Serial.print("HIGH is ");
  Serial.print(HIGH);
  Serial.println("");
  Serial.print("LOW is ");
  Serial.print(LOW);


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

  server.begin();
}

void loop()
{

  WiFiClient client = server.available(); // listen for incoming clients

  if (client)
  {                                // if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        if (c == '\n')
        { // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else
          { // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H"))
        {
          digitalWrite(BACKWARDS_ASS_ONBOARD_LED, LOW); // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(BACKWARDS_ASS_ONBOARD_LED, HIGH); // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
