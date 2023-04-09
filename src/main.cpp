#include <Arduino.h>
#include <OrbChain.h>
#include <Adafruit_NeoPixel.h>

const int color_size = 3;
//Color colors[color_size] = {Color(82, 255, 253), Color(1, 74, 79), Color(8, 103, 79), Color(1, 74, 79)};
Color colors[color_size] = {Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255)};

Orb o1 = Orb(colors, color_size);
Adafruit_NeoPixel strip(Orb::LED_COUNT, 8, NEO_KHZ800 + NEO_GRB);

void setup() {
	Serial.begin(9600);
    // Serial.println("Calling constructor OrbChain");
    // OrbChain chain(1, colors, color_size, 8);
    // Serial.println("finished with constructor OrbChain");
    // chain.show_next(1);
    // delay(1000);
    // chain.show_next(500);
    // delay(1000);
    // chain.show_next(500);


    o1.begin();
    //Serial.println(o1.debug_get_interval_color());

    strip.begin();
    strip.clear();
    strip.show();    
}

void loop() {
    o1.next();
    for(size_t i = 0; i < o1.LED_COUNT; ++i){
        strip.setPixelColor(i, o1.get_color_value(i).r, o1.get_color_value(i).g, o1.get_color_value(i).b);
    }
    delay(1);
    strip.show();
}