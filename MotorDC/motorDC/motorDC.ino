#include <SoftwareSerial.h>

int motor1Pin1 = 6; //Motor Tracao
int motor1Pin2 = 9; //Motor Tracao
int motor2Pin1 = 10; //Motor Roda
int motor2Pin2 = 11; //Motor Roda

int tempoInatividade = 200; // 

SoftwareSerial mySerial(2, 3); // RX, TX

int motorA[] = { motor1Pin2 , motor1Pin1 };
int motorB[] = { motor2Pin2 , motor2Pin1 };
int delayTime = 0;

char c;


unsigned long lastTimeCommand;



void moveUp(int motor[])
{ 
  digitalWrite(motor[0],HIGH);
  digitalWrite(motor[1],LOW);
  delay(delayTime);
}

void moveDown(int motor[])
{ 
  digitalWrite(motor[0],LOW);
  digitalWrite(motor[1],HIGH);
  delay(delayTime);
}

void offAll(){
  digitalWrite(motorA[0],LOW);
  digitalWrite(motorA[1],LOW);
  digitalWrite(motorB[0],LOW);
  digitalWrite(motorB[1],LOW);

}

void setup() {

  mySerial.begin(9600);
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);

}

void loop() {
  
  if (mySerial.available() > 0) 
  {
    mySerial.println("Reading...");    
    c=mySerial.read();
    mySerial.println(String(c));
    if (c == 'W' || c == 'w')
    {
      moveUp(motorA);
    }
    else if (c == 'S' || c == 's')
    {
      moveDown(motorA);
    }
    else if (c == 'D' || c == 'd')
    {
      moveUp(motorB);
    }
    else if (c == 'A' || c == 'a')
    {
      moveDown(motorB);
    }
    else if (c == 'x' || c == 'x')   // X - Stop
    {
      offAll();
    }
    lastTimeCommand = millis();
  }
  
  if(millis() >= (lastTimeCommand + tempoInatividade)){ 
    mySerial.println("Inative... turn off");
    offAll();    
    lastTimeCommand = millis();
  }
  
}
