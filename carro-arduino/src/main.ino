#include <Wire.h>


#define PIN_CH_5 A2
#define PIN_CH_6 A3

#define PIN_THR A0
#define PIN_ROLL A1

#define MIN_THR 1050
#define MAX_THR 1880

#define MIN_ROLL 1048
#define MAX_ROLL 1880

#define PIN_LED_CHASSI 4
#define PIN_LED_FAROL 5


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
      // high = a  
      if (abs(v) <= 70){
        v = 0;
      }
      analogWrite(this->pin_a, abs(v));
      analogWrite(this->pin_b, 0);

    }else {
      // high = b
      if (abs(v) <= 70){
        v = 0;
      }
      analogWrite(this->pin_b, abs(v));
      analogWrite(this->pin_a, 0);
    }
  }

};

Motor tracao = Motor(6, 9);
Motor direcao = Motor(10,11);

void setup(){
  Wire.begin();
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  pinMode(PIN_LED_CHASSI, OUTPUT);
  pinMode(PIN_LED_FAROL, OUTPUT);
  tracao.off();
  direcao.off();
}

void loop(){
  int raw_thr = constrain(pulseIn(PIN_THR, 20000), MIN_THR, MAX_THR);
  int raw_dir = constrain(pulseIn(PIN_ROLL, 20000), MIN_ROLL, MAX_ROLL);

  int thr = map(raw_thr, MIN_THR, MAX_THR, -255, 255);
  int direction = map(raw_dir, MIN_ROLL, MAX_ROLL, -255, 255);

  //Serial.print("thr="); Serial.println(thr);
  //Serial.print("roll="); Serial.println(direction);

  
  //Serial.print("ch=5 "); Serial.println(pulseIn(PIN_CH_5, 20000));
  //


  int led_farol = pulseIn(PIN_CH_6, 20000);
  if (led_farol > 1600){
    digitalWrite(PIN_LED_FAROL, HIGH);
  }else{
    digitalWrite(PIN_LED_FAROL, LOW);
  }

  tracao.write(thr);
  direcao.write(direction);

}
