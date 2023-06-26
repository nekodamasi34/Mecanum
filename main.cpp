#include "mbed.h"
#include "math.h"

#include <SerialBridge.hpp>
#include <MbedHardwareSerial.hpp>
#include <Controller.hpp>
#include <Counter.hpp>

#include <Mecanum.hpp>

SerialDev *dev = new MbedHardwareSerial(new Serial(D5, D4, 115200));
SerialBridge serial(dev, 1024);

Controller msc;

int main() {

    // メカナムホイールの制御ピン
    PinName FL_Pin = PA_0;
    PinName FR_Pin = PA_1;
    PinName RL_Pin = PA_2;
    PinName RR_Pin = PA_3;

    // エンコーダーの制御ピン
    PinName encoder_FL_Pin = A0;
    PinName encoder_FR_Pin = A1;
    PinName encoder_RL_Pin = A2;
    PinName encoder_RR_Pin = A3;

    // PID制御ゲイン
    double kpFL = 1.0;
    double kiFL = 0.1;
    double kdFL = 0.05;

    double kpFR = 1.0;
    double kiFR = 0.1;
    double kdFR = 0.05;

    double kpRL = 1.0;
    double kiRL = 0.1;
    double kdRL = 0.05;

    double kpRR = 1.0;
    double kiRR = 0.1;
    double kdRR = 0.05;

    // メカナムホイールの制御オブジェクトの作成
    MecanumWheel mecanumWheel(FL_Pin, FR_Pin, RL_Pin, RR_Pin,
                              kpFL, kiFL, kdFL,
                              kpFR, kiFR, kdFR,
                              kpRL, kiRL, kdRL,
                              kpRR, kiRR, kdRR);

    serial.add_frame(0, &msc);

    while (1) {

        serial.update();

        if(msc.was_updated()){
        // Joystickの値を取得
        double joyXValue = msc.data.x;
        double joyYValue = msc.data.y;

        // ボタンの状態を取得
        bool isLeftTurnMode  = msc.data.l;
        bool isRightTurnMode = msc.data.r;

        // 目標速度と回転速度の計算
        double targetSpeed = sqrt(joyXValue * joyXValue + joyYValue * joyYValue);
        double targetRotation = joyXValue;

        // 横方向速度と斜め方向速度の計算
        double targetSidewaysSpeed = joyXValue;
        double targetDiagonalSpeed = joyYValue;

        // 目標速度と回転速度を設定
        mecanumWheel.setTarget(targetSpeed, targetRotation, targetSidewaysSpeed, targetDiagonalSpeed);

        // 現在の速度の取得（センサーやエンコーダーから取得するなど）
        double currentSpeedFrontLeft  = 0.0;
        double currentSpeedFrontRight = 0.0;
        double currentSpeedRearLeft   = 0.0;
        double currentSpeedRearRight  = 0.0;

        // PID制御による速度制御
        mecanumWheel.controlSpeed(currentSpeedFrontLeft, currentSpeedFrontRight,
                                  currentSpeedRearLeft, currentSpeedRearRight,
                                  isLeftTurnMode, isRightTurnMode);

        // 10ms待つ
        ThisThread::sleep_for(10);
        // do

        }
        
    }
    
}