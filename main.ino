/* ESP32 Projeto Cotação */

// Incluindo bibliotecas necessárias
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

// Endereçando o LCD
LiquidCrystal_I2C lcd(0X27, 16, 2);

// Variáveis globais
const char* ssid = "Wokwi-GUEST";
const char* password = "";

void setup() {
  // Configurando o LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Conectando...");
  lcd.print("Conectando...");

  // Esperando efetuar a conexão
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(" .");
    delay(500);
  }
  // Conexão efetuada
  Serial.println("");
  Serial.println("Conexão WiFi com sucesso!!");
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Conectado!");

}

void loop(){
  // Fazendo a requisição ao endpoint
  HTTPClient http;
  http.begin("https://economia.awesomeapi.com.br/json/last/USD-BRL,EUR-BRL,GBP-BRL,CAD-BRL");
  int responseStatus = http.GET();
  Serial.println("");
  Serial.print("O status da requisição é: ");
  Serial.println(responseStatus);

  // Exibindo a resposta da requisição no console
  if(responseStatus == 200){
    String responseBody = http.getString();
    // Encontrando os valores bid
    int bloco;
    int posInicio;
    int posFim;
    String valorBid;
    String chave = "\"bid\":\"";

    // bid USD
    bloco = responseBody.indexOf("USDBRL");
    posInicio = responseBody.indexOf(chave, bloco);
    posInicio += chave.length(); // Avançando até o valor do bid buscado
    posFim = responseBody.indexOf("\"", posInicio);
    valorBid = responseBody.substring(posInicio, posFim);
    Serial.print("O valor do USD-BRL é: R$ ");
    Serial.println(valorBid);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("USD em BRL");
    lcd.setCursor(1,1);
    lcd.print("R$");
    lcd.setCursor(4,1);
    lcd.print(valorBid);
    // Ag. 5 seg
    delay(5000);
    
    // bid EUR
    bloco = responseBody.indexOf("EURBRL");
    posInicio = responseBody.indexOf(chave, bloco);
    posInicio += chave.length(); // Avançando até o valor do bid buscado
    posFim = responseBody.indexOf("\"", posInicio);
    valorBid = responseBody.substring(posInicio, posFim);
    Serial.print("O valor do EUR-BRL é: R$ ");
    Serial.println(valorBid);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("EUR em BRL");
    lcd.setCursor(1,1);
    lcd.print("R$");
    lcd.setCursor(4,1);
    lcd.print(valorBid);
    // Ag. 5 seg
    delay(5000);

    // bid GBP
    bloco = responseBody.indexOf("GBPBRL");
    posInicio = responseBody.indexOf(chave, bloco);
    posInicio += chave.length(); // Avançando até o valor do bid buscado
    posFim = responseBody.indexOf("\"", posInicio);
    valorBid = responseBody.substring(posInicio, posFim);
    Serial.print("O valor do GBP-BRL é: R$ ");
    Serial.println(valorBid);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("GBP em BRL");
    lcd.setCursor(1,1);
    lcd.print("R$");
    lcd.setCursor(4,1);
    lcd.print(valorBid);
    // Ag. 5 seg
    delay(5000);

    // bid CAD
    bloco = responseBody.indexOf("CADBRL");
    posInicio = responseBody.indexOf(chave, bloco);
    posInicio += chave.length(); // Avançando até o valor do bid buscado
    posFim = responseBody.indexOf("\"", posInicio);
    valorBid = responseBody.substring(posInicio, posFim);
    Serial.print("O valor do CAD-BRL é: R$ ");
    Serial.println(valorBid);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("CAD em BRL");
    lcd.setCursor(1,1);
    lcd.print("R$");
    lcd.setCursor(4,1);
    lcd.print(valorBid);
    // Finaliza a requisição
    http.end();
    // Ag. 5 seg
    delay(5000);
    
  }
  else{
    Serial.println("Nenhuma informação foi recuperada do endpoint.");
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Requisição");
    lcd.setCursor(1,1);
    lcd.print("falha :( ");
    http.end(); // Finaliza a requisição
    delay(5000);
  }

}