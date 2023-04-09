#include "OrbChain.h"

OrbChain::OrbChain(size_t orb_count, Color trajectory[], size_t trajectory_size, int pin){
    this->orb_count = orb_count;
    this->orbs = new Orb*[orb_count];

    for(size_t i = 0; i < this->orb_count; ++i){
        this->orbs[i] = new Orb(trajectory, trajectory_size);
    }

    this->strip = Adafruit_NeoPixel(orb_count * Orb::LED_COUNT, pin, NEO_KHZ800 + NEO_GRB);
    strip.begin();
    strip.clear();
    strip.show();
}

OrbChain::~OrbChain(){
    for(size_t i = 0; i < this->orb_count; ++i){
        delete this->orbs[i];
    }
    delete[] this->orbs;
}

void OrbChain::set_uniform_orb_trajectory(){
    for(size_t i = 0; i < this->orb_count; ++i){
        orbs[i]->set_uniform_color_change();
    }
}

void OrbChain::set_random_orb_trajectory(){
    for(size_t i = 0; i < this->orb_count; ++i){
        orbs[i]->set_random_color_change();
    }
}

void OrbChain::set_orb_trajectory(Color trajectory[], size_t trajectory_size, int orb_index){
    this->orbs[orb_index]->set_trajectory(trajectory, trajectory_size);
}

void OrbChain::show_next(int step){
    Serial.println("Called OrbChain::show_next");
    
    if(step < 1){
        step = 1;
    }

    int led_index = 0;

    for(size_t orb_num = 0; orb_num < this->orb_count; ++orb_num){
        for(size_t led_num = 0; led_num < Orb::LED_COUNT; ++led_num){
            Color led_color = this->orbs[orb_num]->get_color_value(led_num);
            strip.setPixelColor(led_index, strip.Color(led_color.r, led_color.g, led_color.b));
            led_index++;
        }
        for(int i = 0; i < step; ++i){
            this->orbs[i]->next();
        }
    }
    strip.show();
}