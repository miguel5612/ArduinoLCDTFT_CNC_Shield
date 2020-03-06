// Programa para el control de 4 motores usando 
// dos arduinos uno y una pantalla grafica TFT LCD TOUCH


#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
// Edit MCUFRIEND_kbv.cpp:  #define SUPPORT_8347D
#include <TouchScreen.h>

const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
const int TS_LEFT=907,TS_RT=136,TS_TOP=942,TS_BOT=139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT

int prensa = 123;
int boom = 123;
int zoom = 123;
int altura = 123;

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() {
  // Inicializacion del LCD
  tft.reset();
  ID = tft.readID();
  tft.begin(ID);

  // Inicializacion del puerto serie 
  Serial.begin(9600);
  Serial.print("Tft Width: "); Serial.print(tft.width()); Serial.println(" px");
  Serial.print("Tft Height: "); Serial.print(tft.height()); Serial.println(" px");
  
  graficaInicial();
    
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1) {
        tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        //Serial.print("X: ");Serial.println(tp.x);
        //Serial.print("Y: ");Serial.println(tp.y);
        if(tp.x > 750 & tp.x < 850 & tp.y > 750 & tp.y < 850)
        {
          Serial.println("Modo prensa");  
          unEje("X");        
        }
        else if(tp.x > 700 & tp.x < 750 & tp.y > 450 & tp.y < 550)
        {
          Serial.println("Modo Boom");
          unEje("Y");
        }
        else if(tp.x > 750 & tp.x < 850 & tp.y > 250 & tp.y < 350)
        {
          Serial.println("Modo Zoom");
          unEje("Z");
        }
        else if(tp.x > 650 & tp.x < 750 & tp.y > 730 & tp.y < 850)
        {
          Serial.println("Modo Altura");
          unEje("A");
        }
        if(tp.x > 500 & tp.x < 600 & tp.y > 700 & tp.y < 800)
        {
          delay(50);
          if(tp.x > 500 & tp.x < 600 & tp.y > 700 & tp.y < 800) {Serial.println("G21G91G1X1F10");} //Serial.println("Arriba izquierdo");
          // X +
        }
        else if(tp.x > 220 & tp.x < 300 & tp.y > 755 & tp.y < 790)
        {
          delay(50);
          if(tp.x > 220 & tp.x < 300 & tp.y > 755 & tp.y < 790) {Serial.println("G21G91G1X-1F10");}//Serial.println("Abajo izquierdo");
          // X -
        }
        else if(tp.x > 300 & tp.x < 400 & tp.y > 800 & tp.y < 900)
        {
          delay(50);
          if(tp.x > 300 & tp.x < 400 & tp.y > 800 & tp.y < 900) {Serial.println("G21G91G1Y1F10");}//Serial.println("Izquierdo izquierdo");
          // Y + 
        }
        else if(tp.x > 415 & tp.x < 450 & tp.y > 600 & tp.y < 680)
        {
          Serial.println("X: " + String(tp.x) + " Y:" + String(tp.y));  
          delay(50);
          if(tp.x > 415 & tp.x < 450 & tp.y > 600 & tp.y < 680) {Serial.println("G21G91G1Y-1F10");}//Serial.println("Derecho izquierdo");
          // Y -
        }
        else if(tp.x > 200 & tp.x < 280 & tp.y > 300 & tp.y < 380)
        {
          delay(50);
          if(tp.x > 200 & tp.x < 280 & tp.y > 300 & tp.y < 380) {Serial.println("G21G91G1Z1F10");}//Serial.println("Abajo Derecho"); 
          // Z +
        }
        else if(tp.x > 500 & tp.x < 560 & tp.y > 300 & tp.y < 350)
        {
          delay(50);
          if(tp.x > 500 & tp.x < 560 & tp.y > 300 & tp.y < 350) {Serial.println("G21G91G1Z-1F10");}//Serial.println("Arriba Derecho");
          // Z - 
        }
        else if(tp.x > 380 & tp.x < 490 & tp.y > 400 & tp.y < 510)
        {
          delay(50);
          if(tp.x > 380 & tp.x < 490 & tp.y > 400 & tp.y < 510) Serial.println("Izquierdo Derecho");
        }
        else if(tp.x > 380 & tp.x < 450 & tp.y > 200 & tp.y < 300)
        {
          delay(50);
          if(tp.x > 380 & tp.x < 450 & tp.y > 200 & tp.y < 300) Serial.println("Derecho Derecho");
        }
        //Serial.println("Punto x: " + String(tp.x) + "Punto y: " + String(tp.y)); 
  }
}





