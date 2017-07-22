#include "Chasis.h"
#include "PuenteH.h"
#include <Arduino.h>

Chasis::Chasis(){}
Chasis::~Chasis(){}
void Chasis::inicializar(int ena, int enb, int in1, int in2, int in3, int in4, int porcentajeVelocidad){
  this->puenteH.inicializar(ena, enb, in1, in2, in3, in4);
  this->editarVelocidad(porcentajeVelocidad);
}
void Chasis::avanzar(){
  this->demorar(&PuenteH::avanzar);
  estado = ESTOY_AVANZANDO;
}

void Chasis::retroceder(){
  this->demorar(&PuenteH::retroceder);
  estado = ESTOY_RETROCEDIENDO;
}
void Chasis::frenar(){
  this->demorar(&PuenteH::frenar);
  estado = ESTOY_QUIETO;
}
void Chasis::rotarIzquierda(){
  this->demorar(&PuenteH::rotarIzquierda);
  estado = ESTOY_ROTANDO_IZQUIERDA;
}
void Chasis::rotarDerecha(){
  this->demorar(&PuenteH::rotarDerecha);
  estado = ESTOY_ROTANDO_DERECHA;
}

void Chasis::editarVelocidad(int editarVelocidad){
  this->porcentajeVelocidad = 100 - porcentajeVelocidad;
  if (this->porcentajeVelocidad < 0)
  {
    this->porcentajeVelocidad = 0;
  }
}


//arreglar
void Chasis::doblarIzquierda(){
  if(estado != ESTOY_RETROCEDIENDO)
    this->demorar(&PuenteH::avanzarIzquierda);
  else
    this->demorar(&PuenteH::retrocederDerecha);
  estado = ESTOY_DOBLANDO_IZQUIERDA;
}

void Chasis::doblarDerecha(){
  if(estado != ESTOY_RETROCEDIENDO)
    this->demorar(&PuenteH::avanzarDerecha);
  else
    this->demorar(&PuenteH::retrocederIzquierda);
   estado = ESTOY_DOBLANDO_DERECHA;
}

void Chasis::demorar(void (PuenteH::*accion)()){
  (this->puenteH.*accion)();
/*  for (int i = 1; i < this->porcentajeVelocidad                                                                                                                               ; ++i)
  {
    this->puenteH.frenar();
  }
  (this->puenteH.*accion)();*/
}