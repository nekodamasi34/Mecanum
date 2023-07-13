#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include "mbed.h"
#include "math.h"
#include <chrono>

class Encoder
{
    private:
        InterruptIn encoder_a;
        InterruptIn encoder_b;

        int revolution;
        int count;
        int rotate;
        double last_angle;
        double last_rotation;

    
    public:
    Encoder(PinName encoder_a_pin, PinName encoder_b_pin, int revolution) 
    : encoder_a(encoder_a_pin), encoder_b(encoder_b_pin), revolution(revolution)
    {
        encoder_a.rise(callback(this, &Encoder::rise_a));
        encoder_b.rise(callback(this, &Encoder::rise_b));
        encoder_a.fall(callback(this, &Encoder::fall_a));
        encoder_b.fall(callback(this, &Encoder::fall_b));
    };


    


    void rise_a()
    {
        if(encoder_b.read()){
            count++;
            rotate = 0;
        }else if(encoder_b.read()){
            count--;
            rotate = 1;
        };        
    }

    void rise_b()
    {
        if(encoder_a.read()){
            count++;
            rotate = 0;
        }else if(encoder_b.read()){
            count--;
            rotate = 1;
        };        
    }

    void fall_a()
    {
        if(encoder_b.read()){
            count++;
            rotate = 0;
        }else if(encoder_b.read()){
            count--;
            rotate = 1;
        };        
    }

    void fall_b()
    {
        if(encoder_a.read()){
            count++;
            rotate = 0;
        }else if(encoder_a.read()){
            count--;
            rotate = 1;
        };        
    }

    double get_rotation()
    {
        return (double)count/1296;
    }

    double get_count()
    {
        return count;
    }

    void reset()
    {
        count = 0;
        last_angle = 0;
    }

    double get_rps()
    {
        rps = ( get_rotation() - last_rotation ) / (double)t;

    
        t.reset();
    
        last_rotation = get_rotation();

        return (double)rps;
    }




};



#endif