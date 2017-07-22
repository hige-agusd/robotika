#ifndef __CHASIS_H__
#define __CHASIS_H__
#include "PuenteH.h"
#include <Arduino.h>

enum Estado
{
  ESTOY_AVANZANDO, ESTOY_RETROCEDIENDO, ESTOY_ROTANDO_DERECHA, ESTOY_ROTANDO_IZQUIERDA, ESTOY_DOBLANDO_DERECHA, ESTOY_DOBLANDO_IZQUIERDA,
  ESTOY_QUIETO
};

class Chasis
{
public:
  Chasis();
  virtual ~Chasis();
  void inicializar(int ena, int enb, int in1, int in2, int in3, int in4, int porcentajeVelocidad = 100);
  void avanzar();
  void retroceder();
  void frenar();
  void rotarIzquierda();
  void rotarDerecha();
  void doblarIzquierda();
  void doblarDerecha();
  void editarVelocidad(int porcentajeVelocidad);
  Estado estado;
protected:
  PuenteH puenteH;
  int porcentajeVelocidad;
private:
  void demorar(void (PuenteH::*accion)());
};



#endif