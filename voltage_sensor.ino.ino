#include <Wire.h>
int val11;
float val2;


void setup()
{
  Serial.begin(9600); 
}
void loop()
{
      float temp;
      val11=analogRead(A1);
      temp=val11/4.092;
      val2=((temp/10)+0.7);
      Serial.print("Voltage: ");
      Serial.print(val2);
      Serial.print("V");
      Serial.print("\n");
     
   delay(1000);
}
