  #include "NewPing.h"
  #include "Chasis.h"
  #define DIST_MAX 35
  #define PORCENTAJE_VELOCIDAD 20
  #define BLANCO LOW
  #define NEGRO HIGH

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
