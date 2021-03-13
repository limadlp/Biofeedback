#define sensorPin A3 //2
#define potenciometro A2 //3 
#define azul 2 //2
#define verde 1 //1
#define vermelho 0 //0
short int sensorValue = 0; // variável inteiro igual a zero
short int ganho = 0;
short int alpha = 0;
 
short int cor = 0;
short int antecor = 9;
 
void setup()
{
   //Serial.begin(9600);
   //pinMode(sensorPin, INPUT);
   //pinMode(potenciometro, INPUT);
   pinMode(azul, OUTPUT);
   pinMode(verde, OUTPUT);
   pinMode(vermelho, OUTPUT);

   //analogReference(DEFAULT);
}
 
//Funções responsáveis por executar o brilho selecionado
void vermelhoFuncao(){
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
}
void azulFuncao(){
  digitalWrite(azul, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}
void verdeFuncao(){
  digitalWrite(azul, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, LOW);
}
void amareloFuncao(){
  analogWrite(azul, 0);
  analogWrite(verde, 50);
  analogWrite(vermelho, 255);
}
void brancoFuncao(){
  digitalWrite(azul, HIGH);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, HIGH);
}
void oceanFuncao(){
  analogWrite(azul, 255);
  analogWrite(verde, 125);
  analogWrite(vermelho, 0);
}
void violetaFuncao(){
  analogWrite(azul, 255);
  analogWrite(verde, 0);
  analogWrite(vermelho, 125);
}
void raspberryFuncao(){
  analogWrite(azul, 125);
  analogWrite(verde, 0);
  analogWrite(vermelho, 255);
}




 
void loop()
{
  
  sensorValue = analogRead(sensorPin);
  //ganho = -analogRead(potenciometro)/4;
  
  
//  Serial.println(sensorValue);

  /*
  if(Serial.available()){
    cor = Serial.readString();
    Serial.println(cor);
  }
  */

  /*
  if (sensorValue < 200 + alpha + ganho){
    cor = 1;
    //brancoFuncao();
  }
   else if (sensorValue >= 200 + alpha + ganho && sensorValue < 240 + alpha + ganho){
    cor = 2;
    //azulFuncao();
  } 
  else if (sensorValue >= 240 +alpha + ganho && sensorValue < 280 + alpha+  ganho){
    cor = 3;
    //verdeFuncao();
  }
  else if (sensorValue >= 280 + alpha + ganho && sensorValue < 320 +alpha + ganho){
    cor = 4;
    //amareloFuncao();
  }
  else if (sensorValue <= 320 +alpha  + ganho && sensorValue < 380 + alpha + ganho){
    cor = 5;
    //vermelhoFuncao();
  }
  else if (sensorValue >= 380 + alpha + ganho){
    cor = 6;
    //roxoFuncao();
  }
*/  


  if (sensorValue < 40 + alpha + ganho){
    cor = 1;
    //brancoFuncao();
  }
   else if (sensorValue >= 40 + alpha + ganho && sensorValue < 80 + alpha + ganho){
    cor = 2;
    //azulFuncao();
  } 
  else if (sensorValue >= 80 +alpha + ganho && sensorValue < 120 + alpha+  ganho){
    cor = 3;
    //verdeFuncao();
  }
  else if (sensorValue >= 120 + alpha + ganho && sensorValue < 160 +alpha + ganho){
    cor = 4;
    //amareloFuncao();
  }
  else if (sensorValue >= 160 +alpha  + ganho && sensorValue < 210 + alpha + ganho){
    cor = 5;
    //vermelhoFuncao();
  }
  else if (sensorValue >= 210 +alpha  + ganho && sensorValue < 250 + alpha + ganho){
    cor = 6;
    //vermelhoFuncao();
  }
  else if (sensorValue >= 250 +alpha  + ganho && sensorValue < 300 + alpha + ganho){
    cor = 7;
    //vermelhoFuncao();
  }
  else if (sensorValue >= 300 + alpha + ganho){
    cor = 8;
    //roxoFuncao();
  }

  
 
 
  if(cor == 1 && cor != antecor){
    brancoFuncao();
  }
  if(cor == 2 && cor != antecor){
    azulFuncao();
  }
  if(cor == 3 && cor != antecor){
    verdeFuncao();
  }
  if(cor == 4 && cor != antecor){
    amareloFuncao();
  }
  if(cor == 5 && cor != antecor){
    vermelhoFuncao();
  }
  if(cor == 6 && cor != antecor){
    raspberryFuncao();
  }
  if(cor == 7 && cor != antecor){
    violetaFuncao();
  }
  

  antecor = cor;
  
  delay(200);
}
