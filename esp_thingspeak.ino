#include <stdlib.h>
#include <SoftwareSerial.h>

/*-----------------ESP8266 Serial WiFi Module---------------*/
#define RX 10                                  //TX pin of esp8266 goes to RX of Arduino
#define TX 11                                  //RX pin of esp8266 goes to TX of Arduino
#define SSID "SSID"                            // "SSID-WiFiname" 
#define PASS "PASSWORD"                        // "password"
#define IP "184.106.153.149"                   // thingspeak.com ip
String api1 = "GET /update?key=WRITE_API_KEY"; //change WRITE_API_KEY with your key of channel 1...
String api2 = "GET /update?key=WRITE_API_KEY"; //change WRITE_API_KEY with your key of channel 2...
SoftwareSerial esp8266(RX,TX);
/*-----------------------------------------------------------*/


int error;

int field1;
int field2;
int field3;
int field4;
int field5;
int field6;
int field7;
int field8;
int field9;
int field10;
int field11;
int field12;
int field13;
int field14;
int field15;
int field16;


void setup() {
  Serial.begin(9600);
  esp8266.begin(115200); //use default 115200 for esp8266.
  esp8266.println("AT");
  delay(5000);
  if(esp8266.find("OK")){
    connectWiFi();
  }
  
  // put your setup code here, to run once:

}
  
void loop() {
  start: //label 
  error=0;


  
  // put your main code here, to run repeatedly:



  updateCh1();    //Resend if transmission is not completed 
  if (error==1){
    goto start;   //go to label "start"
  }
  updateCh2();    //Resend if transmission is not completed 
  if (error==1){
    goto start;   //go to label "start"
  }
  delay(60000);   //Update every 1 minute
}



void updateCh1(){                       //For updating Channel 1
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  esp8266.println(cmd);
  delay(2000);
  if(esp8266.find("Error")){
    return;
  }
  cmd = api1 ;
  cmd += "&field1=";    //field 1 for field 1 data
  cmd += field1;
  cmd += "&field2=";    //field 2 for field 2 data
  cmd += field2;
  cmd += "&field3=";    //field 1 for field 3 data
  cmd += field3;
  cmd += "&field4=";    //field 4 for field 4 data
  cmd += field4;
  cmd += "&field5=";    //field 5 for field 5 data
  cmd += field5;
  cmd += "&field6=";    //field 6 for field 6 data
  cmd += field6;
  cmd += "&field7=";    //field 7 for field 7 data
  cmd += field7;
  cmd += "&field8=";    //field 8 for field 8 data
  cmd += field8;
  cmd += "\r\n\r\n";
  esp8266.print("AT+CIPSEND=");
  esp8266.println(cmd.length());
  if(esp8266.find(">")){
    esp8266.print(cmd);
    Serial.print("Data Uploaded in Channel 1");
  }
  else{
    esp8266.println("AT+CIPCLOSE");
    Serial.println("Error Uploading Data in Channel 1");
    }
}

void updateCh2(){                         //For updating Channel 2
  delay(3000);
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  esp8266.println(cmd);
  delay(2000);
  if(esp8266.find("Error")){
    return;
  }
  cmd = api2 ;
  cmd += "&field1=";    //field 1 for field 9 data
  cmd += field9;
  cmd += "&field2=";    //field 2 for field 10 data
  cmd += field10;
  cmd += "&field3=";    //field 3 for field 11 data
  cmd += field11;
  cmd += "&field4=";    //field 4 for field 12 data
  cmd += field12;
  cmd += "&field5=";    //field 5 for field 13 data
  cmd += field13;
  cmd += "&field6=";    //field 6 for field 14 data
  cmd += field14;
  cmd += "&field7=";    //field 7 for field 15 data
  cmd += field15;
  cmd += "&field8=";    //field 8 for field 16 data
  cmd += field16;
  cmd += "\r\n\r\n";
  esp8266.print("AT+CIPSEND=");
  esp8266.println(cmd.length());
  if(esp8266.find(">")){
    esp8266.print(cmd);
    Serial.print("Data Uploaded in Channel 2");
  }
  else{
    esp8266.println("AT+CIPCLOSE");
    Serial.println("Error Uploading Data in Channel 2");
    }
}

 
boolean connectWiFi(){            //Connect esp8266 with WiFi
  esp8266.println("AT+CWMODE=1");
  Serial.println("Connecting to WiFi");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  esp8266.println(cmd);
  delay(5000);
  
}
