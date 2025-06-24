#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

//#define OLED_RESET 4
//Adafruit_SH110X display (OLED_RESET);

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
                         // e.g. the one with GM12864-77 written on it
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
  //display.begin(SH1106_SWITCHAPVCC, 0x3C);  //initialize with the I2C addr 0x3C (for the 128x64)
  display.begin(i2c_Address, true); // Address 0x3C default
  display.clearDisplay();
  display.display();
  delay(2000);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  display.println("HOLA MUNDO");
  display.setTextColor(SH110X_BLACK, SH110X_WHITE);   //'inverted' text
  display.println("HOLA MUNDO");
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.println("EDITRONIKX");
  display.setTextSize(2);
  display.setTextColor(SH110X_BLACK, SH110X_WHITE);   //'inverted' text
  display.println("EDITRONIKX");
  display.display();
  delay(4000);
}

void loop()
{
  for (int i=0;i<11<i++){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(29,0);
    display.println("CONTADOR");
    display.setTextSize(4);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(55,20);
    display.println(i);
    display.display();
    delay(1000);
  }
}
