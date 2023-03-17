#include <Servo.h>

#define EN_A 5
#define IN_1A 13
#define IN_2A 12

#define EN_B 6
#define IN_1B 8
#define IN_2B 7

#define POTVEL A0
#define POTDIR A1

#define botao 4
#define ver 3
#define verde 2

Servo volante;

void setup()
{
  volante.attach(11);

  pinMode(botao, INPUT);

  pinMode(ver, OUTPUT);
  pinMode(verde, OUTPUT);

  pinMode(EN_A, OUTPUT);
  pinMode(IN_1A, OUTPUT);
  pinMode(IN_2A, OUTPUT);

  pinMode(EN_B, OUTPUT);
  pinMode(IN_1B, OUTPUT);
  pinMode(IN_2B, OUTPUT);

  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
  volante.write(0);
}

void loop()
{
  int valorBotao = digitalRead(botao);
  if (valorBotao == HIGH) {
    ledOnOff(HIGH);
	motorOnOff(HIGH);
    direcao();
  } else {
    ledOnOff(LOW);
    motorOnOff(LOW);
  }
}

void ledOnOff (bool estado){
  if(estado){
  	digitalWrite(verde, HIGH);
    digitalWrite(ver, LOW);
  } else {
  	digitalWrite(verde, LOW);
    digitalWrite(ver, HIGH);
  }
}

void motorOnOff (bool estado){
  int valorVel = analogRead(POTVEL) * 0.25;
  if(estado){
    if (valorVel >= 127) {
      int velocidade = map(valorVel, 127, 255, 0, 255);
 
      //motor para FRENTE
      digitalWrite(IN_1A, HIGH);
      digitalWrite(IN_2A, LOW);
      analogWrite(EN_A, velocidade);
      digitalWrite(IN_1B, HIGH);
      digitalWrite(IN_2B, LOW);
      analogWrite(EN_B, velocidade); 
    
    } else {
      int velocidade = map(valorVel, 127.5, 0, 0, 255);
     
      //motor para TRAS
      digitalWrite(IN_1A, LOW);
      digitalWrite(IN_2A, HIGH);
      analogWrite(EN_A, velocidade);
      digitalWrite(IN_1B, LOW);
      digitalWrite(IN_2B, HIGH);
      analogWrite(EN_B, velocidade);    
    }
  } else {
  	digitalWrite(EN_A, LOW);
    digitalWrite(EN_B, LOW);
  }
  delay(100);
}

void direcao (){
  int valorDir = analogRead(POTDIR) * 0.25;
  int direcao = map(valorDir, 0, 255, 0, 180);
  volante.write(direcao);
}
