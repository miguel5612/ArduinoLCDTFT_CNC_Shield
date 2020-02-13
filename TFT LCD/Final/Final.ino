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

void loop() {
  // put your main code here, to run repeatedly:
  while (1) {
        tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        
        if(tp.x > 500 & tp.x < 600 & tp.y > 700 & tp.y < 800)
        {
          delay(50);
          if(tp.x > 500 & tp.x < 600 & tp.y > 700 & tp.y < 800) Serial.println("Arriba izquierdo");
        }
        else if(tp.x > 220 & tp.x < 300 & tp.y > 755 & tp.y < 790)
        {
          delay(50);
          if(tp.x > 220 & tp.x < 300 & tp.y > 755 & tp.y < 790) Serial.println("Abajo izquierdo");
        }
        else if(tp.x > 300 & tp.x < 400 & tp.y > 800 & tp.y < 900)
        {
          delay(50);
          if(tp.x > 300 & tp.x < 400 & tp.y > 800 & tp.y < 900) Serial.println("Izquierdo izquierdo");
        }
        else if(tp.x > 300 & tp.x < 400 & tp.y > 600 & tp.y < 700)
        {
          delay(50);
          if(tp.x > 300 & tp.x < 400 & tp.y > 600 & tp.y < 700) Serial.println("Derecho izquierdo");
        }
        else if(tp.x > 200 & tp.x < 280 & tp.y > 300 & tp.y < 380)
        {
          delay(50);
          if(tp.x > 200 & tp.x < 280 & tp.y > 300 & tp.y < 380) Serial.println("Abajo Derecho");
        }
        else if(tp.x > 500 & tp.x < 560 & tp.y > 300 & tp.y < 350)
        {
          delay(50);
          if(tp.x > 500 & tp.x < 560 & tp.y > 300 & tp.y < 350) Serial.println("Arriba Derecho");
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
        Serial.println("Punto x: " + String(tp.x) + "Punto y: " + String(tp.y)); 
  }
}
