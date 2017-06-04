#include <NewPing.h>

//alias estaticos
#define BAUDIOS_SERIAL 9600
#define MAX_DIST 30000000
#define MIN_DIST_CM 10
#define BLANCO LOW
#define NEGRO HIGH
#define TIEMPO_RETROCEDIENDO 0
#define TIEMPO_DOBLAR_FORZADO 350
#define MAX_INTENTOS 3
#define INTENTOS_AVANZAR 10
#define MUY_MANIJA 250

//clases y tipos
//typedef enum {NINGUNO, IZQUIERDA, DERECHA} Lado;

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
const int sensorBlancoCentral = 3;
const int trigger = 2;
const int echo = 1;

//componentes
NewPing ultrasonido(echo,trigger, MAX_DIST);

//variables
//Lado doblarA;
int manija;

//flujo arduino
void setup () {
  
  Serial.begin(BAUDIOS_SERIAL);
  inicializarSensoresBlanco();
  inicializarRuedas();
  inicializarVariables();
}

void loop() {

  if(estaPorChocar()){
    frenar();
  }
  else if(puedeAvanzar()){
    avanzar();
  }
  else if(debeDoblarALaDerecha()){
    Serial.println("dobla a la derecha");
//        doblarA = DERECHA;
    doblarADerecha();
  }
  else if(debeDoblarALaIzquierda()){
    Serial.println("dobla a la izquierda");
//        doblarA = IZQUIERDA;
    doblarAIzquierda();
  }
  else{
    frenar();
  }

  if(debeAumentarManija()){
    manija++;
  } else {
    manija = 0;
  }
}

//inicializacion
void inicializarSensoresBlanco(){
  pinMode(sensorBlancoIzquierdo, INPUT);
  pinMode(sensorBlancoDerecho, INPUT);
  pinMode(sensorBlancoCentral, INPUT);
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

void inicializarVariables(){
//  doblarA = NINGUNO;
  manija = 0;
  pinMode(bocina, OUTPUT);
  apagarBocina();
}

//ultrasonido
boolean estaPorChocar(){
  /*double dist = ultrasonido.ping_cm();
  boolean porChocar = dist == 0 ? false : dist <= MIN_DIST_CM;
  if(porChocar){
    tocarBocina();
  } else {
    apagarBocina();
  }
  Serial.print("esta por chocar? ");
  Serial.print(porChocar ? "si" : "no");
  Serial.print("la distancia es: ");
  Serial.println(dist);
  return porChocar;
  //*/return false;
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

boolean puedePicar(){
  return estaMuyManija() && (digitalRead(sensorBlancoCentral) == NEGRO);
}

boolean estaMuyManija(){
  return manija >= MUY_MANIJA;
}

boolean debeAumentarManija(){
  boolean sensorCentralNegro = digitalRead(sensorBlancoCentral) == NEGRO;
  return sensorCentralNegro && puedeAvanzar() && (manija <= MUY_MANIJA) ;
}

//ruedas
void frenar(){

/*  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);*/
  digitalWrite(ena, LOW);
  
/*  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);*/
  digitalWrite(enb, LOW);

}

void picar(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(ena, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enb, HIGH);
}

void caminar(){
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

void avanzar(){
  //if(puedePicar()){
  //  picar();      
  //} else {
    caminar();
  //}
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

//bocina
void tocarBocina(){
  digitalWrite(bocina, HIGH);
}

void apagarBocina(){
  digitalWrite(bocina, LOW);
}

