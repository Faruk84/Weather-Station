#include <DHT.h>;
#include <SFE_BMP180.h>
#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <math.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define PS_MINX 204
#define PS_MINY 195
#define PS_MAXX 948
#define PS_MAXY 910

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF




#define ALTITUDE 36

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

DHT dht(A14, DHT22);
SFE_BMP180 pressure;

int rain;
int trigpin=24;
int echopin=26;
int relaypin=28;

float x;
long duration;
float height;
float realheight;

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
   
  tft.reset();
  //tft.begin(0x9325);
  //tft.setRotation(1);
  
  tft.fillScreen(BLACK);
  
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(relaypin, OUTPUT);
  dht.begin();
  Wire.begin();
  pressure.begin();
  attachInterrupt(14, rpm_fun, RISING);
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
  rain=analogRead(A15);
  if(rain>=1000)
  {
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);

    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin,LOW);
    duration=pulseIn(echopin,HIGH);
    height=duration*0.34/2;
    realheight=125-height;
    x=0.205*realheight;
    Serial.print(height);
    Serial.print("Rainfall: ");
    Serial.print(x-9);
    Serial.print("mm");
    tft.print("Rainfall:");
    Serial.print("\n");
    if(x>=10)
      digitalWrite(4,HIGH);
    else 
      digitalWrite(4,LOW);
    }
    else
    {
      Serial.print("It is raining");
      tft.print("It is raining");
    }
  }
  tft.begin(0x9325);
  tft.setRotation(1);
  tft.setCursor(0,80);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);


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
  co_value = analogRead(A8);
  air_quality_Value=analogRead(A9);//air quality check sensor value read;
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
  
  LM_val1 = analogRead(A10);
  LM_val2 = analogRead(A11);
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
  int sensorValue1=analogRead(A12);
 int sensorValue2=analogRead(A13);
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
 tft.print("provided altitude: ");
 tft.print(ALTITUDE,0);
 tft.print("\n");
 tft.print("temp_bmp180: ");
 tft.print(T,2);
 tft.print(" deg C, ");
 tft.print("\n");
 tft.print("absolute pressure: ");
 tft.print(P,2);
 tft.print(" mb ");
 tft.print("\n");
 tft.print("computed altitude:");
 tft.print(a,0);
 tft.print(" meters,");
 tft.print("\n");
 tft.print("HYDROCARBON QUANTITY=");//air quality check sensor value;
 tft.print(air_quality_Value);
 tft.print("\n");
 tft.print("CO QUANTITY=");
 tft.print(co_value);
 tft.print("\n");
 tft.print("VOLUME=");
 tft.print(co_value);
 tft.print("\n");
 tft.print("Humidity: ");
 tft.print(hum);
 tft.print("\n");
 tft.print("Temp_dht: ");
 tft.print(temp);
 tft.print(" Celsius");
 tft.print("\n");
 tft.print("Soil1_Temp = ");
 float mv1 = (LM_val1/1024.0)*5000;
 float cel1 = mv1/10;
 tft.print(cel1);
 tft.print(" deg C");
 tft.print("\n");
 //tft.print();
 float mv2 = (LM_val2/1024.0)*5000;
 float cel2 = mv2/10;
 tft.print("Soil2_Temp = ");
 tft.print(cel2);
 tft.print(" deg C");
 tft.print("\n");
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
  
 tft.print("Light Intensity:");
 tft.print(val,DEC);
 tft.print("[lx]");
 }
 tft.println();
 if(sensorValue1>=820)
  tft.print("Soil 1:very low moist");
 else if(sensorValue1>=615 && sensorValue1<820)
  tft.print("Soil 1:low moist");
 else if(sensorValue1>=410 && sensorValue1<615)
  tft.print("Soil 1:moderate moist"); 
 else if(sensorValue1>=250 && sensorValue1<410)
  tft.print("Soil 1:highly moist");
 else
  tft.print("Soil 1 :very highly Moist");
  tft.print("\n");
 if(sensorValue2>=820)
  tft.print("Soil 2 :very low moist");
 else if(sensorValue2>=615 && sensorValue2<820)
  tft.print("Soil 2 :low moist");
 else if(sensorValue2>=410 && sensorValue2<615)
  tft.print("Soil 2 :moderate moist"); 
 else if(sensorValue2>=250 && sensorValue2<410)
  tft.print("Soil 2 :highly moist");
 else
  tft.print("Soil 2 :very highly Moist");
 tft.print("\n");
 delay(25000);  
 
 
 
}
}



