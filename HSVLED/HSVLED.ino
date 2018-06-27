#include <FastLED.h>
#include <ResponsiveAnalogRead.h>
#include <AnalogSmooth.h>

#define NUM_LEDS 20
#define DATA_PIN 5
#define CLOCK_PIN 6

int const POT_PIN_R = A1;
int const POT_PIN_G = A2;
int const POT_PIN_B = A3;

ResponsiveAnalogRead AR(POT_PIN_R, true, 0.001);
ResponsiveAnalogRead AG(POT_PIN_G, true, 0.001);
ResponsiveAnalogRead AB(POT_PIN_B, true, 0.001);

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB, DATA_RATE_MHZ(60)>(leds, NUM_LEDS);
}

void loop()
{  
  int H = getPot(AR);
  int S = getPot(AG);
  int V = getPot(AB);

  FastLED.clear();
  
  CRGB color = CHSV(H, S, V);
  fill_solid(leds, NUM_LEDS, color);
  
  FastLED.show();
}

int getPot(ResponsiveAnalogRead analog)
{
  analog.update();
  int value = map(analog.getValue(), 1023, 0, 0, 255);
  
  return value;
}

