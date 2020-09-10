#include <DHT.h>;
#include <SFE_BMP180.h>
#include <Wire.h>
#include <math.h>

#define ALTITUDE 36

DHT dht(A2, DHT22);
SFE_BMP180 pressure;

int BME280address = 0x76; //setting i2c address
byte buff[2];
int co_value;
int limit;
int air_quality_Value;
float measure_vol;
volatile byte half_revolution;
unsigned int rpm;
unsigned long timeold;
float v;
int chk;
float hum;  
float temp;
char status;
double T,P,p0,a;
int LM_val1;
int LM_val2;

void setup() 
{
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
  pressure.begin();
  attachInterrupt(0, rpm_fun, RISING);
  half_revolution = 0;
  rpm = 0;
  timeold = 0;
  
}
void BME280_Init(int address) 
{
 Wire.beginTransmission(address);
 Wire.write(0x10);//1lx reolution 120ms
 Wire.endTransmission();
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

void rpm_fun()
{
  half_revolution++;
  Serial.print("wind speed=");
  Serial.print(v);
  Serial.print("\n");
  
}

void loop() 
{
  
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

 

{
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");
  
  status = pressure.startTemperature();
  if (status != 0)
  {
        delay(status);
        status = pressure.getTemperature(T);
        if (status != 0)
        {
          Serial.print("temperature_bmp180: ");
          Serial.print(T,2);
          Serial.print(" deg C, ");
          status = pressure.startPressure(3);
          if (status != 0)
            {
              delay(status);
              status = pressure.getPressure(P,T);
                if (status != 0)
                  {
                    Serial.print("absolute pressure: ");
                    Serial.print(P,2);
                    Serial.print(" mb, ");  
                    a = pressure.altitude(P,p0);
                    Serial.print("computed altitude: ");
                    Serial.print(a,0);
                    Serial.print(" meters, ");
                   }
                else Serial.println("error retrieving pressure measurement\n");
           }
          else Serial.println("error starting pressure measurement\n");
        }
        else Serial.println("error retrieving temperature measurement\n");
    }
  else Serial.println("error starting temperature measurement\n");

}
{
  co_value = analogRead(A0);
  air_quality_Value=analogRead(A1);//air quality check sensor value read;
  measure_vol=(float)air_quality_Value/1024*5,0;
  Serial.print("HYDROCARBON QUANTITY=");//air quality check sensor value;
  Serial.print(air_quality_Value);
  Serial.print("\n");
  Serial.print("CO QUANTITY=");
  Serial.print(co_value);
  Serial.print("\n");
  Serial.print("VOLUME=");
  Serial.print(co_value);
  
}
{
  if (half_revolution >= 20)
  {
    rpm = 30*1000/(millis() - timeold)*half_revolution;
    v=(0.15*rpm*60)/1000;
    timeold = millis();
    half_revolution = 0;
  }
}
{
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp_dht: ");
  Serial.print(temp);
  Serial.println(" Celsius");
 }
 {
  LM_val1 = analogRead(A3);
  LM_val2 = analogRead(A4);
  float mv1 = (LM_val1/1024.0)*5000;
  float mv2 = (LM_val2/1024.0)*5000; 
  float cel1 = mv1/10;
  float cel2 = mv2/10;
  Serial.print("SOIL_TEMPRATURE_sample1 = ");
  Serial.print(cel1);
  Serial.print("*C");
  Serial.println();
  Serial.print("SOIL_TEMPRATURE_sample2 = ");
  Serial.print(cel2);
  Serial.print("*C");
  Serial.println();
}
{
  int sensorValue1=analogRead(A5);
 int sensorValue2=analogRead(A6);
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
 
}
}



