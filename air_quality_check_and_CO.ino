const int coAOUTpin = A0;
const int coDOUTpin = 8;
const int ledpin = 13;

int value;
int limit;
int sensorValue;
float vol;

void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);

  

}

void loop() {
 
  value = analogRead(coAOUTpin);
  
 
  sensorValue=analogRead(A2);//air quality check sensor value read;
  //vol=(float)sensorValue/1024*5,0;
  //Serial.print("PPM=");//air quality check sensor value;
  //Serial.println(vol,1);
  Serial.print(sensorValue);
  Serial.print(",");
  //Serial.print("CO value= ");//CO sensor value;
  Serial.println(value);

 delay(1000);

}
