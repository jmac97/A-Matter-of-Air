#include <FastLED.h>
#include "PinChangeInterrupt.h"

// String info
#define NUM_STRINGS 42
#define NUM_LEDS_PER_STRING 12
#define LED_TYPE WS2812
CRGB leds[NUM_STRINGS][NUM_LEDS_PER_STRING];

// LED indicator info
#define NUM_LEDS 5
#define INC 1
#define LED_PIN 53
CRGB indicator[NUM_LEDS];

// Color info
//const CRGB color_neg_three = CRGB(22, 195, 242);
//const CRGB color_neg_two = CRGB(89, 151, 241);
//const CRGB  color_neg_one = CRGB(155, 107, 240);
//const CRGB  color_zero = CRGB(222, 63, 239);
//const CRGB  color_one = CRGB(226, 42,191);
//const CRGB  color_two = CRGB(230, 21, 143);
//const CRGB  color_three = CRGB(234, 0, 95);

const CRGB color_neg_three = CRGB(26, 216, 237);
const CRGB color_neg_two = CRGB(52, 188, 237);
const CRGB  color_neg_one = CRGB(78, 161, 237);
const CRGB  color_zero = CRGB(156, 78, 237);
const CRGB  color_one = CRGB(182, 50, 237);
const CRGB  color_two = CRGB(230, 21, 143);
const CRGB  color_three = CRGB(234, 0, 95);

const CRGB  colors[7] = {color_neg_three, color_neg_two, color_neg_one, color_zero, color_one, color_two, color_three};

// Button pins
const uint8_t button_pm25 = A8;
const uint8_t button_c_asthma = A9;
const uint8_t button_resp = A10;
const uint8_t button_cardio = A11;
const uint8_t button_poverty = A12;

// Brightness settings
uint8_t brightness_og = 42;
int brightness = 42;
uint8_t brightness_inc = 1;
uint8_t brightness_speed = 10;

const char poverty[42] =
{2, 2, 5, 3, 6, 6, 6, 3, 2, 4, 4, 4, 4, 2, 1, 2, 3, 5, 3, 4, 6, 1, 1, 2, 1, 1, 3, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 3, 3, 3, 1, 1};

// PM2.5 data
// [42] = neighborhood
// [12] = space time cube value
const char PROGMEM pm25[42][12] =
{
  {5.0 , 6.0 , 5.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0},
  {5.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0 , 0.0},
  {5.0 , 5.0 , 5.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 2.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 2.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0},
  {5.0 , 5.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0 , 0.0},
  {5.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0},
  {3.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0},
  {5.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 5.0 , 4.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0},
  {4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0},
  {5.0 , 5.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0},
};

