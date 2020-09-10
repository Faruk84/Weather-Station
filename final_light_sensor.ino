#include <Wire.h> //BH1750 IIC Mode 
#include <math.h> 
int BME280address = 0x76; //setting i2c address
byte buff[2];
void setup()
{
 Wire.begin();
 Serial.begin(57600);//init Serail band rate 
}

void loop()
{
 int i;
 uint16_t val=0;
 BME280_Init(BME280address);
 delay(200);

 if(2==BME280_Read(BME280address))
 {
   val=((buff[0]<<8)|buff[1])/1.2;
   Serial.print(val,DEC);      
 }
 delay(150);
}

int BME280_Read(int address) //
{
 int i=0;
 Wire.beginTransmission(address);
 Wire.requestFrom(address, 2);
 while(Wire.available()) //
 {
   buff[i] = Wire.read();  // receive one byte
   i++;
 }
 Wire.endTransmission();  
 return i;
}

void BME280_Init(int address) 
{
 Wire.beginTransmission(address);
 Wire.write(0x10);//1lx reolution 120ms
 Wire.endTransmission();
}
