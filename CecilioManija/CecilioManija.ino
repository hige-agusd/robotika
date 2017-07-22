#include <NewPing.h>

#define BAUDIOS_SERIAL 9600
#define MIN_DIST_CM 10
#define BLANCO LOW
#define NEGRO HIGH

//pines
const int ena = 13;
const int in1 = 12;
const int in2 = 11;
const int in3 = 10;
const int in4 = 9;
const int enb = 8;
const int bocina = 6;
const int sensorBlancoDerecho = 5;
const int sensorBlancoIzquierdo = 4;

//flujo arduino
void setup () {
  
  Serial.begin(BAUDIOS_SERIAL);
  inicializarSensoresBlanco();
  inicializarRuedas();
}

void loop() {

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

//inicializacion
void inicializarSensoresBlanco(){
  pinMode(sensorBlancoIzquierdo, INPUT);
  pinMode(sensorBlancoDerecho, INPUT);
}

void inicializarRuedas(){
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//sensor blanconegro
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
  digitalWrite(ena, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enb, HIGH);
  
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
  while(!puedeAvanzar() && debeDoblarALaIzquierda() ) {
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);;
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(ena, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
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
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, HIGH);
  digitalWrite(enb, HIGH);
  }
}

void doblarADerecha(){
  while(!puedeAvanzar() && debeDoblarALaDerecha() ) {
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

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(ena, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
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
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);
  digitalWrite(ena, HIGH);
  digitalWrite(enb, HIGH);
  }
 
}


