#include <LiquidCrystal.h>
 
LiquidCrystal lcd = LiquidCrystal(12,11,10,5,4,3,1);

int i=0;
int j=0;
volatile int state = LOW;


void setup(){
pinMode( A0,INPUT_PULLUP ); // 入力プルアップ抵抗付加
pinMode( A1,INPUT_PULLUP ); // 入力プルアップ抵抗付加
pinMode( A2,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
pinMode( A3,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
pinMode(  2,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
pinMode( A5,INPUT_PULLUP ); // 入力プルアップ抵抗付加  
lcd.begin(16, 2);
lcd.print("Hello Arduino");
lcd.setCursor(0,1);
lcd.print("             ");
attachInterrupt(0, counta, FALLING);  //INT0 - D2 pin

}
 
void loop(){
  
  char buf[30];
  if(!digitalRead(A2)){
    delay(10);
    while(!digitalRead(A2));
    i=0;
    j=0;
    lcd.setCursor(0,1);
    sprintf(buf,"%04d",i);
    lcd.print(buf);
  };

  j++;if(j>29)j=29;
  
  lcd.setCursor(0,0);
  sprintf(buf,"%04d",j);
  lcd.print(buf);
    
  lcd.setCursor(0,1);
  sprintf(buf,"%04d",i);
  lcd.print(buf);
    
} //loop()

void counta() {

  delay(1);
  if(!digitalRead(A5)) {i=i+(30-j);}else{i=i-(30-j);};
  if(i<0)i=0;
  if(i>1400)i=1400;
  j=0;

} //counta()
