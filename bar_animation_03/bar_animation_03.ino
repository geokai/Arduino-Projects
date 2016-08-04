/*
 LiquidCrystal Library - Elapsed Time

Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
library works with all LCD displays that are compatible with the 
Hitachi HD44780 driver. There are many of them out there, and you
can usually tell them by the 16-pin interface.

This sketch prints an animated progress bar to the LCD.

Based on original Bar animation source code by Jeremy Blum (www.jeremyblum.com)

Library originally added 18 Apr 2008
by David A. Mellis
library modified 5 Jul 2009
by Limor Fried (http://www.ladyada.net)
example added 9 Jul 2009
by Tom Igoe
modified 22 Nov 2010
by Tom Igoe

This example code is in the public domain.


The circuit:
* LCD RS pin to digital pin 2:
* LCD EN pin to digital pin 3:
* LCD D4 pin to digital pin 4:
* LCD D5 pin to digital pin 5:
* LCD D6 pin to digital pin 6:
* LCD D7 pin to digital pin 7:
* LCD R/W pin to ground:
* 10K pot:
* ends to +5V and ground:
* wiper to LCD VO pin (pin 3):

*/

//Include the library:
#include <LiquidCrystal.h>

//Initialize an LCD object:
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Cheate Characters:
byte p000[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte p20[8] = {
  B00000,
  B00000,
  B00000,
  B10000,
  B00000,
  B00000,
  B00000,
};
byte p40[8] = {
  B00000,
  B00000,
  B10000,
  B11000,
  B10000,
  B00000,
  B00000,
};
byte p60[8] = {
  B00000,
  B10000,
  B11000,
  B11100,
  B11000,
  B10000,
  B00000,
};
byte p80[8] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11100,
  B11000,
  B10000,
};
byte p100[8] = {
  B11000,
  B11100,
  B11110,
  B11111,
  B11110,
  B11100,
  B11000,
};
byte p120[8] = {
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100,
};
byte p140[8] = {
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
};
byte p160[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup()
{
  //Begin the LCD interface:
  lcd.begin(16, 2);

  //Print a title to first line:
  lcd.print("JBs Progress Bar:");

  //Create Custom Characters:
  lcd.createChar(0, p000);
  lcd.createChar(1, p20);
  lcd.createChar(2, p40);
  lcd.createChar(3, p60);
  lcd.createChar(4, p80);
  lcd.createChar(5, p100);
  lcd.createChar(6, p120);
  lcd.createChar(7, p140);
  lcd.createChar(8, p160);
}

void loop()
{
  //Move the cursor:
  lcd.setCursor(0, 1);

  //Clear the line:
  lcd.print("                ");
  delay(300);

  //Loop through and make progress bar - increase:
  for (int i = 0; i < 16; i++)
   {
     for (int j = 1; j < 9; j++)
      {
       lcd.setCursor(i, 1);
       lcd.write(j);
       delay(100);
      }
   }
 {
   //Loop through and make progress bar - decrease:
   for (int k = 16; k > -1; k--)
      {
        for (int l = 7; l > -1; l--)
          {
           lcd.setCursor(k, 1);
           lcd.write(l+1);
           delay(100);
           //lcd.setCursor(k, 1);
           lcd.print(" ");
          }
      }
   }
}
