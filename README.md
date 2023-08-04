# メカナムホイールの制御(PID,エンコーダー)

左/右回転モードを実装。
回転しながら動ける....はず

できるだけ見やすい/わかりやすいように書いたので後から訳わからなくなることはないと信じたい。

なおコントローラー側は~~めんどくさいので~~まだ作っていない。

基本的にSerialBridgeを使用しての通信を想定しています。

おびただしい量(15/105)のエラーをはいているのでまだ使えない(7/11現在)

## 使用方法(デフォルトの値)

### PIDのゲイン

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
 
### 速度・方向

        // Joystickの値を取得
        double joyXValue = (msc.data.x - 0.5) * 2;
        double joyYValue = (msc.data.y - 0.5) * 2;

        // ボタンの状態を取得
        double Lturn = msc.data.l;
        double Rturn = msc.data.r;

        // Joystickの制御
        double targetSpeed = sqrt(joyXValue * joyXValue + joyYValue * joyYValue);
        double targetRotation = atan2(msc.data.y, msc.data.x);

(Joystickを90°回転させて使うが無難)

### 制御ピン(PWM,DIR)

    MD md1(PA_0, PA_4);   //左前
    MD md2(PA_1, PA_5);   //右前
    MD md3(PA_2, PA_6);   //左後ろ
    MD md4(PA_3, PA_7);   //右後ろ

### エンコーダーの制御ピン

    PinName encoder_FL_Pin = A0;
    PinName encoder_FR_Pin = A1;
    PinName encoder_RL_Pin = A2;
    PinName encoder_RR_Pin = A3;

## 進捗

7/10 pidなど

+todo メカナム制御・エンコーダー・コントローラー

