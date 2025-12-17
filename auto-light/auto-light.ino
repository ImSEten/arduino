#include <FastLED.h>

#define PERSON_PIN 2
#define LED_PIN   3
#define NUM_LEDS  30

bool ledStatus = false;
int personValue = 0;

CRGB leds[NUM_LEDS];

void set_led_color() {
  for (int i = 0; i <= NUM_LEDS - 1; i++) { // set color
    leds[i] = CRGB(255, 150, 40);
  }
}

void led_lazy_on() {
  if (ledStatus) {
    return;
  }
  for (int i = 0; i <= 255; i++) { // light up
    FastLED.setBrightness(i);
    delay(20);
    FastLED.show();
  }
  ledStatus = true;
}

void led_lazy_off() {
  if (!ledStatus) {
    return;
  }
  for (int i = 255; i >= 0; i--) {
    FastLED.setBrightness(i); // 渐灭
    delay(10);
    FastLED.show();
  }
  ledStatus = false;
}

bool person_detect() {
  personValue = digitalRead(PERSON_PIN); // 读取引脚的电平
  if (personValue == HIGH) {
    Serial.println("person exist"); // 如果电平为高，打印 "高电平"
    return true;
  } else {
    Serial.println("person not exist"); // 如果电平为低，打印 "低电平"
    return false;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PERSON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); // LED初始化引脚为输出模式
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200);
  set_led_color();
  led_lazy_on();
  led_lazy_off();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (person_detect()) { // 有人
    led_lazy_on();
    delay(100); // 等待0.1s后再检查
  } else { // 无人
    led_lazy_off();
    delay(100);
  }
}
