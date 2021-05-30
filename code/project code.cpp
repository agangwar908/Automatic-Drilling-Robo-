
//ESP8266 Blynk Joystick Car
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define RightMotorSpeed       D5   //14 
#define RightMotorDir         D6   //12 
#define LeftMotorSpeed        D7   //13 
#define LeftMotorDir          D8   //15 

char auth[] = "Qd5dFU-pLy17nV2bq-BkfRWFd6lOKnbO";  //Blynk Authentication Token
char ssid[] = "MANI1111";           //WIFI Name
char pass[] = "12345678";           //WIFI Password

int minRange = 312;
int maxRange = 712;
int relayInput = 2; 
int minspeed = 450;
int maxspeed = 1020;
int nospeed = 0;

Servo servo1;

BLYNK_WRITE(V3) {

servo1.write(param.asInt());
}

Servo servo2;
BLYNK_WRITE(V4) {

servo2.write(param.asInt());

}


void moveControl(int x, int y)
{
//Move Forward
    if(y >= maxRange && x >= minRange && x<= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed, maxspeed);
        analogWrite(LeftMotorSpeed , maxspeed);
    }


//Move Forward Right
    else if(x >= maxRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir, HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Forward Left
    else if(x <= minRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
    }

//No Move
    else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
    {
        analogWrite(RightMotorSpeed,nospeed);
        analogWrite(LeftMotorSpeed , nospeed);
    }

//Move Backward
    else if(y <= minRange && x >= minRange && x <= maxRange)
    {
        digitalWrite(RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Backward Right
    else if(y <= minRange && x <= minRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Backward Left
    else if(y <= minRange && x >= maxRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
    }
}



void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
     
    pinMode(RightMotorSpeed, OUTPUT);
    pinMode(LeftMotorSpeed , OUTPUT);
    pinMode( RightMotorDir, OUTPUT);
    pinMode(LeftMotorDir, OUTPUT);
    servo1.attach(00);
   
    digitalWrite(RightMotorSpeed, LOW);
    digitalWrite(LeftMotorSpeed , LOW);
    digitalWrite( RightMotorDir, HIGH);
    digitalWrite(LeftMotorDir, HIGH);
     servo2.attach(16);
     pinMode(relayInput, OUTPUT);

     pinMode(04,OUTPUT);
     digitalWrite(04,HIGH);
}


void loop()
{
    Blynk.run();
    
}


BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    moveControl(x,y);
}
