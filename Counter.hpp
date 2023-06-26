#ifndef _COUNTER_HPP_
#define _COUNTER_HPP_

#include "mbed.h"
#include "math.h"

class Counter
{
    public:
    Counter(PinName counter_a_pin , PinName counter_b_pin) 
    : counter_a(counter_a_pin) , counter_b(counter_b_pin)
    {
        counter_a.rise(callback(this, &Counter::rise));
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
        if(counter_b.read() == 1){
            ct++;
            rt = 0;
        }else if(counter_b.read() == 0){
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
        InterruptIn counter_a;
        DigitalIn counter_b;

};



#endif