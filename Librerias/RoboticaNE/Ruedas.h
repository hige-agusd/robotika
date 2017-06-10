#ifndef __RUEDAS_H__
#define __RUEDAS_H__

class Ruedas
{
public:
  Ruedas();
  virtual ~Ruedas();
  void inicializar(int en, int in1, int in2);
  void avanzar();
  void frenar();
  void retroceder();
protected:
  int en;
  int in1;
  int in2;  
};

#endif