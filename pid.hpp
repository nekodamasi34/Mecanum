#ifndef _PID_HPP_
#define _PID_HPP_

#include "mbed.h"
#include "math.h"

class pid {

private:
    //PID制御
    double kp;   // 比例ゲイン
    double ki;   // 積分ゲイン
    double kd;   // 微分ゲイン

    double p, i, d;
    //  内部におけるものは積極的に内部におく
    double error_now, error_behind, integral;


public:
    pid(double kp, double ki, double kd)
        : kp(kp), ki(ki), kd(kd), error_now(0), error_behind(0), integral(0)
{}

void control(
    double feedback_val,  // 現在速度
    double target_val,    // 目標速度
    double DELTA_T        // 制御周期
    )
{

error_behind = error_now;
error_now = feedback_val – target_val;

integral += (error_behind + error_now) / 2.0 * DELTA_T;

p = kp * error_behind;
i = ki * integral;
d = kd * (error_now - error_behind) / DELTA_T;

}

double get_pid()
{
    return (p + i + d);
}


};

#endif