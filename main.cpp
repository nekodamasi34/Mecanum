#include "mbed.h"
#include "math.h"
#include <chrono>

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

/*
    [0] --→ 左前　 (FrontLeft)  [FL]
    [1] --→ 右前　 (FrontRight) [FR]
    [2] --→ 左後ろ (RearLeft)   [RL]
    [3] --→ 右後ろ (RearRight)  [RR]
*/

// PIDゲイン調整 {kp(比例), ki(積分), kd(微分)}
PID pid_0(1.0, 0.1, 0.05);
PID pid_1(1.0, 0.1, 0.05);
PID pid_2(1.0, 0.1, 0.05);
PID pid_3(1.0, 0.1, 0.05);

// PID用周期調整 (ここを変えるならmainの最後の行も変える)
double DELTA_T = 0.01;

// エンコーダーの制御ピン (a, b)
Encoder encoder_0(A0, D0);
Encoder encoder_1(A1, D1);
Encoder encoder_2(A2, D2);
Encoder encoder_3(A3, D3);

// MDの制御ピン (pwmピン, dirピン, 逆転モード)
MD md_0(PA_0, PA_4, 0);
MD md_1(PA_1, PA_5, 0);
MD md_2(PA_2, PA_6, 0);
MD md_3(PA_3, PA_7, 0);

int main() {

    serial.add_frame(0, &msc);

    while (1) {

        serial.update();

        if(msc.was_updated()){

        // Joystickの値を取得(値域を±0.5から±1にする)
        double joyXValue = (msc.data.x - 0.5) * 2;
        double joyYValue = (msc.data.y - 0.5) * 2;

        // ボタンの状態を取得(Lならマイナス,Rならプラス)
        double LRturn = msc.data.r - msc.data.l;

        // Joystickのベクトル化
        double targetSpeed    = sqrt(joyXValue * joyXValue + joyYValue * joyYValue);
        double targetRotation = atan2(msc.data.y, msc.data.x) - (PI /4);

        if(targetRotation < 0){
            targetRotation += (2 * PI);
        }

        // 目標速度, 回転速度, 回転方向を設定
        mw.control(targetSpeed, targetRotation, LRturn);

        // PID制御
        pid_0.control(encoder_0.get_rps(), mw.getSpeed(0), DELTA_T);
        pid_1.control(encoder_1.get_rps(), mw.getSpeed(1), DELTA_T);
        pid_2.control(encoder_2.get_rps(), mw.getSpeed(2), DELTA_T);
        pid_3.control(encoder_3.get_rps(), mw.getSpeed(3), DELTA_T);

        // MD出力
        md_0.drive(pid_0.get_pid());
        md_1.drive(pid_1.get_pid());
        md_2.drive(pid_2.get_pid());
        md_3.drive(pid_3.get_pid());

        // 周期調整用 (ここを変えるならDELTA_Tも変える)
        ThisThread::sleep_for(10ms);
        }     
    }
}
