// Sensor de luz
int lightPin = 0; // Pin LDR.
int valor; // Variable para cálculos.
int min = 988; // Valor minimo obtenido por A0.
int max = 1018; // Valor maximo obtenido por A0.

// Temperatura
#include <DHT11.h>
DHT11 dht11(2); // Pin 2
  // Ventilador
  int ventilador =  27;
  int err;
  char dato;
  float temp, hum; // lectores digitales

// Luces

// terraza = 53, 49, 47

// Sala = 52, 54 

// Alarma = 50, 51

int led1Sala = 52;
int led2Sala = 54;

int led1Terraza = 53;
int led2Terraza = 47;
int led3Terraza = 49;

int led1Calle = 43;

int led1Interior = 41;
int led2Interior = 39;
int led3Interior = 37;
int led4Interior = 35;
int led5Interior = 33;

int led1Alarma = 51;
int led2Alarma = 50;

int led1Exterior = 22;
int led2Exterior = 24;

// Sensor de Proximidad - Funciona a 5V
int ecoPin = 12;  // cable blanco/marron
int trigPin = 13; // cable azul
bool filtro_proximidad = false;
long duracion, distancia; 

// Sensor PIR

int pinopir = 29;  //Pino ligado ao sensor PIR
int acionamento;  //Variavel para guardar valor do sensor
int ct = 15;
int bocina = 31;
bool filtro_alarma = false;



void setup(){
  Serial.begin(9600);
  pinMode(ventilador, OUTPUT);  pinMode(led1Sala, OUTPUT);  pinMode(led2Sala, OUTPUT);  pinMode(led1Terraza, OUTPUT); pinMode(led2Terraza, OUTPUT);  pinMode(led3Terraza, OUTPUT);  
  pinMode(led1Calle, OUTPUT);  pinMode(led1Interior, OUTPUT);  pinMode(led2Interior, OUTPUT);  pinMode(led3Interior, OUTPUT);  pinMode(led4Interior, OUTPUT);  pinMode(led5Interior, OUTPUT);
  pinMode(led1Alarma, OUTPUT);  pinMode(led2Alarma, OUTPUT);
  
  pinMode(bocina, OUTPUT); //Define pino como saida
  pinMode(pinopir, INPUT);   //Define pino sensor como entrada
  
  pinMode(trigPin, OUTPUT);   //envia la señal de ultrasonido
  pinMode(ecoPin, INPUT);     //reciba la señal de ultrasonido
  
}

void loop(){

    char dato = Serial.read();

    if(dato == 'a'){
      lucesSala(true);
    }

    if(dato == 'b'){
      lucesSala(false);
    }

    if(dato == 'c'){
      lucesTerraza(true);
    }

    if(dato == 'd'){
      lucesTerraza(false);
    }

    if(dato == 'e'){
      lucesCalle(true);
    }

    if(dato == 'f'){
      lucesCalle(false);
    }
    
    if(dato == 'g'){
      lucesInterior(true);
    }

    if(dato == 'h'){
      lucesInterior(false);
    }
    
    if(dato == 'i'){
      filtro_alarma = true;
    }
    
    if(dato == 'j'){
      lucesAlarma(false);
      digitalWrite(bocina, LOW);
      filtro_alarma = false;
    }
    
    
   if (getTempValue() >= 26){
    digitalWrite(ventilador, HIGH);
   }else{
    digitalWrite(ventilador, LOW);
   }

   if (valorSensor() > 600){
      lucesExterior(true);
   }else {
      lucesExterior(false);
   }

   getProximidad();
   
   if (filtro_alarma == true){
      getPIR();
   }

   
   
   delay(1000);
    
 }
 
// Funcion para el sensor de Luz
int valorSensor(){
  valor = analogRead(lightPin); // Leemos el valor de A0.
  return (valor);
}


// Funcion para el modulo PIR
void getPIR(){
  acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
  if (acionamento == HIGH) {
    digitalWrite(bocina, HIGH);
    lucesAlarma(true);
  }
}


// Funcion para el valor de la proximidad
void getProximidad(){
  if (filtro_proximidad == false){
  //funcionamento del sensor envia y recibe la señal
   digitalWrite(trigPin, LOW);  
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(5); 
   digitalWrite(trigPin, LOW);
   // Fin de lectura
   duracion = pulseIn(ecoPin, HIGH); 
   //transformo los microsegundos en centimetros
   distancia = (duracion / 29 / 2);
   
   if(distancia <= 14){
     lucesSala(true);
     filtro_proximidad = true;  
   }
  }
}
// Retorna el valor de la temperatura
float getTempValue(){
    if((err = dht11.read(hum, temp)) == 0){    // Si devuelve 0 es que ha leido bien
      Serial.print(temp);
      delay(20);
      return temp;
    }else{
      return 0;
    }
}


//Funciones para encender luces
void lucesSala(bool filtro){
  if(filtro == true) {
    digitalWrite(led1Sala, HIGH);
    digitalWrite(led2Sala, HIGH);
  }else{
    digitalWrite(led1Sala, LOW);
    digitalWrite(led2Sala, LOW);
    filtro_proximidad = false;  
  }
}

void lucesTerraza(bool filtro){
  if(filtro == true) {
    digitalWrite(led1Terraza, HIGH);
    digitalWrite(led2Terraza, HIGH);
    digitalWrite(led3Terraza, HIGH);
  }else{
    digitalWrite(led1Terraza, LOW);
    digitalWrite(led2Terraza, LOW);
    digitalWrite(led3Terraza, LOW);
  }
}

void lucesInterior(bool filtro){
  if(filtro == true) {
    digitalWrite(led1Interior, HIGH);
    digitalWrite(led2Interior, HIGH);
    digitalWrite(led3Interior, HIGH);
    digitalWrite(led4Interior, HIGH);
    digitalWrite(led5Interior, HIGH);
    
  }else{
    digitalWrite(led1Interior, LOW);
    digitalWrite(led2Interior, LOW);
    digitalWrite(led3Interior, LOW);
    digitalWrite(led4Interior, LOW);
    digitalWrite(led5Interior, LOW);
  }
}

void lucesCalle(bool filtro){
  if(filtro == true) {
    digitalWrite(led1Calle, HIGH);
    
  }else{
    digitalWrite(led1Calle, LOW);
    
  }
}

void lucesAlarma(bool filtro){
  if(filtro == true) {
    digitalWrite(led1Alarma, HIGH);
    digitalWrite(led2Alarma, HIGH);
  }else{
    digitalWrite(led1Alarma, LOW);
    digitalWrite(led2Alarma, LOW);
   }
}

void lucesExterior(bool filtro){
  if(filtro == true) {
    digitalWrite(led1Exterior, HIGH);
    digitalWrite(led2Exterior, HIGH);
  }else{
    digitalWrite(led1Exterior, LOW);
    digitalWrite(led2Exterior, LOW);
   }
}
//Fin funciones para encender luces









