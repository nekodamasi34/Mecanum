#include "mbed.h"
#include "math.h"
#include "Mecanum_4.h"


Mecanum_4::Mecanum_4(MD *md[NUM])
{
    wheel[LF] = new Wheel( md[LF],  1.0 * M_PI / 4.0,  3.0 * M_PI / 4.0 );
    wheel[LB] = new Wheel( md[LB],  3.0 * M_PI / 4.0, -3.0 * M_PI / 4.0 );
    wheel[RB] = new Wheel( md[RB], -3.0 * M_PI / 4.0, -1.0 * M_PI / 4.0 );
    wheel[RF] = new Wheel( md[RF], -1.0 * M_PI / 4.0,  1.0 * M_PI / 4.0 );
}

Mecanum_4::Mecanum_4(MD *md_LF, MD *md_LB, MD *md_RB, MD *md_RF)
{
    wheel[LF] = new Wheel( md_LF,  1.0 * M_PI / 4.0,  3.0 * M_PI / 4.0 );
    wheel[LB] = new Wheel( md_LB,  3.0 * M_PI / 4.0, -3.0 * M_PI / 4.0 );
    wheel[RB] = new Wheel( md_RB, -3.0 * M_PI / 4.0, -1.0 * M_PI / 4.0 );
    wheel[RF] = new Wheel( md_RF, -1.0 * M_PI / 4.0,  1.0 * M_PI / 4.0 );
}

Mecanum_4::Mecanum_4(Wheel *wheel[NUM])
{
    for(int i = 0; i < NUM; i++){
        this->wheel[i] = wheel[i];
    }
}

void Mecanum_4::move(double x, double y, double yaw)
{
    double move_angle, move_radius;
    double duty[NUM];
    double max_duty, limit_duty = 1.0;
    
    move_angle = atan2(y, x);
    move_radius = sqrt( y * y + x * x );
    
    for(int i = 0; i < NUM; i++)
        duty[i] = wheel[i]->set_wheel_vel(move_angle, move_radius, yaw);

    // 平行移動と回転のうち、大きい方をmax_dutyに格納
    if(move_radius > fabs(yaw))
    	max_duty = move_radius;
    else
    	max_duty = fabs(yaw);

	up_limit_balance(duty, NUM, max_duty);
	down_limit_balance(duty, NUM, limit_duty);
    
    for(int i = 0; i < NUM; i++){
        wheel[i]->drive(duty[i]);
    }
}