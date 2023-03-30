/*
1. from 52fffd to 014a4f
2. from 014a4f to 08674f
3. from 08674f to 014a4f
4. from 014a4f to 52fffd
45d9cb
1e6a7d

Color values
1. 52fffd = rgb(82, 255, 253)
2. 014a4f = rgb(1, 74, 79)
3. 08674f = rgb(8, 103, 79)
4. 014a4f = rgb(1, 74, 79)
*/


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

//TODO change processing and values of the colour, such that we can apply byte datatype
struct Color{
	int r;
	int g;
	int b;
	int alpha;

	Color(int r, int g, int b, int alpha = 255) : r(r), g(g), b(b), alpha(alpha){}
	Color() : r(0), g(0), b(0), alpha(255){}
};



Color interpolateColor(Color &in, Color &target, int step, int intervallSize){
	double fraction = (double)step/(double)intervallSize;
	return Color(
		in.r + (target.r - in.r) * fraction, 
		in.g + (target.g - in.g) * fraction, 
		in.b + (target.b - in.b) * fraction,
		in.alpha + (target.alpha - in.alpha) * fraction
	);
}

void orbEffect(Adafruit_NeoPixel &p, int ledCount){
	int colorCount = 4;
	
	//values taken from: see above
	Color colors[colorCount] = {Color(82, 255, 253), Color(1, 74, 79), Color(8, 103, 79), Color(1, 74, 79)};
	const int singleIntervall = 1000;
	const int intervallSize = colorCount * singleIntervall;
	 
	int stepValues[ledCount] = {0};
	for(int i = 0; i < ledCount; ++i){
		stepValues[i] = random(intervallSize);
	}

	for(int step = 0; step <= intervallSize; ++i){
		for(int led = 0; led < ledCount; ++led){
			Color currColor;
			switch(stepValues[led] % 1000){
				case 0: 
					currColor = interpolateColor(colors[0], colors[1], step, singleIntervall);
					break;
				case 1:
					currColor = interpolateColor(colors[1], colors[2], step, singleIntervall);
					break;
				case 2:
					currColor = interpolateColor(colors[2], colors[3], step, singleIntervall);
					break;
				case 3:
					currColor = interpolateColor(colors[3], colors[0], step, singleIntervall);
					break;
			}
			stepValues[led] = (stepValues[led] + 1) % intervallSize;

			p.setPixelColor(led, currColor.r, currColor.g, currColor.b);
			
		}
		p.show();
	}
}

Adafruit_NeoPixel p(3, GPIO_NUM_23, NEO_KHZ800 + NEO_GRB);

int i = 0;
int intervallSize = 100;
Color start(82, 255, 253);
Color end(1, 74, 79);

void setup() {
	Serial.begin(9600);
	
	p.begin();
	p.clear();
	p.show();
}

void loop() {

	orbEffect(p, 6);

	/*
	Serial.println("Start: " + String(start.r) + " " + String(start.g) + " " + String(start.b));
	Serial.println("End: " + String(end.r) + " " + String(end.g) + " " + String(end.b));
	Color inter = interpolateColor(start, end, i, intervallSize);
	Serial.println("Intermediate: " + String(inter.r) + " " + String(inter.g) + " " + String(inter.b));

	p.fill(p.Color(inter.r, inter.g, inter.b), 0, 3);
	p.show();

	i = (i + 1) % intervallSize;
*/
}