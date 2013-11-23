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

int velocidade = 5;
int vel_atual = 0;


unsigned long lastTimeCommand;



void moveUp(int motor[])
{  
  vel_atual = map(velocidade, 0, 10, 0, 255);
  analogWrite(motor[0],vel_atual);
  analogWrite(motor[1],0);
  delay(delayTime);
}

void moveDown(int motor[])
{ 
 vel_atual = map(velocidade, 0, 10, 0, 255);
  analogWrite(motor[0],0);
  analogWrite(motor[1],vel_atual);
  delay(delayTime);
}

void offAll(){
  analogWrite(motorA[0],0);
  analogWrite(motorA[1],0);
  analogWrite(motorB[0],0);
  analogWrite(motorB[1],0);

}

void setup() {

  mySerial.begin(9600);
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);
  
  offAll();
  
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
}

void loop() {
  
  if (mySerial.available() > 0) 
  {
    mySerial.println("Reading...");    
    c=mySerial.read();
    mySerial.println(String(c));
    if (c == 'F' || c == 'f')
    {
      moveUp(motorA);
    }
    else if (c == 'B' || c == 'b')
    {
      moveDown(motorA);
    }
    else if (c == 'R' || c == 'r')
    {
      moveUp(motorB);
    }
    else if (c == 'L' || c == 'l')
    {
      moveDown(motorB);
    }
    else if (c == 'G' || c == 'g')
    {
      moveUp(motorA);
      moveDown(motorB);    
    }
    else if (c == 'I' || c == 'i')
    {
      moveUp(motorA);
      moveUp(motorB);
    }
    else if (c == 'H' || c == 'h')
    {
      moveDown(motorA);
      moveDown(motorB);    
    }
    else if (c == 'J' || c == 'j')
    {
      moveDown(motorA);
      moveUp(motorB);
    }
    else if (c == 'W')
    {
      // light front ON
      digitalWrite(4,HIGH);
    }
    else if (c == 'w')
    {
      // light front OFF
      digitalWrite(4, LOW);
    }
    
    else if (c == 'U')
    {
      // light back ON
      digitalWrite(5, HIGH);
    }
    else if (c == 'u')
    {
      // light back OFF
      digitalWrite(5, LOW);
    }    
    
    else if (c == 'V')
    {
      // Horn ON
      c == '1';
    }
    else if (c == 'v')
    {
      // Horn Off
      c == '1';
    }    
    
        
    else if (c == 'X')
    {
      // Extra ON
      c == '1';
    }
    else if (c == 'x')
    {
      // Extra off
      c == '1';
    }        
    
    else if (c == '0')
    {
      // Velocidade
      velocidade = 0;
    }           
    else if (c == '1')
    {
      // Velocidade 
      velocidade = 1;
    }        
    else if (c == '2')
    {
      // Velocidade
      velocidade = 2;
    }           
    else if (c == '3')
    {
      // Velocidade 
      velocidade = 3;
    }        
    else if (c == '4')
    {
      // Velocidade
      velocidade = 4;
    }           
    else if (c == '5')
    {
      // Velocidade 
      velocidade = 5;
    }        
    else if (c == '6')
    {
      // Velocidade
      velocidade = 6;
    }           
    else if (c == '7')
    {
      // Velocidade 
      velocidade = 7;
    }        
    else if (c == '8')
    {
      // Velocidade
      velocidade = 8;
    }           
    else if (c == '9')
    {
      // Velocidade 
      velocidade = 9;
    }        
    else if (c == 'q')
    {
      // Velocidade MAX
      velocidade = 10;
    }  

    else if (c == 'S')   // Stop
    {
      offAll();
    }
    lastTimeCommand = millis();
  }
  
  if(millis() >= (lastTimeCommand + tempoInatividade)){ 
    mySerial.println("Inative... turn off");
    //offAll();    
    lastTimeCommand = millis();
  }
  
}
