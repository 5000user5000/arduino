// 來源網址:https://sites.google.com/view/rayarduino/step-motor?pli=1
//==========================================================================

#include <Servo.h>
#include <Stepper.h>                        //含入程式庫 Stepper.h

const int stepsPerRevolution = 2048;        //設定步進馬達轉一圈為 2048步

Stepper myStepper = Stepper(stepsPerRevolution, 11, 9, 10, 8);       //因為步進馬達28BYJ-48 和程式庫 Stepper.h 的要求，順序為 pin1/pin3/pin2/pin4
Servo servo1;  //控制車體方向
Servo servo2;  //控制機翼升降

//定義伺服馬達腳位
#define servo1Pin 12 
#define servo2Pin 13 

#define servo1int 83 //定義伺服馬達1的初始位置，即為前輪方向置中的位置 ， 經測試83跑動才是直線
#define servo2int 0  //定義伺服馬達2的初始位置，即為機翼未升起的位置

#define wingrise 100 //機翼升起的角度

#define wheelDia 52 //輪子直徑(mm)

#define motorSpeed 15 //馬達轉速(PRM)

//函數宣告
void initial(int delaytime=5000);
void Stepper_forward(int steps,int delaytime=1000);
void Servo_turn(int angle,int delaytime=1000);
void Servo_updown(int angle,int delaytime=1000);

void setup() {
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
    myStepper.setSpeed(motorSpeed);   // 角速度(PRM)，範圍0~15。這裡設定為15，表示每分鐘轉15圈。(這裡還可以在測試如果插上電源的話的最大值，max 20)
}

void loop() {
    initial();        // 馬達位置歸零

    int steps = -1 * stepsPerRevolution;      //乘上-1表示前進
    
    Stepper_forward(5.5*steps); //輪胎轉一圈約16.3cm，到163cm左右(至少大於150)時再升起。
    Servo_updown(servo2int + wingrise); //機翼升起
    Stepper_forward(3.5*steps); 
    Servo_updown(servo2int); //收起
    exit(0); //跳離

}

//回到初始位置
void initial(int delaytime=5000){
    servo1.write(servo1int);
    servo2.write(servo2int);
    delay(delaytime);      // 預設等待5秒
}
//步進馬達前進
void Stepper_forward(int steps,int delaytime=1000)
{
    myStepper.step(steps);
    delay(delaytime);
}

//servo 轉彎
void Servo_turn(int angle,int delaytime=1000)
{
    servo1.write(angle);
    delay(delaytime);
}

//servo 升降
void Servo_updown(int angle,int delaytime=1000)
{
    servo2.write(angle);
    delay(delaytime);
}
