#include "PuenteH.h"
#include "Ruedas.h"
#include <Arduino.h>

PuenteH::PuenteH() {}

PuenteH::~PuenteH(){}

void PuenteH::inicializar(const int ena, const int enb, const int in1, const int in2, const int in3, const int in4){
  ruedasIzquierdas.inicializar(ena, in1, in2); 
  ruedasDerechas.inicializar(enb,in3,in4);
}

void PuenteH::avanzar(){
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

void PuenteH::avanzarIzquierda(){
  ruedasDerechas.avanzar();
  ruedasIzquierdas.frenar();

/*  ruedasIzquierdas.frenar();
  ruedasIzquierdas.avanzar();
  ruedasIzquierdas.frenar();
  ruedasIzquierdas.avanzar();*/

}
void PuenteH::avanzarDerecha(){
  ruedasIzquierdas.avanzar();
  ruedasDerechas.frenar();

/*  ruedasDerechas.frenar();
  ruedasDerechas.avanzar();
  ruedasDerechas.frenar();
  ruedasDerechas.avanzar();*/

}


void PuenteH::retrocederIzquierda(){
  ruedasDerechas.retroceder();
  ruedasIzquierdas.frenar();

/*  ruedasIzquierdas.frenar();
  ruedasIzquierdas.retroceder();
  ruedasIzquierdas.frenar();
  ruedasIzquierdas.retroceder();*/
}

void PuenteH::retrocederDerecha(){
  ruedasIzquierdas.retroceder();
  ruedasDerechas.frenar();

/*  ruedasDerechas.frenar();
  ruedasDerechas.retroceder();
  ruedasDerechas.frenar();
  ruedasDerechas.retroceder();*/
}
