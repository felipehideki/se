#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int LM35 = 0;
const int Botao = 8;
float LCDcima = 0;
float LCDbaixo = 0;
int ADClido = 0;
int EstadoBotao = 0;
int lastButtonState = 0;
int cont = 0;
int on = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  //analogReference(INTERNAL1V1); // Arduino MEGA /Atmel2560
  analogReference(INTERNAL);
  pinMode(Botao,INPUT);
}

void loop() {
  EstadoBotao = digitalRead(Botao);
  if (EstadoBotao != lastButtonState){
    if (EstadoBotao == HIGH){
      if (on == 0){
        on = 1;
      }
    }
    delay(50);
  }
  lastButtonState = EstadoBotao;

  if (on == 1){
    ADClido = analogRead(LM35);
    if (cont == 0){
      	LCDcima = ADClido * 0.1075268817; // Constante de referência para LM35
      	lcd.setCursor(0,0);
    	lcd.print(LCDcima);
    }else{
      	LCDbaixo = LCDcima;
      	LCDcima = ADClido * 0.1075268817;
      	lcd.setCursor(0,0);
      	lcd.print(LCDcima);
      	lcd.setCursor(0,1);
      	lcd.print(LCDbaixo);
    }
    on = 0;
    cont++;
  }
}
