

// include the library code:
#include <LiquidCrystal.h>

// custom stuff.
byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {

  // set up special characters
  lcd.createChar(0, smiley);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.write("abcdefghijklmnopqrstuvwxyz");
  lcd.home();
  lcd.write("123");
  lcd.setCursor(0, 1);
  lcd.print("73%");
  lcd.write(byte(0)); 
  lcd.print(byte(0)); 


/*
  delay(2000);
  lcd.noDisplay();
  delay(2000);
  lcd.display();
  lcd.clear();
  lcd.write(byte(0)); 
*/

}

void loop() {


}


/*
 *  chamber 1
 *    humidity
 *      history
 *      settings
 *    temperature
 *    oxygen
 *  
 *   [xxxxxxxxxxxxxxxx] 
 *   [[C1] C2 C3 C4   ] 
 *   [C1 [C2] C3 C4   ] 
 *   [C1 C2 [C3] C4   ] 
 *   [84" 72% 
 */



void display() {

}



/* NOTES

The docs can be found here:
https://www.arduino.cc/en/Reference/LiquidCrystal


POSITIONING THE CURSOR
  lcd.clear()  // clears the display and positions cursor at top left.
  lcd.home()   // send cursor to top left.
  lcd.setCursor(col, row)  // zero indexed, of course.


PRINTING STUFF
  lcd.write("abc")  // writes text or other data to that spot.
  lcd.print("abc")  // only works with text.

CUSTOM CHARACTERS
  you can only have 8 custom characters, with indexes 0-7
  byte smiley[8] = {
    B00000,
    B10001,
    B00000,
    B00000,
    B10001,
    B01110,
    B00000,
  };
  lcd.createChar(0, smiley);
  lcd.write(byte(0)); 


SCROLLING THE DISPLAY
  lcd.scrollDisplayLeft()    // one character left
  lcd.scrollDisplayRight()   // one character right


DISPLAYING THE CURSOR
  a blinking square cursor
    lcd.blink()
    lcd.noBlink()
  a non-blinking underine cursor
    lcd.cursor()
    lcd.noCursor()


*/
