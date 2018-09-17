void setup(){
pinMode( A0,INPUT_PULLUP ); // 入力プルアップ抵抗付加
pinMode( A1,INPUT_PULLUP ); // 入力プルアップ抵抗付加
pinMode( A2,INPUT_PULLUP ); // 入力プルアップ抵抗付加
pinMode( 7,OUTPUT );
pinMode( 8,OUTPUT );
pinMode( 9,OUTPUT );
digitalWrite( 7, 0 );
digitalWrite( 8, 0 );
digitalWrite( 9, 0);

}
void loop() {
  long int i;
  
  if (!digitalRead(A0)) {
    delay(100);while(!digitalRead(A0));
 /*   delay(100);while(!digitalRead(A0));
    
    for (i=1;i<=100;i++) {
      digitalWrite( 8, 1);
      digitalWrite( 9, 0);
      delay(2);
      digitalWrite( 8, 1);
      digitalWrite( 9, 1);
      delay(2);
    };
 */

    for (i=1;i<=200;i++) {
      digitalWrite( 8, 1);
      digitalWrite( 9, 0);
      delayMicroseconds(100);
      digitalWrite( 8, 1);
      digitalWrite( 9, 1);
      delayMicroseconds(100);
    };

  };

  
  if (!digitalRead(A1)) {
    digitalWrite( 8, 1);
    digitalWrite( 9, 0);
    delay(2);
    digitalWrite( 8, 1);
    digitalWrite( 9, 1);
    delay(2);
  };

  if (!digitalRead(A2)) {
    digitalWrite( 8, 0);
    digitalWrite( 9, 0);
    delay(2);
    digitalWrite( 8, 0);
    digitalWrite( 9, 1);
    delay(2);
  };
  
}
