#include "Ruedas.h"
#include <Arduino.h>

Ruedas::Ruedas() {}

Ruedas::~Ruedas(){}

void Ruedas::inicializar(int en, int in1, int in2){
  this->en = en;
  this->in1 = in1;
  this->in2 = in2;
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(en, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void Ruedas::avanzar(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(en, HIGH);

  digitalWrite(en, LOW);
  digitalWrite(en, HIGH);
  digitalWrite(en, LOW);
  digitalWrite(en, HIGH);

}

void Ruedas::frenar(){
  digitalWrite(en, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void Ruedas::retroceder(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(en, HIGH);

  digitalWrite(en, LOW);
  digitalWrite(en, HIGH);
  digitalWrite(en, LOW);
  digitalWrite(en, HIGH);
}
