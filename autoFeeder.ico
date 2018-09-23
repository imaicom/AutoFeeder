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
lcd.print("Auto Feeder");
lcd.setCursor(0,1);
lcd.print("             ");
attachInterrupt(0, counta, FALLING);  //INT0 - D2 pin
}

void loop(){
  
  char buf[30];

  if(!digitalRead(A3)){
    delay(10);
    while(!digitalRead(A3));
    hi_beep();delay(500);
    hi_beep();delay(500);
    z=int(float(float(abs(i))/0.1727825));
    if(i>0) {
      for (zz=1;zz<=z;zz++) {
        digitalWrite( 8, 1);
        digitalWrite( 9, 0);
        delay(2);
        digitalWrite( 8, 1);
        digitalWrite( 9, 1);
        delay(2);
        if(!digitalRead(A3)) break;    
      };
    }else{
      for (zz=1;zz<=z;zz++) {
        digitalWrite( 8, 0);
        digitalWrite( 9, 0);
        delay(2);
        digitalWrite( 8, 0);
        digitalWrite( 9, 1);
        delay(2);
        if(!digitalRead(A3)) break;    
       };
    };
    while(!digitalRead(A3));
  };
  

 
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
  
//  lcd.setCursor(0,0);
//  sprintf(buf,"%04d",j);
//  lcd.print(buf);
    
  lcd.setCursor(0,1);
  sprintf(buf,"%4d mm",i);
  lcd.print(buf);
  if(old_i!=i) beep();
  old_i=i;
    
} //loop()


void counta() {

  delay(1);
  if(!digitalRead(A5)) {i=i+(30-j);}else{i=i-(30-j);};
  if(i<-1400)i=-1400;
  if(i>1400)i=1400;
  j=0;

} //counta()

void beep() {
  int ii;
  for (ii=1;ii<=200;ii++) {
    digitalWrite( 8, 1);
    digitalWrite( 9, 0);
    delayMicroseconds(100);
    digitalWrite( 8, 1);
    digitalWrite( 9, 1);
    delayMicroseconds(100);
  };
}

void hi_beep() {
  int ii;
  for (ii=1;ii<=100;ii++) {
    digitalWrite( 8, 1);
    digitalWrite( 9, 0);
    delayMicroseconds(200);
    digitalWrite( 8, 1);
    digitalWrite( 9, 1);
    delayMicroseconds(200);
  };
}
