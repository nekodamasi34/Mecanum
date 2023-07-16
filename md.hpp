#ifndef _MD_HPP_
#define _MD_HPP_

#include "mbed.h"
#include "math.h"

class MD
{
    public:
    MD(PinName pwm_pin, PinName dir_pin)
    : pwm(pwm_pin), dir(dir_pin)
    {
        pwm.period(0.0005);
    };
    
    int getdir()
    {
        return dir;
    }

    void drive(float power)
    {   
        dir = power < 0 ? 0 : 1;
        pwm = abs(power) > 1 ? 1.0 : abs(power);
        // a ? b : c aが真ならbが実行、aが偽ならcが実行。
    }

    private:
        PwmOut pwm;
        DigitalOut dir;
};

#endif