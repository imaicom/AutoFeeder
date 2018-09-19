#include <LiquidCrystal.h>
 
LiquidCrystal lcd = LiquidCrystal(12,11,10,5,4,3,2);

int i=0;

void setup(){
pinMode( A0,INPUT_PULLUP ); // 入力プルアップ抵抗付加
pinMode( A1,INPUT_PULLUP ); // 入力プルアップ抵抗付加
pinMode( A2,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
pinMode( A3,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
pinMode( A4,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
pinMode( A5,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
lcd.begin(16, 2);
lcd.print("Hello Arduino");
lcd.setCursor(0,1);
lcd.print("Hello Makoto!");
}
 
void loop(){
  char buf[30];
  if(!digitalRead(A3)){
    delay(10);
    while(!digitalRead(A3));
    i++;
    lcd.setCursor(0,1);
    sprintf(buf,"%04d",i);
    lcd.print(buf);
  };
  if(!digitalRead(A4)){
    delay(1);while(!digitalRead(A4));
    i++;
    lcd.setCursor(0,1);
    sprintf(buf,"%04d",i);
    lcd.print(buf);
  };
}
