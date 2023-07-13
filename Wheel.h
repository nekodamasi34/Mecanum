#ifndef WHEEL_H_
#define WHEEL_H_

#include <mbed.h>
#include "math.h"
#include <MD.hpp>

class Wheel
{
public:
    Wheel(MD *md, double wheel_angle, double position_angle);
    Wheel(MD *md, double wheel_angle, double position_x, double position_y, double wheel_radius = 0);
    
    void set_position(double position_x, double position_y);
    
    double set_wheel_vel(double move_angle, double move_radius, double yaw);
    
    void drive(double duty);
private:
    MD *md;

    double position_angle, position_radius;
    double wheel_angle, wheel_radius;
};
    
#endif

#ifndef M_PI
#define M_PI 3.1415926535
#endif