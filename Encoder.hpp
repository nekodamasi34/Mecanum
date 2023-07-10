#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include "mbed.h"
#include "math.h"

class Encoder
{
    public:
    Encoder(PinName encoder_a_pin , PinName encoder_b_pin) 
    : encoder_a(encoder_a_pin) , encoder_b(encoder_b_pin)
    {
        encoder_a.rise(callback(this, &Encoder::rise));
        t.start();
    };

    double rps;
    double r;
    int ct;
    int rt;
    int get_t;
    int count_t;
    Timer t;
    double last_rotation;
    


    void rise()
    {
        if(encoder_b.read() == 1){
            ct++;
            rt = 0;
        }else if(encoder_b.read() == 0){
            ct--;
            rt = 1;
        };        
    }

    double get_rotation()
    {
        return (double)ct/1296;
    }

    double get_rps()
    {
        rps = ( get_rotation() - last_rotation ) / (double)t;

    
        t.reset();
    
        last_rotation = get_rotation();

        return (double)rps;
    }


    private:
        InterruptIn encoder_a;
        DigitalIn encoder_b;

};



#endif