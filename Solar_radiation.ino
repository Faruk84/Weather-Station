#include <Wire.h>

int val11;
float val2;


void setup() {
 
  Serial.begin(9600);
}
 
void loop() {
 {
      float temp;
      val11=analogRead(A1);
      temp=val11/4.092;
      val2=((temp/10)+0.7);
      //Serial.print("Voltage: ");
      //Serial.println(val2);
      //Serial.println("V");
      //Serial.print("\n");
     
  float average = 0;
  for(int i = 0; i < 1000; i++) {
    average = average + (.0264 * analogRead(A0) -13.51)/ 1000;
  
  //5A mode(.0264 * analogRead(A0) -13.51)
  // 20A or 30A mode, need to modify this formula to 
    //(.19 * analogRead(A0) -25) for 20A mode and 
    //(.044 * analogRead(A0) -3.78) for 30A mode
  
    delay(1);
  }
  //Serial.print(average);
  //Serial.print("A");
  //Serial.print("\n");  
float solar_radiation = ((val2*average)/0.0296);
Serial.print("Solar radiation =");
Serial.print(solar_radiation);
Serial.print("\n");
}
}