void unEje(String eje)
{
  tft.fillScreen(BLACK);
  
  tft.setRotation(3);
  tft.setCursor(10, 50);
  tft.setTextSize(4);
  tft.print(eje);
  tft.setRotation(4);

  BOXSIZE = tft.width() / 4;

  tft.setRotation(3);
  
  tft.drawRect(20, 100, BOXSIZE, BOXSIZE, WHITE);
  tft.setCursor(40, 120);
  tft.print("<");
  
  tft.drawRect(100, 100, BOXSIZE, BOXSIZE, WHITE);
  tft.setCursor(120, 120);
  tft.print("+");

  
  tft.drawRect(200, 100, BOXSIZE, BOXSIZE, WHITE);
  
  tft.setCursor(220, 120);
  tft.print("-");
  
  
  
  while(1)
  {
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    Serial.print("X: ");Serial.println(tp.x);
    Serial.print("Y: ");Serial.println(tp.y);
   if(tp.x > 500 & tp.x < 590 & tp.y > 780 & tp.y < 830)
    {
      Serial.println("Volver atras");          
      delay(400);
      graficaInicial();
      tft.setTextSize(1);
      break;
    }
    if(tp.x > 450 & tp.x < 550 & tp.y > 580 & tp.y < 640)
    {
      Serial.println("G21G91G1" + eje + "+" + "1F10");
    }
    if(tp.x > 450 & tp.x < 550 & tp.y > 300 & tp.y < 450)
    {
      Serial.println("G21G91G1" + eje + "-" + "1F10");
    }
  }
}


void graficaInicial()
{
  BOXSIZE = tft.width() / 7;
  tft.fillScreen(BLACK);

  //Boton ir motor 1
  tft.setRotation(3);
  tft.setCursor(10, 50);
  tft.setTextSize(1);
  tft.print("Prensa: ");
  tft.drawRect(60, 35, BOXSIZE, BOXSIZE, WHITE);
  
  tft.setCursor(120, 50);
  tft.drawRect(160, 35, BOXSIZE, BOXSIZE, WHITE);
  tft.print("Boom: ");

  tft.setCursor(220, 50);
  tft.print("Zoom: ");
  tft.drawRect(260, 35, BOXSIZE, BOXSIZE, WHITE);
  
  tft.setCursor(10, 80);
  tft.print("Altura: ");
  tft.drawRect(60, 65, BOXSIZE, BOXSIZE, WHITE);
  
  tft.setRotation(0);


  //Estadisticas
  tft.setRotation(3);
  tft.setCursor(65, 50);
  tft.print(prensa);

  tft.setCursor(165, 50);
  tft.print(boom);

  tft.setCursor(265, 50);
  tft.print(zoom);

  tft.setCursor(65, 80);
  tft.print(altura);
  
  tft.setRotation(0);


  
    // Boton Izquierdo inferior
    tft.drawRect(200, 225, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(200, 225, BOXSIZE, BOXSIZE, RED);

    tft.setRotation(1);
    tft.setCursor(235, 20);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);

    // Boton Izquierdo superior
    tft.drawRect(120, 225, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(120, 225, BOXSIZE, BOXSIZE, RED);
    
    tft.setRotation(3);
    tft.setCursor(70, 130);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);
        
    // Boton Izquierdo izquierdo
    tft.drawRect(160, 270, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(160, 270, BOXSIZE, BOXSIZE, GREEN);

    tft.setRotation(2);
    tft.setCursor(55, 30);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);
    
    // Boton Izquierdo derecho
    tft.drawRect(160, 180, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(160, 180, BOXSIZE, BOXSIZE, GREEN);
    
    tft.setRotation(4);
    tft.setCursor(170, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);
    
    // Boton derecho inferior
    tft.drawRect(200, 60, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(200, 60, BOXSIZE, BOXSIZE, CYAN);
    
    tft.setRotation(1);
    tft.setCursor(70, 20);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);
    
    // Boton derecho superior
    tft.drawRect(120, 60, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(120, 60, BOXSIZE, BOXSIZE, CYAN);

    tft.setRotation(3);
    tft.setCursor(235, 130);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);
    
    // Boton derecho izquierdo
    tft.drawRect(160, 106, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(160, 106, BOXSIZE, BOXSIZE, MAGENTA);
    
    tft.setRotation(2);
    tft.setCursor(55, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);
    
    // Boton derecho derecho
    tft.drawRect(160, 20, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(160, 20, BOXSIZE, BOXSIZE, MAGENTA);

    tft.setRotation(4);
    tft.setCursor(170, 30);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("^");
    tft.setRotation(0);
    

    
    tft.setRotation(3);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(YELLOW, BLACK);
    tft.println(F("Control GRBL de 4 motores"));
    tft.setTextColor(BLACK, YELLOW);
    tft.setTextSize(1);
    tft.println(F("Desarrollado en CNC Plametza y onmotica"));
    tft.println(F("github.com/miguel5612/ArduinoLCDTFT_CNC_Shield"));
}
