#include "NewPing.h"
#include "Chasis.h"
#define DIST_MAX 35
#define PORCENTAJE_VELOCIDAD 20
#define BLANCO LOW
#define NEGRO HIGH
#define MODO_SUMO HIGH
#define MODO_SIGUELINEAS LOW

//pines siguelineas
const int sensorBlancoDerecho = 5;
const int sensorBlancoIzquierdo = 4;
//pines comunes
const int ena = 13;
const int in1 = 12;
const int in2 = 11;
const int in3 = 10;
const int in4 = 9;
const int enb = 8;
//pines sumo
const int triggerDelantero = 22;
const int triggerTrasero = 53;
const int echoDelantero = 23;
const int echoTrasero = 52;
const int sensorFrontal = 24;
const int sensorTrasero = 47;
const int sensorDerecha = 49;
const int sensorIzquierda = 48;
//pines adicionales
const int llaveModo = 25;

NewPing sonarDelatero(triggerDelantero, echoDelantero, DIST_MAX);
NewPing sonarTrasero(triggerTrasero, echoTrasero, DIST_MAX);
Chasis chasis;

void setup() {
  pinMode(llaveModo, INPUT);
  setupSumo();
  setupSiguelineas();
}

void loop(){
  if (digitalRead(llaveModo) == MODO_SUMO)
    loopSumo();
  else
    loopSiguelineas();
}

void setupSumo(){
  Serial.begin(9600);
  chasis.inicializar(ena, enb, in1, in2, in3, in4, PORCENTAJE_VELOCIDAD);
  inicializarSensoresBlanco();
}

void loopSumo(){
  if(meEstoySaliendo()){
    meterse();
  }else if(algoAdelante()){
    Serial.println("algo adelante");
    chasis.avanzar();
  }else if(algoDetras()){
    Serial.println("algo atras");
    chasis.retroceder();
  }else{
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
  if(meSalgoPorDelante()){
    Serial.println("Me voy por adelante: retroceder");
    chasis.retroceder();
  }else if(meSalgoPorDetras()){
    Serial.println("Me voy por atras: avanzar");
    chasis.avanzar();
  }else if(meSalgoPorLaIzquerda() && estoyAvanzando()) {
    Serial.println("Me voy por la izquierda avanzando: doblar a la derecha");
    chasis.doblarDerecha();
  }else if(meSalgoPorLaIzquerda() && estoyRetrocediendo()) {
    Serial.println("Me voy por la izquierda retrocediendo: doblar a la izquierda");
    chasis.doblarIzquierda();
  }else if(meSalgoPorLaDerecha() && estoyAvanzando()) {
    Serial.println("Me voy por la derecha avanzando: doblar a la izquierda");
    chasis.doblarIzquierda();
  }else if(meSalgoPorLaDerecha() && estoyRetrocediendo()) {
    Serial.println("Me voy por la derecha retrocediendo: doblar a la derecha");
    chasis.doblarDerecha();
  }
  delay(750);
}

boolean meEstoySaliendo(){
  return (meSalgoPorDelante() || meSalgoPorDetras() || meSalgoPorLaDerecha() || meSalgoPorLaIzquerda());
}

boolean meSalgoPorDelante(){
  return(digitalRead(sensorFrontal) == BLANCO);
}

boolean meSalgoPorDetras(){
  return(digitalRead(sensorTrasero) == BLANCO);
}

boolean meSalgoPorLaDerecha(){
  return(digitalRead(sensorDerecha) == BLANCO);
}

boolean meSalgoPorLaIzquerda(){
  return(digitalRead(sensorIzquierda) == BLANCO);
}

boolean estoyAvanzando() {
  return (chasis.estado != ESTOY_RETROCEDIENDO);
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


void setupSiguelineas(){
  pinMode(sensorBlancoIzquierdo, INPUT);
  pinMode(sensorBlancoDerecho, INPUT);
}

void loopSiguelineas(){
  if(puedeAvanzar()){
    avanzar();
  }
  else if(debeDoblarALaDerecha()){
    Serial.println("dobla a la derecha");
    doblarADerecha();
  }
  else if(debeDoblarALaIzquierda()){
    Serial.println("dobla a la izquierda");
    doblarAIzquierda();
  }
  else{
    frenar();
  }
}

boolean puedeAvanzar(){
  boolean izquierdoEnNegro = digitalRead(sensorBlancoIzquierdo) == NEGRO;
  boolean derechoEnNegro = digitalRead(sensorBlancoDerecho) == NEGRO;
  boolean bnavanzar = izquierdoEnNegro && derechoEnNegro;
  return bnavanzar;
}

boolean debeDoblarALaDerecha(){
  boolean izquierdoEnBlanco = digitalRead(sensorBlancoIzquierdo) == BLANCO;
  boolean derechoEnNegro = digitalRead(sensorBlancoDerecho) == NEGRO;
  return izquierdoEnBlanco && derechoEnNegro;
}

boolean debeDoblarALaIzquierda(){
  boolean izquierdoEnNegro = digitalRead(sensorBlancoIzquierdo) == NEGRO;
  boolean derechoEnBlanco = digitalRead(sensorBlancoDerecho) == BLANCO;
  return izquierdoEnNegro && derechoEnBlanco;
}

//ruedas
void frenar(){
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
}

void avanzar(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, HIGH);
  digitalWrite(enb, HIGH);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, HIGH);
  digitalWrite(enb, HIGH);

}

void doblarAIzquierda(){
  while(!puedeAvanzar() && debeDoblarALaIzquierda()){
    digitalWrite(ena, LOW);
    digitalWrite(enb, LOW);
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(ena, HIGH);
    
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(enb, HIGH);

    digitalWrite(ena, LOW);
    digitalWrite(enb, LOW);
    digitalWrite(ena, HIGH);
    digitalWrite(enb, HIGH);  
  }
}

void doblarADerecha(){
  while(!puedeAvanzar() && debeDoblarALaDerecha()){
    digitalWrite(ena, LOW);
    digitalWrite(enb, LOW);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(ena, HIGH);
    
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(enb, HIGH);

    digitalWrite(ena, LOW);
    digitalWrite(enb, LOW);
    digitalWrite(ena, HIGH);
    digitalWrite(enb, HIGH);
  }
}

void retroceder(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(ena, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enb, HIGH); 
}
