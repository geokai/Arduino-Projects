/*
  LiquidCrystal Library - Elapsed Time
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints Elapsed time in Days, Hours, Minites & Seconds to the LCD
 with leading zeros and right justified digits.
 
 eg: 
     Dy,Hr,Mn,Sc
     00:01:27:09
 
  The circuit:
 * LCD RS pin to digital pin 2:
 * LCD Enable pin to digital pin 3:
 * LCD D4 pin to digital pin 4:
 * LCD D5 pin to digital pin 5:
 * LCD D6 pin to digital pin 6:
 * LCD D7 pin to digital pin 7:
 * LCD R/W pin to ground:
 * 10K pot:
 * ends to +5V and ground:
 * wiper to LCD VO pin (pin 3):
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

  byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

void setup() {
  // optional serial monitor:
  //Serial.begin(9600);

  // create a new character
  lcd.createChar(1, smiley);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Dy,Hr,Mn,Sc");
  
  /*
  // optional smily
  lcd.setCursor(13, 0);
  lcd.write(1);          // this display doesn't like it's 0 register being used:
  */
}

// elapsed time in days, hours, minutes & seconds:

void loop() {
   unsigned long time = millis()/1000;                 // total seconds:
   unsigned long secs = time % 60;                     // seconds < 60:
   unsigned long minite = time / 60;                   // up to 59 minutes:
   unsigned long mins = minite % 60;                   // minites < 60:
   unsigned long hours = minite / 60;                  // up to 23 hours:
   unsigned long hrs = hours % 24;                     // hours < 24:
   unsigned long days = hours /24;                     // total days:

  // set the cursor to column 0, line 1:
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
  // print the number of days:
    // to justify single digits to the right with a leading zero:
   if (days < 10)
     {
       lcd.setCursor(0, 1);
       lcd.print("0");       // print a leading 0:
       lcd.setCursor(1, 1);
       lcd.print(days);      //days < 10:
       lcd.print(" ");
     } 
   else
    {
      lcd.setCursor(0, 1);
      lcd.print(days);      //days > 9:
      lcd.print(" ");
    }

     lcd.setCursor(2, 1);
     lcd.print(":");

  // print the number of hours:
    // to justify single digits to the right with a leading zero:
    if (hrs < 10)
     {
       lcd.setCursor(3, 1);
       lcd.print("0");      // print a leading 0:
       lcd.setCursor(4, 1);
       lcd.print(hrs);      //hours < 10:
       lcd.print(" ");
     } 
   else
    {
      lcd.setCursor(3, 1);
      lcd.print(hrs);      //hours > 9:
      lcd.print(" ");
    }

     lcd.setCursor(5, 1);
     lcd.print(":");

 // print the number of minites:
   // to justify single digits to the right with a leading zero:
   if (mins < 10)
     {
       lcd.setCursor(6, 1);
       lcd.print("0");       // print a leading 0:
       lcd.setCursor(7, 1);
       lcd.print(mins);      // minites < 10:
       lcd.print(" ");
     } 
   else
    {
      lcd.setCursor(6, 1);
      lcd.print(mins);      //minites > 9:
      lcd.print(" ");
    }
    
     lcd.setCursor(8, 1);
     lcd.print(":");

  // print the number of seconds:
    // to justify single digits to the right with a leading zero:
   if (secs < 10)
     {
       lcd.setCursor(9, 1);
       lcd.print("0");       // print a leading 0:
       lcd.setCursor(10, 1);
       lcd.print(secs);      //seconds < 10:
     } 
   else
    {
      lcd.setCursor(9, 1);
      lcd.print(secs);      //seconds > 9:
      lcd.print(" ");
    }
    
    /*
     lcd.setCursor(8, 1);
     lcd.print(":");
    */
}

