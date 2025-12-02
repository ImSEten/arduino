#include <FastLED.h>

#define LED_PIN   2
#define NUM_LEDS  30

bool start = true;

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); // LED初始化引脚为输出模式
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (start) {
    for (int i = 0; i <= NUM_LEDS - 1; i++) {
      leds[i] = CRGB(255, 150, 40);
    }
    for (int i = 0; i <= 255; i++) {
      FastLED.setBrightness(i);
      FastLED.delay(20);
      FastLED.show();
    }
    start = false;
  } else {
    FastLED.delay(5000);
  }
}
