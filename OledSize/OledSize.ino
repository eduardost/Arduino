#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define OLED_RESET 4
Adafruit_SH110X display (OLED_RESET);

void setup()
{
  display.begin(SH1106_SWITCHAPVCC, 0x3C);  //initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();
  display.display();
  delay(2000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("HOLA MUNDO");
  display.setTextColor(BLACK, WHITE);   //'inverted' text
  display.println("HOLA MUNDO");
  display.setTextSize(2);
  display.setColor(WHITE);
  display.println("EDITRONIKX");
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);   //'inverted' text
  display.println("EDITRONIKX");
  display.display();
  delay(4000);
}

void loop()
{
  for (int i=0;i<11<i++){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(29,0);
    display.println("CONTADOR");
    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.setCursor(55,20);
    display.println(i);
    display.display();
    delay(1000);
  }
}
