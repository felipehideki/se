const int LM35 = 0;
const int Botao = 9;
const int ledPin = 13;
float temperatura[100];
float media = 0;
float soma = 0;
float maior = -40;
float menor = 140;
int ADClido = 0;
int EstadoBotao = 0;
int lastButtonState = 0;
int cont = 0;
int i = 0;
int on = 0;

void setup(){
  Serial.begin(9600);
  //analogReference(INTERNAL1V1);
  analogReference(INTERNAL);
  pinMode(Botao,INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop(){
  EstadoBotao = digitalRead(Botao);
  if (EstadoBotao != lastButtonState){
	if (EstadoBotao == HIGH){
      if (on == 0){
        on = 1;
      }else{
        on = 0;
      }
	}
    delay(50);
  }
  lastButtonState = EstadoBotao;

  if (on == 1){
    ADClido = analogRead(LM35);
    temperatura[cont] = ADClido * 0.1075268817;
    Serial.print("Temperatura = ");
    Serial.print(temperatura[cont]);
    Serial.println(" *C");
    cont++;
    digitalWrite(ledPin,HIGH);
    delay(250);
    digitalWrite(ledPin,LOW);
    delay(250);  
  }else{
    if (cont != 0){
      for (i=0;i<cont;i++){
      	soma = soma + temperatura[i];
        if (temperatura[i] >= maior){
          maior = temperatura[i];
        }
        if (temperatura[i] <= menor){
          menor = temperatura[i];
        }
        temperatura[i] = 0;
      }
      media = soma/cont;
      Serial.println("---------------------------------------------");
      Serial.print("Temperatura MED = ");
      Serial.print(media);
      Serial.println(" *C");
      Serial.print("Temperatura MAX registrada = ");
      Serial.print(maior);
      Serial.println(" *C");
      Serial.print("Temperatura MIN registrada = ");
      Serial.print(menor);
      Serial.println(" *C");
      cont = 0;
      soma = 0;
      maior = -40;
      menor = 140;
      delay(500);
    }
  }
}
