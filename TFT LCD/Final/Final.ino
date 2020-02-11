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

  
    // Boton Izquierdo inferior
    tft.drawRect(200, 225, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(200, 225, BOXSIZE, BOXSIZE, RED);
    
    // Boton Izquierdo superior
    tft.drawRect(120, 225, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(120, 225, BOXSIZE, BOXSIZE, RED);
    // Boton Izquierdo izquierdo
    tft.drawRect(160, 270, BOXSIZE, BOXSIZE, WHITE);
    //tft.fillRect(160, 270, BOXSIZE, BOXSIZE, GREEN);

    tft.setRotation(3);
    tft.setCursor(30, 140);
    tft.setTextColor(WHITE);
    tft.print("V");
    tft.setRotation(0);
    
    // Boton Izquierdo derecho
    tft.drawRect(160, 180, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(160, 180, BOXSIZE, BOXSIZE, GREEN);

    // Boton derecho inferior
    tft.drawRect(200, 60, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(200, 60, BOXSIZE, BOXSIZE, CYAN);
    // Boton derecho superior
    tft.drawRect(120, 60, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(120, 60, BOXSIZE, BOXSIZE, CYAN);
    // Boton derecho izquierdo
    tft.drawRect(160, 106, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(160, 106, BOXSIZE, BOXSIZE, MAGENTA);
    // Boton derecho derecho
    tft.drawRect(160, 20, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(160, 20, BOXSIZE, BOXSIZE, MAGENTA);

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

}
