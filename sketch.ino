#include "LiquidCrystal_I2C.h"
#include <Wire.h>

float valueOut;

LiquidCrystal_I2C lcd(0x27,  16, 2);

// Definir los pines para los segmentos del display de 7 segmentos
int a = 8;
int b = 9;
int c = 10;
int d = 11;
int e = 12;
int f = 13;
int g = A1;

void setup(){
  pinMode(A0, INPUT); 
  pinMode(2, OUTPUT); // Salida digital para el primer bit de Gray
  pinMode(3, OUTPUT); // Salida digital para el segundo bit de Gray
  pinMode(4, OUTPUT); // Salida digital para el tercer bit de Gray 
  pinMode(5, INPUT);  // Pin digital como entrada para el primer bit Exceso3
  pinMode(6, INPUT);  // Pin digital como entrada para el segundo bit Exceso3
  pinMode(7, INPUT);  // Pin digital como entrada para el tercer bit Exceso3
  pinMode(a, OUTPUT); // Pin digital como salida para el a del 7 segmentos
  pinMode(b, OUTPUT); // Pin digital como salida para el b del 7 segmentos
  pinMode(c, OUTPUT); // Pin digital como salida para el c del 7 segmentos
  pinMode(d, OUTPUT); // Pin digital como salida para el d del 7 segmentos
  pinMode(e, OUTPUT); // Pin digital como salida para el e del 7 segmentos
  pinMode(f, OUTPUT); // Pin digital como salida para el f del 7 segmentos
  pinMode(g, OUTPUT); // Pin analógico como salida para el g del 7 segmentos
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

    //Pasando el BCD a dedcimal
    int decimalNumber = BCD2 * 4 + BCD1 * 2 + BCD0; // Convertir BCD a decimal
    displayNumber(decimalNumber);

    
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

// Función para mostrar un número en el display de 7 segmentos
void displayNumber(int num) {
  switch(num) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    default:
      // Apagar todos los segmentos si el dígito no es válido
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
  }
}
