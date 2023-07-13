#ifndef MECANUM_4_H_
#define MECANUM_4_H_

#include "mbed.h"
#include "math.h"

#include <Movement.h>
#include <Wheel.h>

class Mecanum_4 : public Movement
{
public:
    enum
    {
        LF,
        LB,
        RB,
        RF,
        NUM
    };
    
    Mecanum_4(MD *md[NUM]);
    Mecanum_4(MD *md_LF, MD *md_LB, MD *md_RB, MD *md_RF);
    Mecanum_4(Wheel *wheel[NUM]);
    
    virtual void move(double x, double y, double yaw);
    
    
private:
    Wheel *wheel[NUM];

};

#endif