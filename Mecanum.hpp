#ifndef MECANUM_HPP
#define MECANUM_HPP

#include "mbed.h"

class MecanumWheel {
private:
    // メカナムホイールの制御ピン
    PwmOut frontLeftWheel;   // 前左のホイール
    PwmOut frontRightWheel;  // 前右のホイール
    PwmOut rearLeftWheel;    // 後左のホイール
    PwmOut rearRightWheel;   // 後右のホイール

    double kpFrontLeft;   // 前左の比例ゲイン
    double kiFrontLeft;   // 前左の積分ゲイン
    double kdFrontLeft;   // 前左の微分ゲイン

    double kpFrontRight;  // 前右の比例ゲイン
    double kiFrontRight;  // 前右の積分ゲイン
    double kdFrontRight;  // 前右の微分ゲイン

    double kpRearLeft;    // 後左の比例ゲイン
    double kiRearLeft;    // 後左の積分ゲイン
    double kdRearLeft;    // 後左の微分ゲイン

    double kpRearRight;   // 後右の比例ゲイン
    double kiRearRight;   // 後右の積分ゲイン
    double kdRearRight;   // 後右の微分ゲイン

    double targetSpeed;      // 目標速度
    double targetRotation;   // 目標回転速度
    double targetSidewaysSpeed;   // 目標横方向速度
    double targetDiagonalSpeed;   // 目標斜め方向速度

    double prevErrorFrontLeft;   // 前左の前回の偏差
    double integralFrontLeft;    // 前左の積分値
    double prevErrorFrontRight;  // 前右の前回の偏差
    double integralFrontRight;   // 前右の積分値
    double prevErrorRearLeft;    // 後左の前回の偏差
    double integralRearLeft;     // 後左の積分値
    double prevErrorRearRight;   // 後右の前回の偏差
    double integralRearRight;    // 後右の積分値

public:
    MecanumWheel(PinName frontLeftPin, PinName frontRightPin, PinName rearLeftPin, PinName rearRightPin,
                 double kpFL, double kiFL, double kdFL,
                 double kpFR, double kiFR, double kdFR,
                 double kpRL, double kiRL, double kdRL,
                 double kpRR, double kiRR, double kdRR)
        : frontLeftWheel(frontLeftPin), frontRightWheel(frontRightPin),
          rearLeftWheel(rearLeftPin), rearRightWheel(rearRightPin),
          kpFrontLeft(kpFL), kiFrontLeft(kiFL), kdFrontLeft(kdFL),
          kpFrontRight(kpFR), kiFrontRight(kiFR), kdFrontRight(kdFR),
          kpRearLeft(kpRL), kiRearLeft(kiRL), kdRearLeft(kdRL),
          kpRearRight(kpRR), kiRearRight(kiRR), kdRearRight(kdRR),
          targetSpeed(0.0), targetRotation(0.0), targetSidewaysSpeed(0.0), targetDiagonalSpeed(0.0),
          prevErrorFrontLeft(0.0), integralFrontLeft(0.0),
          prevErrorFrontRight(0.0), integralFrontRight(0.0),
          prevErrorRearLeft(0.0), integralRearLeft(0.0),
          prevErrorRearRight(0.0), integralRearRight(0.0)
    {
    }

    void setTarget(double speed, double rotation, double sidewaysSpeed, double diagonalSpeed) {
        targetSpeed = speed;
        targetRotation = rotation;
        targetSidewaysSpeed = sidewaysSpeed;
        targetDiagonalSpeed = diagonalSpeed;
    }

    void controlSpeed(double currentSpeedFrontLeft, double currentSpeedFrontRight,
                      double currentSpeedRearLeft, double currentSpeedRearRight,
                      bool isLeftTurnMode, bool isRightTurnMode) {
        double speedErrorFrontLeft  = targetSpeed - currentSpeedFrontLeft;
        double speedErrorFrontRight = targetSpeed - currentSpeedFrontRight;
        double speedErrorRearLeft   = targetSpeed - currentSpeedRearLeft;
        double speedErrorRearRight  = targetSpeed - currentSpeedRearRight;

        double rotationErrorFrontLeft  = targetRotation;
        double rotationErrorFrontRight = targetRotation;
        double rotationErrorRearLeft   = targetRotation;
        double rotationErrorRearRight  = targetRotation;

        if (isLeftTurnMode) {
            rotationErrorFrontLeft  -= currentSpeedFrontLeft;
            rotationErrorFrontRight -= currentSpeedFrontRight;
            rotationErrorRearLeft   -= currentSpeedRearLeft;
            rotationErrorRearRight  -= currentSpeedRearRight;
        }

        if (isRightTurnMode) {
            rotationErrorFrontLeft  += currentSpeedFrontLeft;
            rotationErrorFrontRight += currentSpeedFrontRight;
            rotationErrorRearLeft   += currentSpeedRearLeft;
            rotationErrorRearRight  += currentSpeedRearRight;
        }

        double outputFrontLeft = kpFrontLeft * speedErrorFrontLeft + kiFrontLeft * integralFrontLeft +
                                 kdFrontLeft * (speedErrorFrontLeft - prevErrorFrontLeft) + rotationErrorFrontLeft;

        double outputFrontRight = kpFrontRight * speedErrorFrontRight + kiFrontRight * integralFrontRight +
                                  kdFrontRight * (speedErrorFrontRight - prevErrorFrontRight) + rotationErrorFrontRight;

        double outputRearLeft = kpRearLeft * speedErrorRearLeft + kiRearLeft * integralRearLeft +
                                kdRearLeft * (speedErrorRearLeft - prevErrorRearLeft) + rotationErrorRearLeft;

        double outputRearRight = kpRearRight * speedErrorRearRight + kiRearRight * integralRearRight +
                                 kdRearRight * (speedErrorRearRight - prevErrorRearRight) + rotationErrorRearRight;

        frontLeftWheel  = outputFrontLeft;
        frontRightWheel = outputFrontRight;
        rearLeftWheel   = outputRearLeft;
        rearRightWheel  = outputRearRight;

        prevErrorFrontLeft = speedErrorFrontLeft;
        integralFrontLeft += speedErrorFrontLeft;

        prevErrorFrontRight = speedErrorFrontRight;
        integralFrontRight += speedErrorFrontRight;

        prevErrorRearLeft = speedErrorRearLeft;
        integralRearLeft += speedErrorRearLeft;

        prevErrorRearRight = speedErrorRearRight;
        integralRearRight += speedErrorRearRight;
    }
};

#endif  // MECANUM_HPP
