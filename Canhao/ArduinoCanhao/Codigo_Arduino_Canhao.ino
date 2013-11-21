#include <SoftwareSerial.h>
#include <Servo.h> 

Servo myservo_H;
Servo myservo_V;

SoftwareSerial mySerial(2, 3); // RX, TX

const int PIN_SERVO_V = 5;
const int PIN_SERVO_H = 4;

const int FIRE_BRANCO = 12;
const int FIRE_AMARELO = 11;

int pos = 0 ;
int pos_H = 0;
int pos_V = 0;

char c;

void ServoOn(){
  myservo_H.attach(PIN_SERVO_H);
  myservo_V.attach(PIN_SERVO_V); 
}

void ServoOff(){
  myservo_H.detach();
  myservo_V.detach();
}

void resetServos(){
  ServoOn();
  Serial.println("Reseting...");
  pos_V = myservo_H.read();
  pos_H = myservo_V.read();
  Serial.println(pos_V, DEC);
  myservo_H.write(90);
  myservo_V.write(90);
  ServoOff();
}

void moveDown(Servo s, int velocidade){
  ServoOn();
  Serial.println("Moving Down");
  pos_V = s.read();
  Serial.println(pos_V, DEC);
  for(pos = pos_V; pos < pos_V+10 && pos < 180 ; pos += velocidade)  // goes from 0 degrees to 180 degrees 
  {
    Serial.println(pos, DEC);
    s.write(pos);
    delay(15);
  }
  ServoOff();
}

void moveUp(Servo s, int velocidade){
  ServoOn();
  Serial.println("Moving up");
  pos_V = s.read();
  Serial.println(pos_V, DEC);
  for(pos = pos_V; pos > pos_V-10 && pos > 0 ; pos -= velocidade)  // goes from 0 degrees to 180 degrees 
  {
    Serial.println(pos, DEC);
    s.write(pos);
    delay(15);
  }
  ServoOff();
}


void fire_works(){
  pinMode(FIRE_AMARELO, OUTPUT);
  pinMode(FIRE_BRANCO, OUTPUT);
  digitalWrite(FIRE_AMARELO,  LOW);
  digitalWrite(FIRE_BRANCO, HIGH);
  delay(150);
  digitalWrite(FIRE_AMARELO,  LOW);
  digitalWrite(FIRE_BRANCO, LOW);
  delay(800);
}  


void fire(){
  ServoOff();
  Serial.println("Fire!!!");
  digitalWrite(FIRE_AMARELO,  HIGH);
  digitalWrite(FIRE_BRANCO, LOW);
  delay(500);
  digitalWrite(FIRE_AMARELO,  LOW);
  digitalWrite(FIRE_BRANCO, LOW);
}  

void setup()
{  
  //Serial debug usb
  Serial.begin(9600);
  Serial.println("Welcome Serial!!");

  pinMode(FIRE_AMARELO, OUTPUT);
  pinMode(FIRE_AMARELO, OUTPUT);
   
  // Bluetooth
  mySerial.begin(9600);
  mySerial.println("Welcome BlueTooth!!");
  
  resetServos();
}

void loop()
{
  if (Serial.available() > 0) {
    mySerial.println("Reading...");
    
    //c=Serial.read();
    c=mySerial.read();

    if (c == 'W')
    {
      moveUp(myservo_V, 1);
    }
    else if (c == 'S')
    {
      moveDown(myservo_V, 1);
    }
    else if (c == 'D')
    {
      moveUp(myservo_H, 1);
    }
    else if (c == 'A')
    {
      moveDown(myservo_H, 1);
    }
    else if (c == 'Z')
    {
      resetServos();
    }
    else if (c == 'F')
    {
      fire_works();
    }
    else
    {
      Serial.println("Error");
    }
  }
}

