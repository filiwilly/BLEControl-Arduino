#include <SoftwareSerial.h>
#include <Keyboard.h>
#include <Mouse.h>

SoftwareSerial mySerial(8, 9); //RX,TX
String tmp;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
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
      case 5: raton_mover(data); break;
      case 6: raton_click(data); break;
      case 7: raton_scroll(data); break;
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

void raton_mover (String data){
  String sx, sy;
  for (int i = 0; i < data.length(); i++) {
    if (data.substring(i, i+1) == ";") {
      sx = data.substring(0, i);
      sy= data.substring(i+1);
      break;
    }
  }
  int x = sx.toInt();
  int y = sy.toInt();
  Mouse.move(x,y,0);
}
void raton_click (String data){
  if(data=="LEFT"){
    Mouse.click(MOUSE_LEFT);
  } else if(data=="RIGHT"){
    Mouse.click(MOUSE_RIGHT);
  }
}
void raton_scroll (String data){
  int scroll = data.toInt();
  Mouse.move(0,0,scroll);
}
