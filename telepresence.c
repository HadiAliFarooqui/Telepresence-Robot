// Simple WiFi Car using Blynk Joystick Widget
// Pins are based on looking at rear of car.
 
// -- Motor Leads --
// Looking at rear of car, left motor leads, A- -> red, A+ -> black
// Looking at rear of car, right motor leads, B- -> black, B+ -> red
 
// -- Blynk Settings --
// ---Use a Joystick Widget --                                                      
//  ->Merge not Split  should be selected
//  ->Select "Virtual Pin 1"
//  ->Turn autorotate off, use the phone in a portrait not landscape position
//  ->Leave autoreturn on...too hard to control with it off
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Servo.h> 
 
Servo myservo;
int pos=0; 
#define RightMotorSpeed 4
#define RightMotorDir   0 //B
#define LeftMotorSpeed  2  //A
#define LeftMotorDir    5
#define hadi            12
#define hadiali         14
#define mudssir          13
#define musdd1           15
int tim=0;
int dist=0;
 int x,y,z,w,p,q,r,s;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// Use your own WiFi settings
char auth[] = "a7453077948448788a0496c8730b78e5";
char ssid[] = "mudassir";
char pass[] = "1234567890";
 
// neutral zone settings for x and y
// joystick must move outside these boundary numbers to activate the motors
// makes it a little easier to control the wifi car
int minRange = 312;
int maxRange = 712;
 
// analog speeds from 0 (lowest) - 1023 (highest)
// 3 speeds used -- 0 (noSpeed), 350 (minSpeed), 850 (maxSpeed).
// use whatever speeds you want...too fast made it a pain in the ass to control
int minSpeed = 0;
int maxSpeed = 1023;
double noSpeed = 0;
int nomov=512;
 
 
void moveControl(int x, int y,int z, int w)
{
  // movement logic
  // move forward

   // y je vetsi jak maxrange a soucasne x je vetsi jak minRange a soucasne mensi jak max range 
  if(x==1) //zataci R
  {
    digitalWrite(RightMotorDir,HIGH);  
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,HIGH); 
    analogWrite(LeftMotorSpeed,HIGH);
    Serial.println("forward");
  }
  
  // move  right
  else if(z == 1)   //zataci R
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,minSpeed); 
    analogWrite(LeftMotorSpeed,maxSpeed);
    Serial.println("right");
  }
 
   //left
  else if(w==1)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed); 
    analogWrite(LeftMotorSpeed,minSpeed);
  Serial.println("left");
  }
  
 
  
 // move back
  else if(y == 1)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,maxSpeed); 
    analogWrite(LeftMotorSpeed,maxSpeed);
  Serial.println("back and");
  }

 else 
 {
     digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,LOW); 
    analogWrite(LeftMotorSpeed,LOW);
  Serial.println("stop");
  
  
  
  }
  
}
void moveControl1(int p,int q)
 {
 if(p == 1) //zataci R
  {
    digitalWrite(12,HIGH);  
    digitalWrite(14,LOW);
    analogWrite(12,maxSpeed); 
    analogWrite(14,minSpeed);
     Serial.println("UP");
  }
  // move back
  else if(q == 1)
  {
    digitalWrite(12,LOW);
    digitalWrite(14,HIGH);
   analogWrite(12,minSpeed); 
    analogWrite(14,maxSpeed);
  Serial.println("DOWN");
  }
 
  // move back and right
 else
 {
   digitalWrite(12,HIGH);
    digitalWrite(14,HIGH);
   analogWrite(12,maxSpeed); 
    analogWrite(14,maxSpeed);
  Serial.println("stuck");
 } 
 }

 void moveControl2(int r,int s)
 {
 if(r == 1) //zataci R
  {
    digitalWrite(13,HIGH);  
    digitalWrite(15,LOW);
    analogWrite(13,maxSpeed); 
    analogWrite(15,minSpeed);
     Serial.println("UP");
  }
  // move back
  else if(s == 1)
  {
    digitalWrite(13,LOW);
    digitalWrite(15,HIGH);
   analogWrite(13,minSpeed); 
    analogWrite(15,maxSpeed);
  Serial.println("DOWN");
  }
 
  // move back and right
 else
 {
   digitalWrite(13,HIGH);
    digitalWrite(15,HIGH);
   analogWrite(13,maxSpeed); 
    analogWrite(15,maxSpeed);
  Serial.println("stuck");
 } 
 }


 
void setup()
{
  // initial settings for motors off and direction forward
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, LOW);
  digitalWrite(LeftMotorDir,LOW);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(14, LOW);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
  Blynk.begin(auth, ssid, pass);
    // put your setup code here, to run once


 Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  
 }
 
 
void loop()
{
  Blynk.run();
  
}
 
 
BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  moveControl(x,y,z,w);
}

BLYNK_WRITE(V2)
{
  int y= param[0].asInt();
  moveControl(x,y,z,w);
}

BLYNK_WRITE(V3)
{
  int z = param[0].asInt();
  moveControl(x,y,z,w);
}

BLYNK_WRITE(V4)
{
  int w = param[0].asInt();
  moveControl(x,y,z,w);
}

BLYNK_WRITE(V5)
{
  int p = param[0].asInt();

  moveControl1(p,q); 
}
 
BLYNK_WRITE(V6)
{
  int q = param[0].asInt();

  moveControl1(p,q); 
}
BLYNK_WRITE(V7)
{
  int r = param[0].asInt();

  moveControl2(r,s); 
}
 
BLYNK_WRITE(V8)
{
  int s = param[0].asInt();

  moveControl2(r,s); 
}


