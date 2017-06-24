#include "NewPing.h"
#include "Chasis.h"
#define DIST_MAX 20
#define PORCENTAJE_VELOCIDAD 3
#define BLANCO HIGH
#define NEGRO LOW
#define RETRASO_METERSE 500

const int ena = 13;
const int in1 = 12;
const int in2 = 11;
const int in3 = 10;
const int in4 = 9;
const int enb = 8;
const int triggerDelantero = 22;
const int triggerTrasero = 53;
const int echoDelantero = 23;
const int echoTrasero = 52;
const int sensorFrontal = 24;
const int sensorTrasero = 47;
const int sensorDerecha = 49;
const int sensorIzquierda = 48;

NewPing sonarDelatero(triggerDelantero, echoDelantero, DIST_MAX);
NewPing sonarTrasero(triggerTrasero, echoTrasero, DIST_MAX);
Chasis chasis;

void setup(){
  Serial.begin(9600);
  chasis.inicializar(ena, enb, in1, in2, in3, in4, PORCENTAJE_VELOCIDAD);
  inicializarSensoresBlanco();
}

void loop(){
  if(meEstoySaliendo()){
    meterse();
  }else if(algoAdelante()){
    Serial.println("avanzar");
    chasis.avanzar();
  }else if(algoDetras()){
    Serial.println("retroceder");
    chasis.retroceder();
  }else {
    Serial.println("rotar");
    chasis.rotarIzquierda();
  }
}

boolean algoDetras(){
  return (sonarTrasero.ping_cm() != 0);
}

boolean algoAdelante(){
  return (sonarDelatero.ping_cm() != 0);
}

void meterse(){
  Serial.print("meterse ");
  if(meSalgoPorDelante()){
    Serial.println("retroceder");
    chasis.retroceder();
  }else if(meSalgoPorDetras()){
    Serial.println("avanzar");
    chasis.avanzar();
  }else if(meSalgoPorLaIzquerda() && estoyAvanzando()) {
    Serial.println("doblarDerecha");
    chasis.doblarDerecha();
  }else if(meSalgoPorLaIzquerda() && estoyRetrocediendo()) {
    Serial.println("doblarIzquierda");
    chasis.doblarIzquierda();
  }else if(meSalgoPorLaDerecha() && estoyAvanzando()) {
    Serial.println("doblarIzquierda");
    chasis.doblarIzquierda();
  }else if(meSalgoPorLaDerecha() && estoyRetrocediendo()) {
    Serial.println("doblarDerecha");
    chasis.doblarDerecha();
  }
  delay(RETRASO_METERSE);
}

boolean meEstoySaliendo(){
  return (meSalgoPorDelante() || meSalgoPorDetras() || meSalgoPorLaDerecha() || meSalgoPorLaIzquerda());
}

boolean meSalgoPorDelante(){
  boolean meSalgo = (digitalRead(sensorFrontal) == NEGRO);
  if (meSalgo) Serial.println("meSalgoAdelante ");
  return meSalgo;
}

boolean meSalgoPorDetras(){
  boolean meSalgo = (digitalRead(sensorTrasero) == NEGRO);
  if (meSalgo) Serial.println("meSalgoDetras ");
  return meSalgo;
}

boolean meSalgoPorLaDerecha(){
  boolean meSalgo = (digitalRead(sensorDerecha) == NEGRO);
  if (meSalgo) Serial.println("meSalgoDerecha ");
  return meSalgo;
}

boolean meSalgoPorLaIzquerda(){
  boolean meSalgo = (digitalRead(sensorIzquierda) == NEGRO);
  if (meSalgo) Serial.println("meSalgoIzquierda ");
  return meSalgo;
}

boolean estoyAvanzando() {
  return (chasis.estado != ESTOY_RETROCEDIENDO) ;
}

boolean estoyRetrocediendo() {
  return (chasis.estado == ESTOY_RETROCEDIENDO);
}


void inicializarSensoresBlanco(){
  pinMode(sensorFrontal, INPUT);
  pinMode(sensorTrasero, INPUT);
  pinMode(sensorDerecha, INPUT);
  pinMode(sensorIzquierda, INPUT);
}