#include "LiquidCrystal_I2C.h"
#include <Wire.h>

float valueOut;

LiquidCrystal_I2C lcd(0x27,  16, 2);

void setup(){
  pinMode(A0, INPUT); 
  pinMode(2, OUTPUT); // Salida digital para el primer bit de Gray
  pinMode(3, OUTPUT); // Salida digital para el segundo bit de Gray
  pinMode(4, OUTPUT); // Salida digital para el tercer bit de Gray 
  pinMode(5, INPUT);  // Pin digital como entrada para el primer bit de Gray
  pinMode(6, INPUT);  // Pin digital como entrada para el segundo bit de Gray
  pinMode(7, INPUT);  // Pin digital como entrada para el tercer bit de Gray
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
    int bit0 = codeGray.charAt(0) - '0';
    int bit1 = codeGray.charAt(1) - '0';
    int bit2 = codeGray.charAt(2) - '0';
    
    // Pasar cada bit por salidas digitales
    digitalWrite(2, bit0);
    digitalWrite(3, bit1);
    digitalWrite(4, bit2);
    
    // Leer los bits de salida y mostrarlos en el puerto serie y en la pantalla LCD
    int BitE0 = digitalRead(5);//C
    int BitE1 = digitalRead(6);//B
    int BitE2 = digitalRead(7);//A

    //Pasar a de Exceso 3 circular a BCD
    int BCD0 = (!BitE0);
    int BCD1 = (!BitE1 && BitE0) || (BitE1 && !BitE0);
    int BCD2 = (!BitE2 && !BitE1) || (!BitE2 && !BitE0) || (BitE2 && BitE1 && BitE0);

    
    // Mostrar los bits de salida en el puerto serie
    /*Serial.print("Bits de salida leídos: ");
    Serial.print(BitE2);
    Serial.print(BitE1);
    Serial.println(BitE0);*/
    
    // Mostrar los bits de salida en la pantalla LCD
    lcd.setCursor(0, 0);
    lcd.print("Exc3:");
    lcd.print(BitE2);
    lcd.print(BitE1);
    lcd.print(BitE0);

    lcd.setCursor(0,1);
    lcd.print("BCD: ");
    lcd.print(BCD2);
    lcd.print(BCD1);
    lcd.print(BCD0);
    
    delay(500);                
     
    delay(1000);
    lcd.clear(); 
}

// Función para pasar el decimal a código de Gray
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

