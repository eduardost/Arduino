#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "Banfield4098 5G";
const char* password = "Achaval2024";
String payload = "";

void connectWiFi() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  Serial.println("Connecting to WiFi..."); //print serial
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connected to WiFi");
  Serial.println("Connected to WiFi"); //print serial
  display.display();
  delay(2000);
}

void resetDisplay() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void readPrice(int x, int y, const String& stockName) {
  String httpRequestAddress = "https://finnhub.io/api/v1/quote?symbol=" + stockName + "&token=d18923hr01ql1b4miqagd18923hr01ql1b4miqb0";
  HTTPClient http;
  int httpCode;

  http.begin(httpRequestAddress);
  httpCode = http.GET();

  if (httpCode > 0) {
    DynamicJsonDocument doc(1024);
    String payload = http.getString();
    Serial.println(payload);
    deserializeJson(doc, payload);

    float previousClosePrice = doc["pc"];
    float currentPrice = doc["c"];
    float differenceInPrice = ((currentPrice - previousClosePrice) / previousClosePrice) * 100.0;

    resetDisplay();
    display.setTextSize(2);
    display.setCursor(x, y);
    display.println(stockName);
    Serial.println(stockName);//print serial

    if (differenceInPrice < 0.0) {
      display.setTextColor(SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }

    display.setTextSize(2);
    display.setCursor(x, y + 25);
    display.print(currentPrice, 2);
    Serial.print(currentPrice, 2);//print serial
    display.println(" USD");

    display.setTextSize(2);
    display.setCursor(x, y + 50);
    display.print(differenceInPrice, 2);
    display.println("%");

    display.display();
  } else {
    resetDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Error in HTTP request");
    Serial.println("Error in HTTP request");//print serial
    display.display();
  }

  http.end();
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Stock Prices Tracker");
  Serial.begin(9600);
  Serial.println("Stock Prices Tracker");//print serial
  display.display();

  connectWiFi();
}

void loop() {
  readPrice(0, 0, "AAPL");
  delay(3000);
  display.clearDisplay();
  readPrice(0, 0, "AMZN");
  delay(3000);
  display.clearDisplay();
  readPrice(0, 0, "TSLA");
  delay(3000);
  display.clearDisplay();
  readPrice(0, 0, "MSFT");
  delay(3000);
  readPrice(0, 0, "PFE");
  delay(3000);
  display.clearDisplay();
  readPrice(0, 0, "OXY");
  delay(3000);
  display.clearDisplay();
  readPrice(0, 0, "EBAY");
  delay(3000);
  display.clearDisplay();
  readPrice(0, 0, "FDX");
  delay(3000);
  display.clearDisplay();
}