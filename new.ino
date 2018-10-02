#include <math.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd = LiquidCrystal(12, 11, 10, 5, 4, 3, 1);

int m = 0;             // Menu transition
int k = 4;             // Item selection( Feed )
int before_k = 2;
int i = 0;             // Encoder count
int before_i = 0;
int j = 0;             // Acceleration encoder count
int p1 = 0;            // Decimal 1 digit setting
int before_p1 = 0;
int skip_p1 = 0;       // Return 1 decimal place setting
int erase_setting = 0;


void setup() {
  pinMode( A2, INPUT_PULLUP ); // Menu button
  pinMode( A3, INPUT_PULLUP ); // Encoder button
  pinMode(  2, INPUT_PULLUP ); // Encoder count
  pinMode( A5, INPUT_PULLUP ); // Rotational direction of encoder

  pinMode( 8, OUTPUT ); // Motor rotation direction
  pinMode( 9, OUTPUT ); // Motor rotation pulse
  digitalWrite( 8, 0 );
  digitalWrite( 9, 0);

  attachInterrupt(0, counta, FALLING);  //INT0 - D2 pin
}


void loop() {


  char buf[30];
  int z, zz;


  if (m != 1) {

    if (!digitalRead(A2)) {
      delay(10);
      while (!digitalRead(A2));
      m = 0;
      k = 4;
    };

  }; // if (m != 1)


  if (m == 0) {

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(" Feed   ");
    sprintf(buf,"%+1d",p1);
    lcd.print(buf);
    lcd.print(" cnt");
    lcd.setCursor(0, 1);
    lcd.print(" Fwd    Back");
    lcd.blink();
    m = 1;

  }; // if (m == 0)


  if (m == 1) {

    if (k == 2)lcd.setCursor(1, 1);
    if (k == 3)lcd.setCursor(8, 1);
    if (k == 4)lcd.setCursor(1, 0);
    if (k == 5)lcd.setCursor(8, 0);
    if (!digitalRead(A3)) {
      delay(10);
      while (!digitalRead(A3));
      m = k;
    }

    if (before_k != k) beep();
    before_k = k;

    if (!digitalRead(A2)) {
      erase_setting++;
      delay(1);

      if (erase_setting > 1000) { // Press and hold for 1 second or longer
        lcd.begin(16, 2);
        lcd.setCursor(0, 0);
        lcd.print(" Erase       ");
        lcd.setCursor(0, 1);
        lcd.print(" all settings");
        hi_beep(); 
        delay(100);
        hi_beep(); 
        delay(100);
        hi_beep(); 
        delay(100);
        m = 0;
        k = 4;
        p1 = 0;
        i = 0;
      };

    } 
    else erase_setting = 0;

  }; // if (m == 1)


  if (m == 2) {

    hi_beep();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(" Fwd        ");
    lcd.setCursor(0, 1);
    lcd.print("            ");
    m = 22;

  }; // if (m == 2)


  if (m == 22) {

    delay(10);
    do {
      if (!digitalRead(A3)) {
        digitalWrite( 8, 1);
        digitalWrite( 9, 0);
        delay(2);
        digitalWrite( 8, 1);
        digitalWrite( 9, 1);
        delay(2);
      }
    } 
    while (digitalRead(A2)); // menu

    m = 0;

  }; // if (m == 22)


  if (m == 3) {

    hi_beep();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("             ");
    lcd.setCursor(0, 1);
    lcd.print("        Back ");

    m = 33;

  }; // if (m == 3)


  if (m == 33) {

    delay(10);
    do {
      if (!digitalRead(A3)) {
        digitalWrite( 8, 0);
        digitalWrite( 9, 0);
        delay(2);
        digitalWrite( 8, 0);
        digitalWrite( 9, 1);
        delay(2);
      }
    } 
    while (digitalRead(A2)); // menu

    m = 0;

  }; // if (m == 33)


  if (m == 4) {

    hi_beep();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(" Feed       ");
    lcd.setCursor(0, 1);
    lcd.print("            ");
    m = 44;

  }; // if (m == 4)


  if (m == 44) {

    delay(10);
    do {
      if (!digitalRead(A3)) {
        delay(10);
        while (!digitalRead(A3));
        hi_beep(); 
        delay(500);
        hi_beep(); 
        delay(500);

        if (i > 0) {  // Feed forward + Consider the blade thickness

          if (i >= 2) z = int((float)i/(98.63/100.0*11.0 * M_PI / 360.0 * 1.8));
          else        z = int((float)i/(98.63/100.0*11.0 * M_PI / 360.0 * 1.8));
          z=z+p1;
          lcd.setCursor(12, 0);
          sprintf(buf, "%4d", z);
          lcd.print(buf);
          digitalWrite( 8, 1);
          for (zz = 1; zz <= z; zz++) { 
            digitalWrite( 9, 0);
            delay(3);
            digitalWrite( 9, 1);
            delay(3);
            if (!digitalRead(A2)) break; // Emergency stop
            if (!digitalRead(A3)) break; // Emergency stop
          };

        } 
        else if(i < 0){ // Negative feed

          z = int((float)(-i) / (98.63/100.0*11.0 * M_PI / 360.0 * 1.8))+p1;
          z=z+p1;
          lcd.setCursor(12, 0);
          sprintf(buf, "%4d", z);
          lcd.print(buf);
          digitalWrite( 8, 0);
          for (zz = -1; zz <= z; zz++) {
            digitalWrite( 9, 0);
            delay(3);
            digitalWrite( 9, 1);
            delay(3);
            if (!digitalRead(A2)) break; // Emergency stop
            if (!digitalRead(A3)) break; // Emergency stop
          };
          if (!digitalRead(A2)) break;

        };
        while (!digitalRead(A3));
      };

      lcd.setCursor(0, 1);
      if (i >= 2) sprintf(buf, "%4d+1.5mm %+1dcnt  ", i, p1);
      else     sprintf(buf, "%4dmm %+1dcnt    ", i, p1);
      lcd.print(buf);

      j++; 
      if (j > 29) j = 29; // Acceleration processing of encoder
      if (before_i != i) beep();
      before_i = i;

    } 
    while (digitalRead(A2)); // menu

    m = 0;
    before_k = 0;

  }; // if (m == 44)


  if (m == 5) {

    hi_beep();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("            ");
    skip_p1 = p1;
    m = 55;

  }; // if (m == 5)


  if (m == 55) {

    delay(10);
    do {

      lcd.setCursor(8, 0);
      sprintf(buf,"%+1d cnt",p1); 
      lcd.print(buf);
      if (!digitalRead(A3)) {
        delay(10);
        while (!digitalRead(A3));
        hi_beep(); 
        k = 4;
        break;
      }
    } 
    while (digitalRead(A2)); // menu
    if (!digitalRead(A2)) p1 = skip_p1;

    m = 0;

  }; // if (m == 55)


} // void loop()


