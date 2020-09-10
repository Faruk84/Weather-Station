#include <Servo.h>

int right = 9;
int left = 10;

Servo servo1, servo2;
int a , b , c, d, e, f;

void setup() {

  Serial.begin(9600);

}

void loop() {
  a = analogRead(A1);
  b = analogRead(A0);
  e = analogRead(A2);
  f = analogRead(A3);
  servo1.attach(5);
  servo2.attach(6);
  c = a - b;
  if (a > b)
  {
    c = map(c, 0, 1023, 120, 0);
    d = map(c, 0, 1023, 0, 120);
    //digitalWrite(3,HIGH);
    //digitalWrite(4,LOW);
  }
  else if (a < b)
  {
    c = 0 - c;
    c = map(c, 0, 1023, 0, 120);
    d = map(c, 0, 1023, 120, 0);
    //digitalWrite(3,LOW);
    //digitalWrite(4,HIGH);
  }
  else {
    servo1.detach();
    servo2.detach();
    //digitalWrite(3,LOW);
    //digitalWrite(4,LOW);
  }

  if (e > f)
  {
    //c=map(c,0,1023,0,120);
    //d=map(c,0,1023,120,0);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    delay(2000);
  }
  else if (e < f)
  {
    //c=0-c;
    //c=map(c,0,1023,120,0);
    //d=map(c,0,1023,0,120);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    delay(2000);
  }
  else {
    //servo1.detach();
    //servo2.detach();
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
  Serial.print("a=");
  Serial.print(a);
  Serial.print("b=");
  Serial.print(b);
  Serial.print("e=");
  Serial.print(e);
  Serial.print("f=");
  Serial.print(f);

  Serial.print("\n");
  servo1.write(c);
  servo2.write(d);
  delay(2000);

}