// children asthma data
// [42] = neighborhood
// [12] = space time cube value
const char PROGMEM c_asthma[42][12] =
{
  {5.0 , 5.0 , 6.0 , 4.0 , 3.0 , 3.0 , 3.0 , 4.0 , 4.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 4.0 , 4.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 4.0 , 3.0 , 3.0 , 3.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0},
  {2.0 , 2.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 2.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {1.0 , 1.0 , 3.0 , 3.0 , 2.0 , 2.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0},
  {2.0 , 2.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 5.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 5.0 , 4.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
};

// respiratory hospitalization data
// [42] = neighborhood
// [13] = space time cube value
const char PROGMEM resp[42][12] =
{
  {6.0 , 6.0 , 6.0 , 6.0 , 4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 4.0 , 4.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 4.0 , 4.0 , 4.0 , 4.0 , 4.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 4.0 , 4.0 , 4.0 , 4.0 , 4.0},
  {4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0},
  {4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0},
  {6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0},
  {5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 4.0 , 4.0 , 4.0},
  {6.0 , 6.0 , 6.0 , 6.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {5.0 , 5.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0},
  {5.0 , 5.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 2.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 1.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0 , 2.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0 , 2.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0 , 1.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {5.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
};

// cardio hospitalization data
// [42] = neighborhood
// [12] = space time cube value
const char PROGMEM cardio[42][12] =
{
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 2.0 , 0.0 , 0.0 , 1.0 , 1.0 , 1.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 0.0 , 0.0 , 1.0 , 2.0 , 2.0},
  {6.0 , 6.0 , 6.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 2.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 2.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 3.0 , 3.0 , 3.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 3.0 , 3.0 , 3.0},
  {5.0 , 5.0 , 3.0 , 3.0 , 2.0 , 2.0 , 1.0 , 0.0 , 0.0 , 1.0 , 2.0 , 2.0},
  {5.0 , 5.0 , 3.0 , 3.0 , 2.0 , 2.0 , 1.0 , 0.0 , 0.0 , 1.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0},
  {4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0 , 1.0 , 2.0 , 2.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 0.0 , 0.0 , 1.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0 , 0.0 , 1.0 , 1.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0 , 0.0 , 1.0 , 1.0},
  {6.0 , 6.0 , 6.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 0.0 , 0.0 , 1.0 , 2.0 , 2.0},
  {6.0 , 6.0 , 5.0 , 3.0 , 3.0 , 3.0 , 3.0 , 2.0 , 2.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 1.0 , 1.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {4.0 , 4.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
  {3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0},
};


void setup() {
  pinMode(button_pm25, INPUT_PULLUP);
  pinMode(button_c_asthma, INPUT_PULLUP);
  pinMode(button_resp, INPUT_PULLUP);
  pinMode(button_cardio, INPUT_PULLUP);
  pinMode(button_poverty, INPUT_PULLUP);

  attachPCINT(digitalPinToPCINT(button_pm25), pm25_ISR, CHANGE);
  attachPCINT(digitalPinToPCINT(button_c_asthma), c_asthma_ISR, CHANGE);
  attachPCINT(digitalPinToPCINT(button_resp), resp_ISR, CHANGE);
  attachPCINT(digitalPinToPCINT(button_cardio), cardio_ISR, CHANGE);
  attachPCINT(digitalPinToPCINT(button_poverty), poverty_ISR, CHANGE);

  FastLED.addLeds<LED_TYPE, 0, GRB>(leds[0], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 1, GRB>(leds[1], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 2, GRB>(leds[2], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 3, GRB>(leds[3], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 4, GRB>(leds[4], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 5, GRB>(leds[5], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 6, GRB>(leds[6], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 7, GRB>(leds[7], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 8, GRB>(leds[8], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 9, GRB>(leds[9], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 10, GRB>(leds[10], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 11, GRB>(leds[11], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 12, GRB>(leds[12], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 13, GRB>(leds[13], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 14, GRB>(leds[14], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 15, GRB>(leds[15], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 16, GRB>(leds[16], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 17, GRB>(leds[17], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 18, GRB>(leds[18], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 19, GRB>(leds[19], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 20, GRB>(leds[20], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 21, GRB>(leds[21], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 22, GRB>(leds[22], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 23, GRB>(leds[23], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 24, GRB>(leds[24], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 25, GRB>(leds[25], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 26, GRB>(leds[26], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 27, GRB>(leds[27], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 28, GRB>(leds[28], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 29, GRB>(leds[29], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 30, GRB>(leds[30], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 31, GRB>(leds[31], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 32, GRB>(leds[32], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 33, GRB>(leds[33], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 34, GRB>(leds[34], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 35, GRB>(leds[35], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 36, GRB>(leds[36], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 37, GRB>(leds[37], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 38, GRB>(leds[38], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 39, GRB>(leds[39], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 40, GRB>(leds[40], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 41, GRB>(leds[41], NUM_LEDS_PER_STRING);


  FastLED.addLeds<WS2811, LED_PIN, RGB>(indicator, NUM_LEDS);

  FastLED.setBrightness(brightness_og);

  clear();

//  colorTest(0);
//  FastLED.show();

}

void loop() {
    cycle();
}

void clear() {
  for (int i = 0; i < NUM_STRINGS; i++) {
    for (int j = 0; j < NUM_LEDS_PER_STRING; j++) {
      leds[i][j] = CRGB::Black;
    }
  }
  FastLED.show();
  delay(100);
}

void colorTest(int color) {

  for (int i = 0; i < NUM_STRINGS; i++) {
    for (int j = 0; j < NUM_LEDS_PER_STRING; j++) {
      leds[i][NUM_LEDS_PER_STRING - 1 - j] = colors[color];
    }
  }

}

void dataTest(int string) {
  int8_t data;
  for (int i = 0; i < NUM_LEDS_PER_STRING; i++) {
    leds[string][NUM_LEDS_PER_STRING - i] = colors[pm25[string][i]];
  }
}

void show_dataset_cube(const char dataset[][12], uint8_t dataset_char) {
  show_indicator(dataset_char);

  for (int i = 0; i < NUM_STRINGS; i++) {
    for (int j = 0; j < NUM_LEDS_PER_STRING; j++) {
      leds[i][NUM_LEDS_PER_STRING - 1 - j] = colors[pgm_read_byte(&(dataset[i][j]))];
    }
  }
}


void show_dataset_percent(const char dataset[], uint8_t dataset_char) {
  show_indicator(dataset_char);

  for (int i = 0; i < NUM_STRINGS; i++) {
    for (int j = 0; j < NUM_LEDS_PER_STRING; j++) {
      leds[i][j] = colors[dataset[i]];
    }
  }
}

void show_indicator(uint8_t dataset_char) {
  for (int i = 0; i < NUM_LEDS; i += INC) {
    if (i == dataset_char) {
      indicator[i] = CRGB::Red;
    } else {
      indicator[i] = CRGB::Black;
    }
  }
}

void cycle() {
  show_dataset_cube(pm25, 0);
  FastLED.show();
  fade_up();
  delay(5000);
  fade_down();
  
  show_dataset_cube(c_asthma, 1);
  FastLED.show();
  fade_up();
  delay(5000);
  fade_down();
  
  show_dataset_cube(resp, 2);
  FastLED.show();
  fade_up();
  delay(5000);
  fade_down();
  
  show_dataset_cube(cardio, 3);
  FastLED.show();
  fade_up();
  delay(5000);
  fade_down();
  
  show_dataset_percent(poverty, 4);
  FastLED.show();
  fade_up();
  delay(5000);
  fade_down();
}

void pm25_ISR() {
  delay(150);
  show_dataset_cube(pm25, 0);
  FastLED.show();
}

void c_asthma_ISR() {
  delay(150);
  show_dataset_cube(c_asthma, 1);
  FastLED.show();
}

void resp_ISR() {
  delay(150);
  show_dataset_cube(resp, 2);
  FastLED.show();
}

void cardio_ISR() {
  delay(150);
  show_dataset_cube(cardio, 3);
  FastLED.show();
}

void poverty_ISR() {
  delay(150);
  show_dataset_percent(poverty, 4);
  FastLED.show();
}

void fade_down() {
  while (brightness > 0) {
    brightness -= brightness_inc;
    FastLED.setBrightness(brightness);
    FastLED.show();
    delay(brightness_speed);
  }
    brightness = 0;
}

void fade_up() {
  while (brightness <= brightness_og) {
    brightness += brightness_inc;
    FastLED.setBrightness(brightness);
    FastLED.show();
    delay(brightness_speed);
  }
  brightness = brightness_og;
}
