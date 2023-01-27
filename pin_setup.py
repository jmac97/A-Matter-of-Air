for x in range(0,42):
    print("FastLED.addLeds<LED_TYPE, ", end='')
    print(x, end='')
    print(", RGB>(leds[", end='')
    print(x, end='')
    print("], NUM_LEDS_PER_STRING);")
