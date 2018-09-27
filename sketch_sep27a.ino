#include <LiquidCrystal.h>
 
LiquidCrystal lcd = LiquidCrystal(12,11,10,5,4,3,1);

int i=0;
int j=0;
int z,zz;
int old_i=0;
float za;
volatile int state = LOW;


void setup(){
pinMode( A0,INPUT_PULLUP );
pinMode( A1,INPUT_PULLUP );
pinMode( A2,INPUT_PULLUP );  
pinMode( A3,INPUT_PULLUP );  
pinMode(  2,INPUT_PULLUP );  
pinMode( A5,INPUT_PULLUP );  

pinMode( 7,OUTPUT );
pinMode( 8,OUTPUT );
pinMode( 9,OUTPUT );
digitalWrite( 7, 0 );
digitalWrite( 8, 0 );
digitalWrite( 9, 0);

lcd.begin(16, 2);
lcd.print(" Fwd    Back");
lcd.setCursor(0,1);
lcd.print(" Feed   +0.5");
//lcd.cursor();
lcd.blink();
attachInterrupt(0, counta, FALLING);  //INT0 - D2 pin
}

void loop(){
  lcd.setCursor(0,0);
  delay(1000);

  lcd.setCursor(7,0);
  delay(1000);

  lcd.setCursor(0,1);
  delay(1000);
  
  lcd.setCursor(7,1);
  delay(1000);
}

void counta() {

  delay(1);
  if(!digitalRead(A5)) {i=i+(30-j);}else{i=i-(30-j);};
  if(i<-1400)i=-1400;
  if(i>1400)i=1400;
  j=0;

} //counta()
