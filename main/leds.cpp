#include "FastLED.h"
#include "FX.h"

#include <string>
#include <iostream>

// We have 13 LEDs but we're skipping #7 because it's in the middle
// and won't be able to be seen
#define NUM_LEDS 13
#define SKIP_LEDS 1
#define SKIP_LED_NUM 7

#define REDLINE 6800

#define DATA_PIN 13
#define BRIGHTNESS  80
#define LED_TYPE    WS2811


CRGB leds[NUM_LEDS];

extern "C" {
	void doLEDS(double);
	void LEDSetup();
	void lightupLEDS(int);
}

double getRPM(double hz) {
	return (hz * 60 / 4);
}

void LEDSetup() {
	FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
}

void lightupLEDS(int numof) {
	// for lighting up the LEDs we want to light up
	for (int i=1; i<=NUM_LEDS; i++) {
		if (i == SKIP_LED_NUM) {
			continue;
		}

		if (i <= numof) {
			// light up LEDs
			leds[i-1] = CRGB(0, 255, 0);
		} else if (i > numof) {
			leds[i-1] = CRGB(0, 0, 0);
		}
	}

	FastLED.show();
}

void doLEDS(double hz) {
	double rpm = getRPM(hz);

	float stages = NUM_LEDS-SKIP_LEDS;
	float interval = (REDLINE / stages);

	lightupLEDS( floor(rpm/interval) );
}
