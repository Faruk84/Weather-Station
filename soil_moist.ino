void setup() {
  Serial.begin(9600);

}

void loop() {
 int sensorValue1=analogRead(A0);
 int sensorValue2=analogRead(A1);
 if(sensorValue1>=820)
  Serial.print("Soil Sample 1 :very low moist");
 else if(sensorValue1>=615 && sensorValue1<820)
  Serial.print("Soil Sample 1 :low moist");
 else if(sensorValue1>=410 && sensorValue1<615)
  Serial.print("Soil Sample 1 :moderate moist"); 
 else if(sensorValue1>=250 && sensorValue1<410)
  Serial.print("Soil Sample 1 :highly moist");
 else
   Serial.print("Soil Sample 1 : very highly Moist");
 Serial.print("\n");      
// Serial.print("\nSensor value of sample 1=");  
 //Serial.println(sensorValue1);
 
 if(sensorValue2>=820)
  Serial.print("Soil Sample 2 :very low moist");
 else if(sensorValue2>=615 && sensorValue2<820)
  Serial.print("Soil Sample 2 :low moist");
 else if(sensorValue2>=410 && sensorValue2<615)
  Serial.print("Soil Sample 2 :moderate moist"); 
 else if(sensorValue2>=250 && sensorValue2<410)
  Serial.print("Soil Sample 2 :highly moist");
 else
  Serial.print("Soil Sample 2 :very highly Moist");
 Serial.print("\n");      
 //Serial.print("\nSensor value of sample 2=");  
 //Serial.println(sensorValue2);
 
 delay(10000);
 

}
