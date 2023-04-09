#ifndef ORBCHAIN_H
#define ORBCHAIN_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Orb.h>
#include <Color.h>

class OrbChain{
public:
    OrbChain(size_t orb_count, Color trajectory[], size_t trajectory_size, int pin);
    ~OrbChain();
    
    void set_uniform_orb_trajectory();
    void set_random_orb_trajectory();
    void set_orb_trajectory(Color trajectory[], size_t trajectory_size, int orb_index);
    void show_next(int step); //the higher the step, the more colors will be skipped -> the faster the colour trajectory

private:
    Orb** orbs;
    size_t orb_count;

    Adafruit_NeoPixel strip;
};

#endif