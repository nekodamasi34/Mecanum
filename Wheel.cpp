#include "mbed.h"
#include "math.h"

#include "Wheel.h"



Wheel::Wheel(MD *md, double wheel_angle, double position_angle)
{
    this->md = md;
    this->wheel_angle = wheel_angle;
    this->wheel_radius = 0;
    
    this->position_angle = position_angle;
    this->position_radius = 1;
}

Wheel::Wheel(MD *md, double wheel_angle, double position_x, double position_y, double wheel_radius)
{
    this->md = md;
    this->wheel_angle = wheel_angle;
    this->wheel_radius = wheel_radius;
    
    set_position(position_x, position_y);
}
    
void Wheel::set_position(double position_x, double position_y)
{
    position_angle = atan2(position_y, position_x);
    position_radius = sqrt( position_y * position_y + position_x * position_x );
}
    
double Wheel::set_wheel_vel(double move_angle, double move_radius, double yaw)
{
    double speed;
    double moving, rotating;
    
    while(move_angle > M_PI)
        move_angle -= 2.0 * M_PI;
    
    moving = cos(wheel_angle - move_angle) * move_radius;
    
    rotating = sin(wheel_angle - position_angle) * yaw * position_radius;
    
    speed = moving + rotating;
    
    return speed;
}

void Wheel::drive(double duty)
{
    md->drive(duty);
}