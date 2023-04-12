#include <Arduino.h>
#include <OrbChain.h>
#include <Adafruit_NeoPixel.h>


const int color_size = 4; Color colors[color_size] = {Color(82, 255, 253), Color(1, 74, 79), Color(8, 103, 79), Color(1, 74, 79)};
//const int color_size = 3; Color colors[color_size] = {Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255)};

OrbChain chain = OrbChain(1, colors, color_size, 8);


void setup() {
	Serial.begin(9600);
    chain.begin();
}

void loop() {
    chain.show_next_n(1);
}