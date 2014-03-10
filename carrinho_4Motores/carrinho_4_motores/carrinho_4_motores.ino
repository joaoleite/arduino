#include <Wire.h>

#define PIN_ESQUERDA A0
#define PIN_DIREITA A1

#define MIN_THR 1050
#define MAX_THR 1880

#define MIN_ROLL 1050
#define MAX_ROLL 1880

class Motor{
  public:
    int pin_a;
    int pin_b;


  Motor(int a, int b){
    this->pin_a = a;
    this->pin_b = b;
  }


  void off(){
   analogWrite(this->pin_a, 0); 
   analogWrite(this->pin_b, 0); 
  }

  void write(int v){
    if (v <= 0){
      if (abs(v) <= 70){
        v = 0;
      }
      analogWrite(this->pin_a, abs(v));
      analogWrite(this->pin_b, 0);

    }else {
      if (abs(v) <= 70){
        v = 0;
      }
      analogWrite(this->pin_b, abs(v));
      analogWrite(this->pin_a, 0);
    }
  }

};

Motor esquerda = Motor(6, 9);
Motor direita = Motor(10,11);

void setup(){
  Wire.begin();
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  esquerda.off();
  direita.off();
}

void loop(){
  int raw_esquerda = constrain(pulseIn(PIN_DIREITA, 20000), MIN_THR, MAX_THR);
  int raw_direita = constrain(pulseIn(PIN_ESQUERDA, 20000), MIN_ROLL, MAX_ROLL);

  int val_velocidade = map(raw_esquerda, MIN_THR, MAX_THR, -100, 100);
  
  int val_direcao = map(raw_direita, MIN_ROLL, MAX_ROLL, -100, 100);
 
  int val_esquerda = 2.55 * val_velocidade;
  int val_direita = 2.55 * val_velocidade;
  float resta = 0;
  
  if (abs(val_velocidade) >= 20)
  {
    if (val_direcao > 60){ //direita 
      Serial.println("====> DIREITAAAAAAAAAA");
      resta = (100.0 - abs(val_direcao));
      val_esquerda = val_esquerda * resta/100;   
      
    }
    else if (val_direcao < -60)// esquerda
    {
      Serial.println("====> ESQUERDAaaaaaaaa");
      resta = (100.0 - abs(val_direcao));
      val_direita = val_direita * resta/100;
    }
  }  
  
  Serial.print("resta="); Serial.println(resta);
  Serial.print("val_velocidade="); Serial.println(val_velocidade);  
  Serial.print("val_direcao="); Serial.println(val_direcao);  
  Serial.print("val_esquerda="); Serial.println(val_esquerda);
  Serial.print("val_direita="); Serial.println(val_direita);
  Serial.println("---------------------------------");
  
  
  esquerda.write(val_esquerda);
  direita.write(val_direita);
  

  //delay(1000);
}

