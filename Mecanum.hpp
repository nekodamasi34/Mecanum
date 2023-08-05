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

    double getSpeed(int unit) {
        if(unit < 0 || unit > 3) {
            return 0.0;
        }
        return wheel[unit];
    }
};

#endif
