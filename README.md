# メカナムホイールの制御(PID,エンコーダー)

左/右回転モードを実装。
回転しながら動ける....はず

できるだけ見やすい/わかりやすいように書いたので後から訳わからなくなることはないと信じたい。

なおコントローラー側は~~めんどくさいので~~作っていない。

## 使用方法(デフォルトの値)

### PIDのゲイン

    double kp = 1.0;
    double ki = 0.1;
    double kd = 0.05;
 
### 速度

    double targetSpeed = 0.5;           // 目標速度
    double targetRotation = 0.2;        // 目標回転速度
    double targetRotationLeft = 0.2;    // 左回転時の目標回転速度
    double targetRotationRight = -0.2;  // 右回転時の目標回転速度

### 制御ピン(PWM)

    PinName frontLeftPin = PA_0;    //左前
    PinName frontRightPin = PA_1;   //右前
    PinName rearLeftPin = PA_2;     //左後
    PinName rearRightPin = PA_3;    //右後


## 進捗

5/29 メカナムの制御まで

+todo 通信・エンコーダー・コントローラー

