#include <Chasis.h>
#include <Ruedas.h>
#include <PuenteH.h>
#include <NewPing.h>


#define MAX_DIST_CM 7'0

//pines
const int ena = 13;
const int in1 = 12;
const int in2 = 11;
const int in3 = 10;
const int in4 = 9;
const int enb = 8;
const int triggerDelantero = 22;
const int echoDelantero = 23;
const int echoTrasero = 52;
const int triggerTrasero = 53;

//componentes
hasis chasis;
NewPing sonarDelantero(triggerDelantero, echoDelantero, MAX_DIST_CM);
NewPing sonarTrasero(triggerTrasero, echoTrasero, MAX_DIST_CM);

void setup(){
  Serial.begin(9600);
  chasis.inicializar(ena, enb, in1, in2, in3, in4, 40);
}

void loop(){
  if(sonarDelantero.ping_cm())
    chasis.avanzar();
  else if (sonarTrasero.ping_cm())
    chasis.retroceder();
  else
    chasis.rotarIzquierda();
}
