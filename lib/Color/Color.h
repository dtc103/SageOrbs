#ifndef COLOR_H
#define COLOR_H

class Color{
public:
    int r;
	int g;
	int b;
	int alpha;

	Color(int r, int g, int b, int alpha = 255) : r(r), g(g), b(b), alpha(alpha){}
	Color() : r(0), g(0), b(0), alpha(255){}

    static Color interpolateColor(Color &in, Color &target, double percentage){
        return Color(
            in.r + (target.r - in.r) * percentage, 
            in.g + (target.g - in.g) * percentage, 
            in.b + (target.b - in.b) * percentage,
            in.alpha + (target.alpha - in.alpha) * percentage
        );
    }
};

#endif