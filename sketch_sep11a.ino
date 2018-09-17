#include <LiquidCrystal.h>
 
LiquidCrystal lcd = LiquidCrystal(12,11,10,5,4,3,2);
 
void setup(){
lcd.begin(16, 2);
lcd.print("Hello Arduino");
lcd.setCursor(0,1);
lcd.print("Hello Makoto!");
}
 
void loop(){
}