void counta() {


  if (m == 1) {
    delay(1);
    if (!digitalRead(A5)) {
      k++;
    } 
    else {
      k--;
    };
    if (k < 2) k = 5;
    if (k > 5) k = 2;
  };


  if (m == 44) {
    delay(1);
    if (!digitalRead(A5)) {
      if (j < 27) i = ((i + (30 - j)) / 10 * 10); 
      else if (j >= 27) i++;
    } 
    else {
      if (j < 27) i = ((i - (30 - j)) / 10 * 10); 
      else if (j >= 27) i--;
    };
    if (i < -1400) i = -1400;
    if (i > 1400) i = 1400;
    j = 0;
  };


  if (m == 55) {
    delay(1);
    if (!digitalRead(A5)) {
      p1++;
    } 
    else {
      p1--;
    };
    if (p1 < -4) p1 = -4;
    if (p1 > +4) p1 = +4;
    if (before_p1 != p1) beep();
    before_p1 = p1;
  };


} // counta()


void beep() {

  int i;
  for (i = 1; i <= 200; i++) {
    //    digitalWrite( 8, 1);
    //    digitalWrite( 9, 0);
    delayMicroseconds(100);
    //    digitalWrite( 8, 1);
    //    digitalWrite( 9, 1);
    delayMicroseconds(100);
  };

}


void hi_beep() {

  int i;
  for (i = 1; i <= 100; i++) {
    //    digitalWrite( 8, 1);
    //    digitalWrite( 9, 0);
    delayMicroseconds(200);
    //    digitalWrite( 8, 1);
    //    digitalWrite( 9, 1);
    delayMicroseconds(200);
  };

}
