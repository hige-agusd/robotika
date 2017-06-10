#include "PuenteH.h"
#include "Ruedas.h"
#include <Arduino.h>

PuenteH::PuenteH() {}

PuenteH::~PuenteH(){}

void PuenteH::inicializar(const int ena, const int enb, const int in1, const int in2, const int in3, const int in4){
  ruedasIzquierdas.inicializar(ena, in1, in2); 
  ruedasDerechas.inicializar(enb,in3,in4);
  Serial.println("CONSTRUCTOR PUENTE H");
  Serial.print("ena ");Serial.println(ena);
  Serial.print("enb ");Serial.println(enb);
  Serial.print("in1 ");Serial.println(in1);
  Serial.print("in2 ");Serial.println(in2);
  Serial.print("in3 ");Serial.println(in3);
  Serial.print("in4 ");Serial.println(in4);
}

void PuenteH::avanzar(){
  Serial.println("PUENTE H: AVANZAR");
  ruedasIzquierdas.avanzar();
  ruedasDerechas.avanzar();
}

void PuenteH::retroceder(){
  ruedasIzquierdas.retroceder();
  ruedasDerechas.retroceder();
}

void PuenteH::frenar(){
  ruedasIzquierdas.frenar();
  ruedasDerechas.frenar();
}
void PuenteH::rotarIzquierda(){
  ruedasIzquierdas.retroceder();
  ruedasDerechas.avanzar();
}
void PuenteH::rotarDerecha(){
  ruedasIzquierdas.avanzar();
  ruedasDerechas.retroceder();
}