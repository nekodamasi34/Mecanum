#include "mbed.h"
#include "math.h"
#include "Ticker.h"

#include <SerialBridge.hpp>
#include <MbedHardwareSerial.hpp>
#include <Controller.hpp>
#include <Encoder.hpp>

#include <Mecanum.hpp>
#include <md.hpp>
#include <pid.hpp>

const double PI = 3.141592653589;

SerialDev *dev = new MbedHardwareSerial(new Serial(D5, D4, 115200));
SerialBridge serial(dev, 1024);

Controller msc;

MecanumWheel mw;
pid pid;
Encoder Encoder;

MD md1(PA_0, PA_4);
MD md2(PA_1, PA_5);
MD md3(PA_2, PA_6);
MD md4(PA_3, PA_7);

int main() {

    /*
        [0] --→ 左前　 (FrontLeft)  [FL]
        [1] --→ 右前　 (FrontRight) [FR]
        [2] --→ 左後ろ (RearLeft)   [RL]
        [3] --→ 右後ろ (RearRight)  [RR]
    */

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

    // 途中計算,最終結果用
    double roll[4];

    // 現在速度
    double current[4];

    // pid.hpp用
    double feedback_val[4], target_val[4], error_now[4], error_behind[4], integral[4];
    double DELTA_T; //積分用周期

    serial.add_frame(0, &msc);

    while (1) {

        serial.update();

        if(msc.was_updated()){

        // Joystickの値を取得
        double joyXValue = (msc.data.x - 0.5) * 2;
        double joyYValue = (msc.data.y - 0.5) * 2;

        // ボタンの状態を取得
        double Lturn = msc.data.l;
        double Rturn = msc.data.r;

        // 目標速度と回転速度の計算
        double targetSpeed = sqrt(joyXValue * joyXValue + joyYValue * joyYValue);
        double targetRotation = atan2(msc.data.y, msc.data.x) + PI/2;


        // 目標速度と回転速度を設定
        mw.control(targetSpeed, targetRotation, Lturn, Rturn);

        // 現在の速度の取得（エンコーダー）
        for(int i = 0; i <= 3, i++){
            current[i] = 0;
        }

        // PID制御

        for(int i = 0; i <= 3, i++){
            pid.control(feedback_val[i], target_val[i], error_now[i], error_behind[i], integral[i], DELTA_T);
        }
   
        // 10ms待つ
        ThisThread::sleep_for(20ms);
        // do

        FL, FR, RL, RR = 0;

        }
        
    }
    
}