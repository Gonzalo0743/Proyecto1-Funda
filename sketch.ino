//Código Divisor de tensión con LDR.
#include "LiquidCrystal_I2C.h"
#include <Wire.h>

float valueOut;

LiquidCrystal_I2C lcd(0x27,  16, 2);

void setup(){
  pinMode(A0,INPUT);                 
  //pinMode(4,OUTPUT);               
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();               
} 

void loop(){
    
    int valorLDR = analogRead(A0) - 8;
    valueOut = (7. * valorLDR)/1007;
    Serial.println(valueOut);

    String codeGray = toGray(valueOut);
    Serial.println(codeGray);

    
    delay(500);                
     
    /*if( valorLDR <= 400 ) 
    {
      //digitalWrite(4, HIGH);
      //Serial.print("LED ON ");
      Serial.println(valorLDR);
      delay(500);
    }
  
    else
    {
      //digitalWrite(4, LOW);
      //Serial.println("LED OFF");
      Serial.println(valorLDR);
      delay(500);
    }*/

    delay(1000);
    lcd.setCursor(0,1);

    lcd.print(valueOut);
    //Colocar en otro lado de la LDR
    /*lcd.setCursor(0,1);
    lcd.print("Prueba");*/
    delay(1000);
    lcd.clear(); 
  }

//Funcion para pasar el decimal a codigo de gray
String toGray(int value) {
  // Implementación de la conversión a código Gray en formato binario
  int gray = (value >> 1) ^ value;

  // Convierte el valor a una cadena binaria de 3 bits
  String binary = String(gray, BIN);

  // Asegura que la cadena tenga siempre 3 bits completos
  while (binary.length() < 3) {
    binary = "0" + binary;
  }

  return binary;
} 