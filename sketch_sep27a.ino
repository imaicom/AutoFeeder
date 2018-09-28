#include <LiquidCrystal.h>
 
LiquidCrystal lcd = LiquidCrystal(12,11,10,5,4,3,1);

int m=0;
int k=2;
int i=0;
int j=0;
int p5=0;
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

attachInterrupt(0, counta, FALLING);  //INT0 - D2 pin
}

void loop(){
  
  if(!digitalRead(A2)) {delay(10);while(!digitalRead(A2));m=0;k=2;}
  
  if(m==0) {
    lcd.begin(16, 2);
    lcd.print(" Fwd    Back");
    lcd.setCursor(0,1);
    lcd.print(" Feed   +0.5");
    lcd.blink();
    m=1;
  };  
  
  if(m==1) {
    if(k==2)lcd.setCursor(0,0);
    if(k==3)lcd.setCursor(7,0);
    if(k==4)lcd.setCursor(0,1);  
    if(k==5)lcd.setCursor(7,1);
    if(!digitalRead(A3)) {delay(10);while(!digitalRead(A3));m=k;}
  };
  
  if(m==2) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" Fwd        ");
    lcd.setCursor(0,1);
    lcd.print("            ");
    m=22;
  };
  
  if(m==22) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" Fwd        ");
    lcd.setCursor(0,1);
    lcd.print("            ");
    do {
      
    } while(digitalRead(A2)); // menu
    m=0;
  };

  if(m==3) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" Back       ");
    lcd.setCursor(0,1);
    lcd.print("            ");
    m=33;
  };
  
  if(m==33) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" Back       ");
    lcd.setCursor(0,1);
    lcd.print("            ");
    do {
      
    } while(digitalRead(A2)); // menu
    m=0;
  };
  
  if(m==4) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" Feed       ");
    lcd.setCursor(0,1);
    lcd.print("            ");
    m=44;
  };
  
  if(m==44) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" Feed       ");
    lcd.setCursor(0,1);
    lcd.print("            ");
    do {
      
    } while(digitalRead(A2)); // menu
    m=0;
  };

  if(m==5) {
    lcd.begin(16, 2);
    lcd.print(" +0.5       ");
    lcd.setCursor(0,1);
    lcd.print("            ");
    m=55;
  };
  
  if(m==55) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" +0.5       ");
    lcd.setCursor(1,1);
    lcd.print(p5);
    do {
      if(!digitalRead(A3)) {delay(10);while(!digitalRead(A3));
        p5+=5;if(p5>5)p5=0;
        lcd.setCursor(1,1);lcd.print(p5);
      };
    } while(digitalRead(A2)); // menu
    m=0;
  };
  
}

void counta() {

  if(m==1) {
    delay(1);
    if(!digitalRead(A5)) {k++;}else{k--;};
    if(k<2)k=5;
    if(k>5)k=2;
  };

  if(m==44) {
    delay(1);
    if(!digitalRead(A5)) {i=i+(30-j);}else{i=i-(30-j);};
    if(i<-1400)i=-1400;
    if(i>1400)i=1400;
    j=0;
  };
  
} //counta()
