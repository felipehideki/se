#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int LM35 = 0;
const int botaoUP = 6;
const int botaoDOWN = 7;
const int botaoENTER = 8;
const int botaoBACK = 9;
int ADClido = 0;
int estadoBotaoUP = 0;
int estadoBotaoDOWN = 0;
int estadoBotaoENTER = 0;
int estadoBotaoBACK = 0;
int lastButtonStateUP = 0;
int lastButtonStateDOWN = 0;
int lastButtonStateENTER = 0;
int lastButtonStateBACK = 0;
int posCIMA = 1;
int selectedLine = 0;
int onUP = 0;
int onDOWN = 0;
int onENTER = 0;
int onBACK = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(7,0);
  lcd.print("*");
  //analogReference(INTERNAL1V1); // Arduino MEGA /Atmel2560
  analogReference(INTERNAL);
  pinMode(botaoUP,INPUT);
  pinMode(botaoDOWN,INPUT);
  pinMode(botaoENTER,INPUT);
  pinMode(botaoBACK,INPUT);
}

void loop() {
  estadoBotaoUP = digitalRead(botaoUP);
  estadoBotaoDOWN = digitalRead(botaoDOWN);
  estadoBotaoENTER = digitalRead(botaoENTER);
  estadoBotaoBACK = digitalRead(botaoBACK);

// MENU  
  if (onENTER == 0){
    lcd.setCursor(0,0);
    if (posCIMA == 1){
      lcd.print("OPCAO 1");
      lcd.setCursor(0,1);
      lcd.print("OPCAO 2");
    }
    if (posCIMA == 2){
      lcd.print("OPCAO 2");
      lcd.setCursor(0,1);
      lcd.print("OPCAO 3");
    }	
    if (posCIMA == 3){
      lcd.print("OPCAO 3");
      lcd.setCursor(0,1);
      lcd.print("OPCAO 4");
    }
    if (posCIMA == 4){
      lcd.print("OPCAO 4");
      lcd.setCursor(0,1);
      lcd.print("OPCAO 5");
    }
  }
  
// BOTAO UP
  if (estadoBotaoUP != lastButtonStateUP){
    if (estadoBotaoUP == HIGH){
      if (onUP == 0){
        onUP = 1;
      }
    }
    delay(50);
  }
  lastButtonStateUP = estadoBotaoUP;

  if (onUP == 1){
    if (onENTER == 0){
      if (selectedLine == 0 && posCIMA != 1){
        posCIMA--;
      }
      if (selectedLine == 1){
        selectedLine = 0;
      }
      lcd.setCursor(7,0);
      lcd.print("*");
      lcd.setCursor(7,1);
      lcd.print(" ");
    }
    onUP = 0;
  }  
  
// BOTAO DOWN  
  if (estadoBotaoDOWN != lastButtonStateDOWN){
    if (estadoBotaoDOWN == HIGH){
      if (onDOWN == 0){
        onDOWN = 1;
      }
    }
    delay(50);
  }
  lastButtonStateDOWN = estadoBotaoDOWN;
  
  if (onDOWN == 1){
    if (onENTER == 0){
      if (selectedLine == 1 && posCIMA != 4){
        posCIMA++;
      }
      if (selectedLine == 0){
        selectedLine = 1;
      }
      lcd.setCursor(7,0);
      lcd.print("  ");
      lcd.setCursor(7,1);
      lcd.print("*");
    }
    onDOWN = 0;
  }

// BOTAO ENTER
  if (estadoBotaoENTER != lastButtonStateENTER){
    if (estadoBotaoENTER == HIGH){
      if (onENTER == 0){
        onENTER = 1;
      }
    }
    delay(50);
  }
  lastButtonStateENTER = estadoBotaoENTER;
  
  if (onENTER == 1){
    lcd.setCursor(0,0);
    if (posCIMA == 1){
      if (selectedLine == 0){
    	lcd.print("A opcao 1 foi");
      }else{
    	lcd.print("A opcao 2 foi");
      }
    }
    if (posCIMA == 2){
      if (selectedLine == 0){
    	lcd.print("A opcao 2 foi");
      }else{
    	lcd.print("A opcao 3 foi");
      }
    }
    if (posCIMA == 3){
      if (selectedLine == 0){
    	lcd.print("A opcao 3 foi");
      }else{
    	lcd.print("A opcao 4 foi");
      }
    }
    if (posCIMA == 4){
      if (selectedLine == 0){
    	lcd.print("A opcao 4 foi");
      }else{
    	lcd.print("A opcao 5 foi");
      }
    }
    lcd.setCursor(0,1);
    lcd.print("selecionada.");
  }

// BOTAO BACK
  if (estadoBotaoBACK != lastButtonStateBACK){
    if (estadoBotaoBACK == HIGH){
      if (onBACK == 0){
        onBACK = 1;
      }
    }
    delay(50);
  }
  lastButtonStateBACK = estadoBotaoBACK;

  if (onBACK == 1){
    if (onENTER == 1){
      lcd.setCursor(0,0);
      if (selectedLine == 0){
        lcd.print("       *       ");
        lcd.setCursor(0,1);
        lcd.print("               ");
      }else{
        lcd.print("               ");
        lcd.setCursor(0,1);
        lcd.print("       *       ");
      }
    }
    onBACK = 0;
    onENTER = 0;
  }
}
