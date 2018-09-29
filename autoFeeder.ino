#include <LiquidCrystal.h>

LiquidCrystal lcd = LiquidCrystal(12, 11, 10, 5, 4, 3, 1);

int m = 0;
int k = 4;
int kk = 2;
int i = 0;
int j = 0;
int p5 = 0;
int pp5 = 0;
int ppp5 = 0;
int z, zz;
int old_i = 0;
int clr = 0;
float za;
volatile int state = LOW;


void setup() {
  pinMode( A0, INPUT_PULLUP );
  pinMode( A1, INPUT_PULLUP );
  pinMode( A2, INPUT_PULLUP );
  pinMode( A3, INPUT_PULLUP );
  pinMode(  2, INPUT_PULLUP );
  pinMode( A5, INPUT_PULLUP );

  pinMode( 7, OUTPUT );
  pinMode( 8, OUTPUT );
  pinMode( 9, OUTPUT );
  digitalWrite( 7, 0 );
  digitalWrite( 8, 0 );
  digitalWrite( 9, 0);

  attachInterrupt(0, counta, FALLING);  //INT0 - D2 pin
}

void loop() {

  char buf[30];

  if (m != 1) {
    if (!digitalRead(A2)) {
      delay(10);
      while (!digitalRead(A2));
      m = 0;
      k = 4;
    };
  };

  if (m == 0) {
    lcd.begin(16, 2);
    lcd.setCursor(0, 1);
    lcd.print(" Fwd    Back");
    lcd.setCursor(0, 0);
    lcd.print(" Feed   +0.");
    lcd.print(p5);
    lcd.print(" mm");
    lcd.blink();
    m = 1;
  };

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
    if (kk != k) beep();
    kk = k;
    if (!digitalRead(A2)) {
      clr++;
      delay(1);
      if (clr > 1000) {
        hi_beep(); delay(100);
        hi_beep(); delay(100);
        hi_beep(); delay(100);
        p5 = 0;
        i = 0;
        m = 0;
        k = 4;
      };
    } else clr = 0;
  };


  if (m == 2) {
    hi_beep();
    lcd.begin(16, 2);
    lcd.print(" Fwd        ");
    lcd.setCursor(0, 1);
    lcd.print("            ");
    m = 22;
  };


  if (m == 22) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print("            ");
    lcd.setCursor(0, 1);
    lcd.print(" Fwd        ");
    do {

      if (!digitalRead(A3)) {
        digitalWrite( 8, 1);
        digitalWrite( 9, 0);
        delay(2);
        digitalWrite( 8, 1);
        digitalWrite( 9, 1);
        delay(2);
      }

    } while (digitalRead(A2)); // menu
    m = 0;
  };

  if (m == 3) {
    hi_beep();
    lcd.begin(16, 2);
    lcd.print("             ");
    lcd.setCursor(0, 1);
    lcd.print("        Back ");
    m = 33;
  };

  if (m == 33) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print("             ");
    lcd.setCursor(0, 1);
    lcd.print("        Back ");
    do {

      if (!digitalRead(A3)) {
        digitalWrite( 8, 0);
        digitalWrite( 9, 0);
        delay(2);
        digitalWrite( 8, 0);
        digitalWrite( 9, 1);
        delay(2);
      }

    } while (digitalRead(A2)); // menu
    m = 0;
  };

  if (m == 4) {
    hi_beep();
    lcd.begin(16, 2);
    lcd.print(" Feed       ");
    lcd.setCursor(0, 1);
    lcd.print("            ");
    m = 44;
  };

  if (m == 44) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print(" Feed       ");
    lcd.setCursor(0, 1);
    lcd.print("            ");
    do {

      if (!digitalRead(A3)) {
        delay(10);
        while (!digitalRead(A3));
        hi_beep(); delay(500);
        hi_beep(); delay(500);
        if (i > 0) {
          if (i >= 2) z = int(float((float(abs(i + 2)) + float(p5) / 10.0) / 0.1727825));
          else     z = int(float((float(abs(i  )) + float(p5) / 10.0) / 0.1727825));
          for (zz = 1; zz <= z; zz++) {
            digitalWrite( 8, 1);
            digitalWrite( 9, 0);
            delay(2);
            digitalWrite( 8, 1);
            digitalWrite( 9, 1);
            delay(2);
            if (!digitalRead(A2)) break;
            if (!digitalRead(A3)) break;
          };
        } else {
          z = int(float((float(abs(i)) + float(p5) / 10.0) / 0.1727825));
          for (zz = 1; zz <= z; zz++) {
            digitalWrite( 8, 0);
            digitalWrite( 9, 0);
            delay(2);
            digitalWrite( 8, 0);
            digitalWrite( 9, 1);
            delay(2);
            if (!digitalRead(A2)) break;
            if (!digitalRead(A3)) break;
          };
          if (!digitalRead(A2)) break;
        };
        while (!digitalRead(A3));
      };

      j++; if (j > 29) j = 29;

      lcd.setCursor(0, 1);
      if (i >= 2) sprintf(buf, "%4d.%1d mm + 2 mm", i, p5);
      else     sprintf(buf, "%4d.%1d mm       ", i, p5);
      lcd.print(buf);
      if (old_i != i) beep();
      old_i = i;

    } while (digitalRead(A2)); // menu
    m = 0;
    kk = 0;
  };

  if (m == 5) {
    hi_beep();
    lcd.begin(16, 2);
    lcd.print("        +0.");
    lcd.print(p5);
    lcd.print("       ");
    lcd.setCursor(0, 1);
    lcd.print("            ");
    m = 55;
  };

  if (m == 55) {
    delay(10);
    lcd.begin(16, 2);
    lcd.print("        +0.  mm    ");
    ppp5 = p5;
    do {

      lcd.setCursor(11, 0); lcd.print(p5);
      if (!digitalRead(A3)) {
        delay(10);
        while (!digitalRead(A3));
        hi_beep(); k = 4;
        break;
      }
    } while (digitalRead(A2)); // menu
    if (!digitalRead(A2)) p5 = ppp5;
    m = 0;
  };

}

void counta() {

  if (m == 1) {
    delay(1);
    if (!digitalRead(A5)) {
      k++;
    } else {
      k--;
    };
    if (k < 2)k = 5;
    if (k > 5)k = 2;
  };

  if (m == 44) {
    delay(1);
    if (!digitalRead(A5)) {
      i = i + (30 - j);
    } else {
      i = i - (30 - j);
    };
    if (i < -1400)i = -1400;
    if (i > 1400)i = 1400;
    j = 0;
  };

  if (m == 55) {
    delay(1);
    if (!digitalRead(A5)) {
      p5++;
    } else {
      p5--;
    };
    if (p5 < 0)p5 = 9;
    if (p5 > 9)p5 = 0;
    if (pp5 != p5) beep();
    pp5 = p5;
  };

} //counta()


void beep() {
  int ii;
  for (ii = 1; ii <= 200; ii++) {
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
  for (ii = 1; ii <= 100; ii++) {
    digitalWrite( 8, 1);
    digitalWrite( 9, 0);
    delayMicroseconds(200);
    digitalWrite( 8, 1);
    digitalWrite( 9, 1);
    delayMicroseconds(200);
  };
}
