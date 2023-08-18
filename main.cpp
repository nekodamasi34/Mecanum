#include "mbed.h"
#include "math.h"
#include <chrono>

#include "MbedHardwareSerial.hpp"
#include "SerialBridge.hpp"
#include "Controller.hpp"

#include "Encoder.hpp"
#include "Mecanum.hpp"
#include "md.hpp"
#include "pid.hpp"

const double PI = 3.141592653589;

SerialDev *dev = new MbedHardwareSerial(new BufferedSerial(PA_15, PB_7, 115200));
SerialBridge serial(dev, 1024);
Controller msc;

MecanumWheel mw;

/*
    [0] --→ 左前　 (FrontLeft)  [FL]
    [1] --→ 右前　 (FrontRight) [FR]
    [2] --→ 左後ろ (RearLeft)   [RL]
    [3] --→ 右後ろ (RearRight)  [RR]
*/

// 呼び出し
Encoder *encoder[4];
PID *pid[4];
MD *md[4];

// PID用周期調整 (ここを変えるならmainの最後の行も変える)
const double DELTA_T = 0.01;

void initialize_module();

int main() {
    initialize_module();

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

            // targetSpeedが1を超えないようにする
            if(targetSpeed > 1){
                targetSpeed = 1;
            }

            // targetRotationがマイナスにならないように2πたす
            if(targetRotation < 0){
                targetRotation += (2 * PI);
            }

            // 目標速度, 回転速度, 回転方向を設定
            mw.control(targetSpeed, targetRotation, LRturn);

            // PID制御
            pid[0]->control(encoder[0]->get_rps(), mw.getSpeed(0), DELTA_T);
            pid[1]->control(encoder[1]->get_rps(), mw.getSpeed(1), DELTA_T);
            pid[2]->control(encoder[2]->get_rps(), mw.getSpeed(2), DELTA_T);
            pid[3]->control(encoder[3]->get_rps(), mw.getSpeed(3), DELTA_T);

            // MD出力
            md[0]->drive(pid[0]->get_pid());
            md[1]->drive(pid[1]->get_pid());
            md[2]->drive(pid[2]->get_pid());
            md[3]->drive(pid[3]->get_pid());

            // 周期調整用 (ここを変えるならDELTA_Tも変える)
            ThisThread::sleep_for(10ms);



        }
    }
}

void initialize_module()
{
// PIDゲイン調整 {kp(比例), ki(積分), kd(微分)}
    pid[0] = new PID(1.0, 0.1, 0.05);
    pid[1] = new PID(1.0, 0.1, 0.05);
    pid[2] = new PID(1.0, 0.1, 0.05);
    pid[3] = new PID(1.0, 0.1, 0.05);

// エンコーダーの制御ピン (a, b)
    encoder[0] = new Encoder(PB_2, PA_11);
    encoder[1] = new Encoder(PC_5, PA_12);
    encoder[2] = new Encoder(PB_1, PC_8);
    encoder[3] = new Encoder(PA_6, PC_9);

// MDの制御ピン (pwmピン, dirピン, 逆転モード)
    md[0] = new MD(PA_10, PB_2,  0);
    md[1] = new MD(PB_3 , PC_11, 0);
    md[2] = new MD(PB_5 , PC_10, 0);
    md[3] = new MD(PB_4 , PC_12, 0);

}

