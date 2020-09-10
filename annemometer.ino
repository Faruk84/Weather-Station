volatile byte half_revolution;
unsigned int rpm;
unsigned long timeold;
float v;
void setup()
{ 
  Serial.begin(9600);
  attachInterrupt(0, rpm_fun, RISING);
  half_revolution = 0;
  rpm = 0;
  timeold = 0;
}
void loop()
{ 
  if (half_revolution >= 20){
    rpm = 30*1000/(millis() - timeold)*half_revolution;
    v=(0.15*rpm*60)/1000;
    timeold = millis();
    half_revolution = 0;
  }
}
void rpm_fun()
{
  half_revolution++;
  Serial.print("wind speed=");
  Serial.print(v);
  Serial.print("\n");
  
}

