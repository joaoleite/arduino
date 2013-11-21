#include <SoftwareSerial.h>
#include <Servo.h> 

Servo myservo_H;
Servo myservo_V;

SoftwareSerial mySerial(2, 3); // RX, TX

const int PIN_SERVO_V = 5;
const int PIN_SERVO_H = 6;

const int FIRE_BRANCO = 12;
const int FIRE_AMARELO = 11;

int velocidade = 1;
int qtd_andar = 10;
int pos = 0 ;
int pos_H = 0;
int pos_V = 0;

char c;

Servo ServoOn(char pos_servo){
  if(pos_servo == 'H')
  {
    myservo_H.attach(PIN_SERVO_H);
    return myservo_H;
  }
  if(pos_servo == 'V')
  {
    myservo_V.attach(PIN_SERVO_V); 
    return myservo_V;
  }
}

void ServoOff(char pos_servo){
  if(pos_servo == 'H')
    myservo_H.detach();
  if(pos_servo == 'V')
    myservo_V.detach();
  return ;
}

void resetServos(int H, int V){
  ServoOn('H');
  ServoOn('V');
  mySerial.println("Reseting...");
  pos_V = myservo_H.read();
  pos_H = myservo_V.read();
  mySerial.println(pos_V, DEC);
  myservo_H.write(H);
  myservo_V.write(V);
  delay(500);
  ServoOff('H');
  ServoOff('V');
}

void moveDown(char pos_servo, int velocidade){
  Servo s;
  s = ServoOn(pos_servo);
  mySerial.println("Moving Down");
  pos_V = s.read();
  mySerial.println(pos_V, DEC);
  pos_V=pos_V+qtd_andar;
  if(pos_V+qtd_andar > 180)
    pos_V = 180;
  s.write(pos_V);
  delay(15);
  ServoOff(pos_servo);
}

void moveUp(char pos_servo, int velocidade){
  Servo s;
  s = ServoOn(pos_servo);
  mySerial.println("Moving up");
  pos_V = s.read();
  mySerial.println(pos_V, DEC);
  pos_V=pos_V-qtd_andar;
  if(pos_V-qtd_andar <= 0)
    pos_V = 0;
  s.write(pos_V);
  delay(15);
  ServoOff(pos_servo);
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

void setup()
{  
  //Serial debug usb
  Serial.begin(14400);
  Serial.println("Welcome Serial!!");

  pinMode(FIRE_AMARELO, OUTPUT);
  pinMode(FIRE_AMARELO, OUTPUT);
     
  // Bluetooth
  mySerial.begin(9600);
  mySerial.println("Welcome BlueTooth!!");
  
  resetServos(90,90);
}

void loop()
{
  if (mySerial.available() > 0) 
  {
    mySerial.println("Reading...");    
    c=mySerial.read();
    mySerial.println(String(c));
    if (c == 'W' || c == 'w')
    {
      moveUp('V', velocidade);
    }
    else if (c == 'S' || c == 's')
    {
      moveDown('V', velocidade);
    }
    else if (c == 'D' || c == 'd')
    {
      moveUp('H', velocidade);
    }
    else if (c == 'A' || c == 'a')
    {
      moveDown('H', velocidade);
    }
    else if (c == 'z' || c == 'z')
    {
      resetServos(90,90);
    }
    else if (c == 'f' || c == 'F')
    {
      fire_works();
    }
    else if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5')
    {
      velocidade = 1;
      qtd_andar = (c - '0') * 10;
    }
    else if (c == 'r' || c == 'R')
    {
      resetServos(90,50);

    }
    
    else
    {
      mySerial.println("No command found");
    }
  }
}
