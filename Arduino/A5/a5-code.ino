#include<EEPROM.h>

const int LM35 = 0;
const int BotaoG = 9;
const int BotaoL = 11;
const int ledPin = 13;
float temperatura[20];
float leitura[40];
int ADClido = 0;
int EstadoBotaoG = 0;
int EstadoBotaoL = 0;
int lastButtonStateG = 0;
int lastButtonStateL = 0;
int cont = 0;
int i = 0;
int onG = 0;
int onL = 0;

void setup(){
  Serial.begin(9600);
  //analogReference(INTERNAL1V1); // Arduino MEGA /Atmel2560
  analogReference(INTERNAL);
  pinMode(BotaoG,INPUT);
  pinMode(BotaoL,INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop(){
// Gravação
  EstadoBotaoG = digitalRead(BotaoG);
  if (EstadoBotaoG != lastButtonStateG){
    if (EstadoBotaoG == HIGH){
      if (onG == 0){
        onG = 1;
      }else{
        onG = 0;
      }
    }
    delay(50);
  }
  lastButtonStateG = EstadoBotaoG;

  if (onG == 1){
    ADClido = analogRead(LM35);
    temperatura[cont/2] = ADClido * 0.1075268817; // Constante de referência para LM35
    if (cont<40){
      EEPROM.write(cont,(int)temperatura[cont/2]);
      EEPROM.write(cont+1,(int)((temperatura[cont/2]-(int)temperatura[cont/2])*100));
      Serial.print("GRAVANDO TEMP ");
      if (((cont/2)+1)<10){
        Serial.print("0");
      }  
      Serial.print((cont/2)+1);
      Serial.println(" NA EEPROM.");
      cont+=2;
    }
    digitalWrite(ledPin,HIGH);
    delay(250);
    digitalWrite(ledPin,LOW);
    delay(250);
    if (cont == 40){
      cont = 0;
      onG = 0;
    }
  }
// Leitura
  EstadoBotaoL = digitalRead(BotaoL);
  if (EstadoBotaoL != lastButtonStateL){
    if (EstadoBotaoL == HIGH){
      if (onL == 0){
        onL = 1;
      }else{
        onL = 0;
      }
    }
    delay(50);
  }
  lastButtonStateL = EstadoBotaoL;

  if (onL == 1){
    leitura[i] = EEPROM.read(i);
    leitura[i+1] = EEPROM.read(i+1);
    if (i!=40){
      Serial.print("LENDO TEMP ");
      if (((i/2)+1)<10){
        Serial.print("0");
      }
      Serial.print((i/2)+1);
      Serial.print(" DA EEPROM.  "); 
      Serial.print("Inteiro:");
      Serial.print((int)leitura[i]);
      Serial.print("  Decimal:");
      if ((int)leitura[i+1]<10){
        Serial.print("0");
      }
      Serial.print((int)leitura[i+1]);
      Serial.print("  |  ");
      Serial.print((int)leitura[i]);
      Serial.print(".");
      if ((int)leitura[i+1]<10){
        Serial.print("0");
      }
      Serial.print((int)leitura[i+1]);
      Serial.println("*C");
      i+=2;
    }else{
      i = 0;
      onL = 0;
    }
  }
}
