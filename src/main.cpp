#include <Arduino.h>
// #include "NeoLight.h"
#include <Adafruit_NeoPixel.h>
#include "ButtonHandler.h"
#include "AnalogButtonHandler.h"

using namespace std;

#define POTENTIOMETER_PIN A0
#define NUMPIXELS 72
#define LED_PIN 2

// int initial_light_intensity = 10;

void noActionHandler()
{ /** no action **/
}

void pixelsUpdateState(); /** will be reimplemented **/
void analogUpdate(); 

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
AnalogButtonHandler analogReader(POTENTIOMETER_PIN, 50, &analogUpdate, &noActionHandler);

void setBrightness(int brig)
{
  pixels.setBrightness(brig);
}

void setup() {
    Serial.begin(115200);
    pixels.begin();
    setBrightness(255);

    Serial.println("ready and stady");
}

void loop() {
    unsigned long currentMillis = millis();

    for(int i=0; i<NUMPIXELS; i++) { 
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    }
    pixels.show();   

    delay(100);
}

void analogUpdate()
{
  int brightness = round(((1024 - analogReader.buttonState) / 4) - 1);

  if (brightness <= 0)
  {
    brightness = 1;
  }

  if (brightness >= 255)
  {
    brightness = 255;
  }

  setBrightness(brightness);
  Serial.println(brightness);
}
