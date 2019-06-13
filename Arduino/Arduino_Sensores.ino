//Trabajo IARS - Sensores v.1
#include <Wire.h>
#include <LiquidCrystal.h>
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD

float Temperatura, Humedad, Viento, Presion, UVA;
int tmp102Address = 0x48;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() 
{
  Serial.begin(9600);
  pinMode(4 , OUTPUT);  //
  pinMode(5 , OUTPUT);  
  Wire.begin();       //se inicializa la comunicacion i2c 
  lcd.begin(16, 2);   //se inicializa el display lcd
  lcd.setCursor(0,0);
  lcd.write("I Te Hu Pre Vi U");
}

void loop()
{
  
    
    if (Serial.available())
    {
    randomSeed(analogRead(A0));
    int ID = Serial.read()- 48; //ASCII 
        
    if (ID == 1){
      Temperatura = getTemp();
      Humedad = random(10, 19) + (random(0, 999) / 1000.0);
      Presion = random(600,900) + (random(0, 999) / 1000.0); 
      Viento = random(10, 19) + (random(0, 999) / 1000.0);
      UVA = random(0, 4) + (random(0, 999) / 1000.0);
      digitalWrite(4 , HIGH);    
      delay(700);                  
      digitalWrite(4 , LOW);    
      }
    
    if (ID == 2){
      Temperatura = random(50, 60) + random(0, 999)/1000.0;
      Humedad = random(20, 29) + random(0, 999)/1000.0;
      Presion = random(600,900) + random(0, 999)/1000.0;
      Viento = random(20, 29) + random(0, 999)/1000.0;
      UVA = random(0, 4) + random(0, 999)/1000.0;
      digitalWrite(4 , HIGH);    
      delay(700);                  
      digitalWrite(4 , LOW);
      }

    if (ID == 3){
      Temperatura = random(50, 60) + random(0, 999)/1000.0;
      Humedad = random(30, 39) + random(0, 999)/1000.0;
      Presion = random(600,900) + random(0, 999)/1000.0;
      Viento = random(30, 39) + random(0, 999)/1000.0;
      UVA = random(0.5, 4) + random(0, 999)/1000.0;
      digitalWrite(4 , HIGH);    
      delay(700);                  
      digitalWrite(4 , LOW);
      }
     
    //AGREGAR CONDICION PARA VALORES DE ID FUERA DE RANGO
    
    lcd.setCursor(0, 1);
    lcd.print(ID);           //imprimir el ID en el LCD
    lcd.setCursor(2, 1);
    lcd.print(Temperatura,0);   //imprimir la temperatura en el LCD
    lcd.setCursor(5, 1);
    lcd.print(Humedad,0);       //imprimir la humedad en el LCD
    lcd.setCursor(8, 1);
    lcd.print(Presion,0);        //imprimirla presion en el LCD
    lcd.setCursor(12, 1);
    lcd.print(Viento,0);        //imprimir viento en el LCD   
    lcd.setCursor(15, 1);
    lcd.print(UVA,0);        //imprimir UVA en el LCD
   
    Serial.println(ID);
    Serial.println(Temperatura,3);
    Serial.println(Humedad,3);
    Serial.println(Presion,3); 
    Serial.println(Viento,3);
    Serial.println(UVA,3);       
    }
}

//FuncionTemperatura
float getTemp()
{
  Wire.requestFrom(tmp102Address,2); 
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 
  float Temperatura = TemperatureSum*0.0625;
  return Temperatura;
}