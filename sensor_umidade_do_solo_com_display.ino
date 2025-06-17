#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensor = A0; // pin analogico A0 declarado como sensor de umidade
int led_vermelho = 7; // pin 7 declarado como led
int led_verde = 9; // pin 9 declarado como led
int valor_max =1016; // declara 1016 como valor maximo de captação do sensor
int Valor_min = 0; // declara 0 como valor minimo de captação do sensor
int valor_sensor = 0; // declara uma variavel para a coleta de dados
int porcent_sensor = 0; // declara uma variavel para aplicar a porcentagem

void setup() {
  
  // faz o setup do codigo.
  Serial.begin(9600);
  lcd.init(); // inicia o LCD
  lcd.backlight();
  lcd.leftToRight();
  lcd.setCursor(3, 0);
  lcd.print("Monitor de");
  lcd.setCursor(5, 7);
  lcd.print("umidade");
  delay(4000);
  pinMode(sensor, INPUT); // sensor vai ser entrada
  pinMode(led_vermelho, OUTPUT); // led vai ser saida
  pinMode(led_verde, OUTPUT); // led vai ser saida
}

void loop() {
  valor_sensor = analogRead(sensor); // Lê o valor analógico do sensor

  porcent_sensor = map(valor_sensor, Valor_min, valor_max, 100, 0); // Mapeia para 0-100%

  // inicia o diagrama de blocos com 3 possibilidades (seco, ideal,supersaturado)
  if (valor_sensor <203) {
     digitalWrite(led_vermelho, HIGH);
   	 digitalWrite(led_verde, LOW);
   	 lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("supersaturado");
     lcd.setCursor(0, 1);
     lcd.print(porcent_sensor);
     lcd.print("%");
     delay(4000);
    
   }
   else if(valor_sensor >203 && valor_sensor <609) {
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_vermelho, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ideal");
  lcd.setCursor(0, 1);
  lcd.print(porcent_sensor);
  lcd.print("%");
  delay(4000);
     
 }
   else{
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Seco:");
  lcd.setCursor(0, 1);
  lcd.print(porcent_sensor);
  lcd.print("%");
  delay(4000);
  }
}