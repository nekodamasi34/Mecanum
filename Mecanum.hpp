#ifndef _MECANUM_H_
#define _MECANUM_H_

#include "mbed.h"
#include "math.h"

class MecanumWheel {

private:

    double wheel[2];

public:

    MecanumWheel() : 
    {}

    void control(double targetSpeed,
                 double targetRotation,
                 double Lturn,
                 double Rturn)
    {
        wheel[0] = sin(targetRotation) / cos(targetRotation) * targetSpeed;
        wheel[1] = cos(targetRotation) / sin(targetRotation) * targetSpeed;
    }

    double getSpeed_0(){
        return wheel[0];
    }

    double getspeed_1(){
        return wheel[1];
    }
};

#endif