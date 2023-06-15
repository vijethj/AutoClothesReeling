#include <Wire.h>
 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.begin(); 
  lcd.backlight();
  
  lcd.setCursor(0,0);
  
  lcd.print("Hello world!");

  lcd.setCursor(0,1);
    
  lcd.print("TechnoEsolution");

}


void loop()
{
}
