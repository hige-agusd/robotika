#ifndef __PUENTE_H_H__
#define __PUENTE_H_H__

#include "Ruedas.h"

class PuenteH
{
public:
  explicit PuenteH();
  virtual ~PuenteH();
  void inicializar(int ena, int enb, int in1, int in2, int in3, int in4);
  void avanzar();
  void retroceder();
  void frenar();
  void rotarIzquierda();
  void rotarDerecha();
protected:
  Ruedas ruedasIzquierdas;
  Ruedas ruedasDerechas;
};

#endif