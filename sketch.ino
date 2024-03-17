//Código Divisor de tensión con LDR.
#include "LiquidCrystal_I2C.h"
#include <Wire.h>

float valueOut;

LiquidCrystal_I2C lcd(0x27,  16, 2);

void setup(){
  pinMode(A0, INPUT); 
  pinMode(2, OUTPUT); // Salida digital para el primer bit de Gray
  pinMode(3, OUTPUT); // Salida digital para el segundo bit de Gray
  pinMode(4, OUTPUT); // Salida digital para el tercer bit de Gray 
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
    
    // Separar el código de Gray en bits individuales
    int bit1 = codeGray.charAt(0) - '0';
    int bit2 = codeGray.charAt(1) - '0';
    int bit3 = codeGray.charAt(2) - '0';
    
    // Pasar cada bit por salidas digitales
    digitalWrite(2, bit1);
    digitalWrite(3, bit2);
    digitalWrite(4, bit3);
    
    delay(500);                
     
    delay(1000);
    lcd.setCursor(0,1);

    lcd.print(valueOut);
    
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
