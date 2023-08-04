#ifndef _MECANUM_HPP_
#define _MECANUM_HPP_

#include "mbed.h"
#include "math.h"

class MecanumWheel {

private:

    double wheel[4];

public:

    MecanumWheel() : 
    {}

    void control(double _targetSpeed, double _targetRotation, double _LRturn)
    {
        wheel[0] = sin(_targetRotation) / cos(_targetRotation) * _targetSpeed - _targetRotation;
        wheel[1] = cos(_targetRotation) / sin(_targetRotation) * _targetSpeed + _targetRotation;
        wheel[2] = cos(_targetRotation) / sin(_targetRotation) * _targetSpeed - _targetRotation;
        wheel[3] = sin(_targetRotation) / cos(_targetRotation) * _targetSpeed + _targetRotation;
    }

    double getSpeed_0(){
        return wheel[0];
    }

    double getSpeed_1(){
        return wheel[1];
    }

    double getSpeed_2(){
        return wheel[2];
    }

    double getSpeed_3(){
        return wheel[3];
    }
};

#endif
