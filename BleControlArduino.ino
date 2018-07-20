#include <SoftwareSerial.h>
#include <Keyboard.h>

SoftwareSerial mySerial(8, 9); //RX,TX
String tmp;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  mySerial.begin(9600);
  mySerial.write("AT");
}

void loop() {
  //Leer puerto serie
  while (mySerial.available() > 0)  {
    char inChar = mySerial.read();
    tmp += inChar;
    delay(10);
  }

  if (tmp.length() > 0) {
    int longitud = tmp.length();
    String codigo = tmp.substring(0, 1);
    int cod = codigo.toInt();
    String data = tmp.substring(1, longitud);
    switch (cod) {
      case 3: voz(data,longitud); break;
      case 4: teclado(data); break;
    }
    tmp = "";
  }
  //Código para configurar el modulo HM
  //por medio de comandos
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void voz (String data, int longitud) {
  byte arrayb[longitud];
    data.getBytes(arrayb, longitud);
    for (int i = 0; i < longitud; i++) {
      switch (arrayb[i]) {
        case 161: Keyboard.write(97); break;
        case 169: Keyboard.write(101); break;
        case 173: Keyboard.write(105); break;
        case 179: Keyboard.write(111); break;
        case 186: Keyboard.write(117); break;
        case 195: Keyboard.write(39); delay(10); break;
        default: Keyboard.write(arrayb[i]); break;
      }
    }
}

void teclado (String data){
  Keyboard.write(data.toInt());
}

