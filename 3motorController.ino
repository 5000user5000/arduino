// 來源網址:https://sites.google.com/view/rayarduino/step-motor?pli=1
//==========================================================================

#include <Servo.h>
#include <Stepper.h>                        //含入程式庫 Stepper.h

const int stepsPerRevolution = 2048;        //設定步進馬達轉一圈為 2048步

Stepper myStepper = Stepper(stepsPerRevolution, 11, 9, 10, 8);       //因為步進馬達28BYJ-48 和程式庫 Stepper.h 的要求，這𥚃 9 和 10 不可互調 
Servo servo1;  //控制車體方向
Servo servo2;  //控制機翼升降

//定義伺服馬達腳位
#define servo1Pin 12 
#define servo2Pin 13 

#define servo1int 88 //定義伺服馬達1的初始位置，即為前輪方向置中的位置
#define servo2int 0  //定義伺服馬達2的初始位置，即為機翼未升起的位置

#define wheelDia 52 //輪子半徑(mm)

#define motorSpeed 15 //馬達轉速(PRM)

void setup() {
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
    myStepper.setSpeed(motorSpeed);   // 角速度(PRM)，範圍0~15。這裡設定為15，表示每分鐘轉15圈。(這裡還可以在測試如果插上電源的話的最大值)
}

void loop() {
    initial();        // 馬達位置歸零

    int steps = -1 * stepsPerRevolution;      //乘上-1表示前進

    for (int i = 0; i < 4; i++) {
        
        Stepper_forward(steps);
    
        if (i == 0) {
          Servo_turn(servo1int + 20); //車體左轉
        } 
        else if (i == 1) {
          Servo_turn(servo1int - 20); //車體右轉
        } 
        else if (i == 3) {
          Servo_updown(servo2int + 90); //機翼升起
        } 
        else {
          Servo_turn(servo1int); //車體直行
        }
    
    }
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
