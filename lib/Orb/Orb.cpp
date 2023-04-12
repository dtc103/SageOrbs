#include "Orb.h"

Orb::Orb(Color colors[], size_t num_colors){
    this->color_trajectory = colors;
    this->color_count = num_colors;

    this->steps = new unsigned int[this->color_count]();   
}

Orb::~Orb(){
    delete[] this->steps;
}

void Orb::begin(){
    randomSeed(analogRead(0));
    for(size_t i = 0; i < LED_COUNT; ++i){
        this->steps[i] = random(INTERVALL_SIZE * this->color_count);
        delay(1);
    }
}

void Orb::next(){
    for(size_t i = 0; i < LED_COUNT; ++i){
        this->steps[i] = (this->steps[i] + 1) % (INTERVALL_SIZE * this->color_count);
    }
}

void Orb::next_n(unsigned int n){
    for(size_t i = 0; i < LED_COUNT; ++i){
        this->steps[i] = (this->steps[i] + n) % (INTERVALL_SIZE * this->color_count);
    }
}

Color Orb::get_color_value(size_t led){
    if(led < 0 || led > this->color_count - 1){
        return Color(0, 0, 0);
    }
    Color color = get_interval_color(this->steps[led]);
    return color; 
}

Color Orb::get_interval_color(unsigned int step){
    unsigned int color_pick = step / INTERVALL_SIZE;

    if(color_pick == this->color_count - 1){
        return Color::interpolateColor(color_trajectory[color_pick], color_trajectory[0], (double)(step % INTERVALL_SIZE) / (double)INTERVALL_SIZE);
    }else{
        return Color::interpolateColor(color_trajectory[color_pick], color_trajectory[color_pick + 1], (double)(step % INTERVALL_SIZE) / (double)INTERVALL_SIZE);
    }
}

void Orb::set_trajectory(Color trajectory[], size_t num_colors){
    this->color_count = num_colors;
    this->color_trajectory = trajectory;

    randomSeed(analogRead(0));
    for(size_t i = 0; i < LED_COUNT; ++i){
        this->steps[i] = random(INTERVALL_SIZE);
        delay(1);
    }
}

void Orb::set_uniform_color_change(){
    for(size_t i = 0; i < LED_COUNT; ++i){
        this->steps[i] = 0;
    }
}

void Orb::set_random_color_change(){
    for(size_t i = 0; i < LED_COUNT; ++i){
        int step = random(INTERVALL_SIZE);

        this->steps[i] = step;
    }
}

String Orb::debug_get_interval_color(){
    String debug_output = String("");

    for(size_t i = 0; i < this->LED_COUNT; ++i){
        debug_output += String("led") + String(i) + String(": ");
        debug_output += String(this->get_color_value(i).r) + String(" ");
        debug_output += String(this->get_color_value(i).g) + String(" ");
        debug_output += String(this->get_color_value(i).b) + String(";\t");
    }
    debug_output += String("\n");

    return debug_output;
}

