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


public:
    pid(double kp, double ki, double kd)
        : kp(kp), ki(ki), kd(kd)
{}

void control(
    double feedback_val,  // 現在速度
    double target_val,    // 目標速度
    double error_now,     // 現在の誤差
    double error_behind,  // ひとつ前の誤差
    double integral,      // ki,定積分用
    double DELTA_T        // 制御周期
    )
{

error_now = error_behind;
error_behind = feedback_val – target_val;
integral += (error_behind + error_now) / 2.0 * DELTA_T;

p = kp * error_behind;
i = ki * integral;
d = kd * (error_behind – error_now) / DELTA_T;

}

double get_pid()
{
    return (p + i + d);
}


};

#endif