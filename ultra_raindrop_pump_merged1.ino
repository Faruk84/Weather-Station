int rain;
int trigpin=9;
int echopin=10;
int relaypin=4;

float x;
long duration;
float height;
float realheight;
void setup() {
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(relaypin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  rain=analogRead(A0);
  Serial.print("\ndata=");
  Serial.print(rain);
  if(rain>=1000){
    
  
  
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  duration=pulseIn(echopin,HIGH);
  height=duration*0.34/2;
  realheight=125-height;
  x=0.205*realheight;
  Serial.print("\nheight=");
  Serial.print(height);
  Serial.print("Rainfall: ");
  Serial.print(x-9);
  Serial.print("mm");
  Serial.print("\n");
  //delay(5000);
  
  if(x>=10)
  
  digitalWrite(4,HIGH);
  
   else
  
  digitalWrite(4,LOW);
  delay(5000);
  

  }
}
  
   





