#include <SoftwareSerial.h>

int motor1Pin1 = 6; //Motor Tracao
int motor1Pin2 = 9; //Motor Tracao
int motor2Pin1 = 10; //Motor Roda
int motor2Pin2 = 11; //Motor Roda

SoftwareSerial mySerial(2, 3); // RX, TX

int motorA[] = {9,6};
int motorB[] = {11,10};
int delayTime = 50;

char c;

int countadorInatividade = 0;


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


void setupInicial() 
{

  mySerial.println("PIN 1 H L ");
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
  delay(2000);
  mySerial.println("PIN 1 L H ");
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,HIGH);
  delay(2000);
  mySerial.println("PIN 1 L L ");
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,LOW);

  mySerial.println("PIN 2 H L ");
  digitalWrite(motor2Pin1,HIGH);
  digitalWrite(motor2Pin2,LOW);
  delay(2000);
  mySerial.println("PIN 2 L H ");
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,HIGH);
  delay(2000);
  mySerial.println("PIN 2 L L ");
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,LOW);  
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
    else
    {
      mySerial.println("No command found");
      mySerial.println(c);
      offAll();
    }
    countadorInatividade = 0;
  }
  else
  {
    countadorInatividade++;
    if (countadorInatividade>150)
    {
      mySerial.println("No Serial Input");
      offAll();
      countadorInatividade = 0;
    }
    delay(1);
  }
}
