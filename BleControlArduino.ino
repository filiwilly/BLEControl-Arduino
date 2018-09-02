#include <SoftwareSerial.h>
#include <Keyboard.h>
#include <Mouse.h>

SoftwareSerial mySerial(8, 9); //RX,TX
String tmp, sx, sy;

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
      case 1: multimedia(data); break;
      case 2: gamepad(data, longitud); break;
      case 3: voz(data,longitud); break;
      case 4: teclado(data); break;
      case 5: raton_mover(data); break;
      case 6: raton_click(data); break;
      case 7: raton_scroll(data); break;
      case 8: Serial.println(data); break;
    }
    tmp = "";
  }
  //Código para configurar el modulo HM
  //por medio de comandos
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void multimedia (String data){
  switch (data.toInt()){
    case 11: Keyboard.press(KEY_LEFT_CTRL); delay(10); Keyboard.press(KEY_UP_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 12: Keyboard.press(KEY_LEFT_CTRL); delay(10); Keyboard.press(KEY_DOWN_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 13: Keyboard.press(32); delay(100); Keyboard.releaseAll(); break;
    case 14: Keyboard.press(KEY_LEFT_CTRL); delay(10); Keyboard.press(KEY_RIGHT_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 15: Keyboard.press(KEY_LEFT_CTRL); delay(10); Keyboard.press(KEY_LEFT_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 16: Keyboard.press(KEY_LEFT_CTRL); delay(10); Keyboard.press(112); delay(100); Keyboard.releaseAll(); break;
    case 17: Keyboard.press(KEY_F9); delay(100); Keyboard.releaseAll(); break;
    case 18: Keyboard.press(KEY_F8); delay(100); Keyboard.releaseAll(); break;
    case 19: Keyboard.press(KEY_UP_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 20: Keyboard.press(KEY_DOWN_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 21: Keyboard.press(KEY_RIGHT_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 22: Keyboard.press(KEY_LEFT_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 23: Keyboard.press(108); delay(100); Keyboard.releaseAll(); break;
    case 24: Keyboard.press(106); delay(100); Keyboard.releaseAll(); break;
    case 25: Keyboard.press(KEY_LEFT_ALT); delay(10); Keyboard.press(KEY_RIGHT_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 26: Keyboard.press(KEY_LEFT_ALT); delay(10); Keyboard.press(KEY_LEFT_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 27: Keyboard.press(KEY_LEFT_CTRL); delay(10); Keyboard.press(98); delay(100); Keyboard.releaseAll(); break;
    case 28: Keyboard.press(KEY_LEFT_CTRL); delay(10); Keyboard.press(102); delay(100); Keyboard.releaseAll(); break;
    case 29: Keyboard.press(KEY_LEFT_SHIFT); delay(10); Keyboard.press(110); delay(100); Keyboard.releaseAll(); break;
    case 30: Keyboard.press(KEY_LEFT_SHIFT); delay(10); Keyboard.press(112); delay(100); Keyboard.releaseAll(); break;
    case 31: Keyboard.press(110); delay(100); Keyboard.releaseAll(); break;
    case 32: Keyboard.press(112); delay(100); Keyboard.releaseAll(); break;
    case 33: Keyboard.press(KEY_LEFT_ALT); delay(10); Keyboard.press(KEY_UP_ARROW); delay(100); Keyboard.releaseAll(); break;
    case 34: Keyboard.press(KEY_LEFT_ALT); delay(10); Keyboard.press(KEY_DOWN_ARROW); delay(100); Keyboard.releaseAll(); break;
  }
}

void gamepad(String data, int longitud) {
  String codigo = data.substring(0,2);
  String datos = data.substring(2,longitud);
  switch (codigo.toInt()) {
    case 11: Keyboard.press(datos.charAt(0)); delay(10);break;
    case 12: Keyboard.release(datos.charAt(0)); delay(10); break;
    case 13: Keyboard.press(datos.toInt()); delay(10);break;
    case 14: Keyboard.release(datos.toInt()); delay(10);break;
    case 15: Keyboard.press(KEY_LEFT_ARROW); delay(10); Keyboard.press(KEY_UP_ARROW);break;
    case 16: Keyboard.release(KEY_UP_ARROW); delay(10); Keyboard.release(KEY_LEFT_ARROW);break;
    case 17: Keyboard.press(KEY_RIGHT_ARROW); delay(10); Keyboard.press(KEY_UP_ARROW);break;
    case 18: Keyboard.release(KEY_RIGHT_ARROW); delay(10); Keyboard.release(KEY_UP_ARROW);break;
    case 19: Keyboard.press(KEY_LEFT_ARROW); delay(10); Keyboard.press(KEY_DOWN_ARROW);break;
    case 20: Keyboard.release(KEY_LEFT_ARROW); delay(10); Keyboard.release(KEY_DOWN_ARROW);break;
    case 21: Keyboard.press(KEY_RIGHT_ARROW); delay(10); Keyboard.press(KEY_DOWN_ARROW);break;
    case 22: Keyboard.release(KEY_RIGHT_ARROW); delay(10); Keyboard.release(KEY_DOWN_ARROW);break;
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
  String codigo = data.substring(0,1);
  String datos = data.substring(1,data.length());
  int x, y;
  switch(codigo.toInt()){
    case 1: dividir(datos); x = sx.toInt(); y = sy.toInt(); Mouse.move(x,y,0); break;
    case 2: Mouse.press(MOUSE_LEFT); break;
    case 3: Mouse.release(MOUSE_LEFT); break;
  }
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

void dividir(String cadena){
  for (int i = 0; i < cadena.length(); i++) {
    if (cadena.substring(i, i+1) == ";") {
      sx = cadena.substring(0, i);
      sy= cadena.substring(i+1);
      break;
    }
  }
}
