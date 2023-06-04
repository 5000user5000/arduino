#include <Servo.h>

// for 42 stepper
#define dirPin 2
#define stepPin 3
#define wheelDia 52 //輪子直徑(mm)
const int spr = 200; //一圈 200 steps (steps per round)
const float total_steps = 1000 / (52 * 3.1416) * spr; //走1公尺所需的steps
int pulse_speed;//數字越小stepper越快，最快可以調到400 (車速)


Servo servo1;  //控制車體方向
Servo servo2;  //控制機翼升降

Servo servoL;  //控制左輪
Servo servoR;  //控制右輪

//定義伺服馬達腳位
#define servoLPin 4 //左前輪伺服馬達
#define servoRPin 5 //右前輪伺服馬達
#define servo1Pin 12 //轉向伺服馬達
#define servo2Pin 13 //機翼升降伺服馬達

#define servo1int 81 //定義伺服馬達1的初始位置，即為前輪方向置中的位置
#define servo2int 10  //定義伺服馬達2的初始位置，即為機翼未升起的位置

#define wingrise 125 //機翼升起的角度

//可變電阻
const int VR = A4;
int m_speed; //A4腳位類比數值，用來換算成車速

//函數宣告
void initial(int delaytime=5000);
void Stepper_forward(int steps,int delaytime=1000);
void Servo_turn(int angle,int delaytime=1000);
void Servo_updown(int current_angle ,int next_angle,int delaytime=250);
void track_finging(int steps);

void setup() {
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);

    servoL.attach(servoLPin);
    servoR.attach(servoRPin);

    //42 stepper
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

}

void loop() {
    initial();        // 馬達位置歸零

    Servo_updown(servo2int , servo2int + wingrise , 50); //機翼升起
    delay(500);
    
    Stepper_forward(total_steps * 2, 1500); //前進
    delay(2000); //讓load cell紀錄當前重量
    
    Servo_turn(servo1int + 40); //左轉
    
    Stepper_forward(total_steps * 0.4, 1500); //前進1m
    Servo_updown(servo2int + wingrise , servo2int , 50); //收起機翼
    
    exit(0); //跳離
}

//回到初始位置
void initial(int delaytime=5000){
    servo1.write(servo1int);
    servo2.write(servo2int);
    delay(delaytime);      // 預設等待5秒
}
//前進
void Stepper_forward(int steps,int delaytime)
{
    digitalWrite(dirPin, HIGH); // 設定轉向為前進
    
    m_speed = analogRead(A4); //讀取可變電阻的類比訊號值
    pulse_speed = map(m_speed, 0, 1023, 500, 3000); //將訊號值轉成車速
    
    // Spin motor quickly，發出pulse(High->delay->Low->delay，即為一次pulse)，其間的delay越短，pulse的頻率越高，stepper轉速越快。1個steps = 1個脈衝，轉1.8度，頻率500 Hz->150 
    for(int x = 0; x < steps; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulse_speed); 
      digitalWrite(stepPin, LOW);
      delayMicroseconds(pulse_speed);
      servoL.write(180); //最快轉速
      servoR.write(20);  //右輪慢些
      delayMicroseconds(pulse_speed);
      
    }
    servoL.write(90);
    servoR.write(90);
    delay(delaytime); // Wait a second
}

//servo 轉彎，角度越大就是往左轉
void Servo_turn(int angle,int delaytime=1000)
{
    servo1.write(angle);
    delay(delaytime);
}

//servo 升降，並把要上升的角度分拆成50份去上升，比較穩定
void Servo_updown(int current_angle ,int next_angle,int delaytime)
{
    int angle_change = next_angle - current_angle; //需要變動的角度
    for (float ratio = 0.02 ; ratio <= 1; ratio+=0.02) 
    {
        servo2.write(current_angle+ratio*angle_change);
        delay(delaytime);
     }
}
