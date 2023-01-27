#include <FastLED.h>

// String info
#define NUM_STRINGS 42
#define NUM_LEDS_PER_STRING 13
#define LED_TYPE WS2811
CRGB leds[NUM_STRINGS][NUM_LEDS_PER_STRING];

// Color info
const CRGB color_neg_three = CRGB(0, 0, 255);
const CRGB color_neg_two = CRGB(0, 200, 255);
const CRGB  color_neg_one = CRGB(0, 225, 225);
const CRGB  color_zero = CRGB(255, 255, 255);
const CRGB  color_one = CRGB(255, 75, 0);
const CRGB  color_two = CRGB(255, 50, 0);
const CRGB  color_three = CRGB(255, 0, 0);

const CRGB  colors[7] = {color_neg_three, color_neg_two, color_neg_one, color_zero, color_one, color_two, color_three};

// PM2.5 data
// [42] = neighborhood
// [13] = space time cube value
const char pm25[42][13] =
{
  {0.0, 2.0 ,3.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0},
  {0.0, 2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 2.0 ,2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,-1.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0},
  {0.0, 2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0, 3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0},
  {0.0, 1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-3.0},
  {0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0},
};

// death data
// [42] = neighborhood
// [13] = space time cube value
const char death[42][13] =
{
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {1.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {1.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {2.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {1.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0},
  {0.0 ,2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {1.0 ,2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0},
  {3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0}
};

// children asthma data
// [42] = neighborhood
// [13] = space time cube value
const char c_asthma[42][13] =
{
  {0.0 ,2.0 ,2.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {1.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0},
  {1.0 ,3.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,-2.0 ,-2.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,1.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
};

// hospitalization data
// [42] = neighborhood
// [13] = space time cube value
const char hosp[42][13] =
{
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,1.0 ,1.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0},
  {1.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0},
  {1.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,1.0 ,1.0 ,1.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {1.0 ,2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0},
  {1.0 ,2.0 ,2.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-1.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {1.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
};

// cardio hospitalization data
// [42] = neighborhood
// [13] = space time cube value
const char cardio[42][13] =
{
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-3.0 ,-3.0 ,-2.0 ,-2.0 ,-2.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-3.0 ,-3.0 ,-2.0 ,-1.0 ,-1.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-1.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-1.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,0.0},
  {1.0 ,2.0 ,2.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0 ,-2.0 ,-1.0 ,-1.0},
  {1.0 ,2.0 ,2.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0 ,-2.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {1.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0 ,-3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0 ,-2.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-3.0 ,-3.0 ,-2.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0 ,-3.0 ,-2.0 ,-2.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-3.0 ,-3.0 ,-2.0 ,-1.0 ,-1.0},
  {2.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-2.0 ,-2.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
};

// adult asthma data
// [42] = neighborhood
// [13] = space time cube value
const char a_asthma[42][13] =
{
  {1.0 ,3.0 ,3.0 ,3.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {1.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {2.0 ,3.0 ,3.0 ,3.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0},
  {3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,3.0 ,2.0 ,2.0 ,2.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,1.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0 ,-1.0 ,-2.0 ,-2.0 ,-2.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,-1.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
  {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0},
};


void setup() {
  FastLED.addLeds<LED_TYPE, 0, RGB>(leds[0], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 1, RGB>(leds[1], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 2, RGB>(leds[2], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 3, RGB>(leds[3], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 4, RGB>(leds[4], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 5, RGB>(leds[5], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 6, RGB>(leds[6], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 7, RGB>(leds[7], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 8, RGB>(leds[8], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 9, RGB>(leds[9], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 10, RGB>(leds[10], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 11, RGB>(leds[11], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 12, RGB>(leds[12], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 13, RGB>(leds[13], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 14, RGB>(leds[14], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 15, RGB>(leds[15], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 16, RGB>(leds[16], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 17, RGB>(leds[17], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 18, RGB>(leds[18], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 19, RGB>(leds[19], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 20, RGB>(leds[20], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 21, RGB>(leds[21], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 22, RGB>(leds[22], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 23, RGB>(leds[23], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 24, RGB>(leds[24], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 25, RGB>(leds[25], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 26, RGB>(leds[26], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 27, RGB>(leds[27], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 28, RGB>(leds[28], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 29, RGB>(leds[29], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 30, RGB>(leds[30], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 31, RGB>(leds[31], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 32, RGB>(leds[32], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 33, RGB>(leds[33], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 34, RGB>(leds[34], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 35, RGB>(leds[35], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 36, RGB>(leds[36], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 37, RGB>(leds[37], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 38, RGB>(leds[38], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 39, RGB>(leds[39], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 40, RGB>(leds[40], NUM_LEDS_PER_STRING);
  FastLED.addLeds<LED_TYPE, 41, RGB>(leds[41], NUM_LEDS_PER_STRING);
  
  FastLED.setBrightness(50);

  clear();

//  colorTest();
//  dataTest(20);
//  show_dataset(pm25);
}

void loop() {
  // put your main code here, to run repeatedly:
  show_dataset(pm25);
  FastLED.show();
  delay(5000);
  show_dataset(death);
  FastLED.show();
  delay(5000);
  show_dataset(c_asthma);
  FastLED.show();
  delay(5000);
  show_dataset(hosp);
  FastLED.show();
  delay(5000);
  show_dataset(cardio);
  FastLED.show();
  delay(5000);
  show_dataset(a_asthma);
  FastLED.show();
  delay(5000);
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

void colorTest() {
  for (int i = 0; i < 7; i++) {
    leds[0][i] = colors[i];
  }
}

void dataTest(int string) {
  for (int i = 0; i < NUM_LEDS_PER_STRING-1; i++) {
    leds[string][NUM_LEDS_PER_STRING-1-i] = colors[pm25[string][i] + 3];
  }
}

void show_dataset(const char dataset[42][13]) {
  for (int i = 0; i < NUM_STRINGS; i++) {
    for (int j = 0; j < NUM_LEDS_PER_STRING; j++) {
      leds[i][NUM_LEDS_PER_STRING-j] = colors[dataset[i][j]+3];
    }
  }  
}
