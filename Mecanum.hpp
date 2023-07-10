#ifndef MECANUM_HPP_
#define MECANUM_HPP_

#include "mbed.h"

class MecanumWheel {
private:

    double speed_FL;
    double speed_FR; 
    double speed_RL;
    double speed_RR;

    double LTurn;
    double RTurn;

    double targetSpeed;      // 目標速度
    double targetRotation;   // 目標回転速度
    double targetSidewaysSpeed;   // 目標横方向速度
    double targetDiagonalSpeed;   // 目標斜め方向速度



public:
    void control(double targetSpeed, double targetRotation, double Lturn, double Rturn) {

    }
};

#endif  // MECANUM_HPP
