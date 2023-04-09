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

Color(82, 255, 253), Color(1, 74, 79), Color(8, 103, 79), Color(1, 74, 79)
*/

#ifndef ORB_H
#define ORB_H

#include <Color.h>
#include <Arduino.h>

class Orb{
public:
    static const size_t LED_COUNT = 3; //put to 6
    static const int INTERVALL_SIZE = 1000;

    Orb(Color colors[], size_t num_colors);
    ~Orb();

    void begin();

    void next();
    void next_n(unsigned int n);
    Color get_color_value(size_t led);
    String debug_get_interval_color();

    void set_trajectory(Color trajectory[], size_t num_colors);
    void set_uniform_color_change();
    void set_random_color_change();

private:
    Color get_interval_color(unsigned int step);


private:
    unsigned int* steps;

    Color* color_trajectory;
    size_t color_count;
};

#endif