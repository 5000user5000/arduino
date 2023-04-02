// 來源網址:https://sites.google.com/view/rayarduino/step-motor?pli=1
//==========================================================================

#include <Servo.h>
#include <Stepper.h>                        //含入程式庫 Stepper.h
const int stepsPerRevolution = 2048;        //設定步進馬達轉一圈為 2048步

Stepper myStepper = Stepper(stepsPerRevolution, 11, 9, 10, 8);       //因為步進馬達28BYJ-48 和程式庫 Stepper.h 的要求，這𥚃 9 和 10 不可互調
Servo servo1;  
Servo servo2;

#define servo1Pin 12 //定義伺服馬達腳位
#define servo2Pin 13 

#define servo1int 88 //定義伺服馬達1的初始位置，即為前輪方向置中的位置
#define servo2int 0  //定義伺服馬達2的初始位置，即為機翼未升起的位置

#define wheelDia 52 //輪子半徑(mm)

void setup() {
 servo1.attach(servo1Pin);
 servo2.attach(servo2Pin);
}

void loop() {
  initial();        // 馬達位置歸零
  delay(5000);      // 等待5秒
  
  myStepper.setSpeed(15);                   // 角速度(PRM)，範圍0~15
  myStepper.step(-1 * stepsPerRevolution);  //乘上-1表示前進
  delay(1000);                              // 執行後停止2秒

  servo1.write(servo1int + 20);             //車體左轉       
  delay(1000);

  myStepper.setSpeed(15);
  myStepper.step(-1 * stepsPerRevolution);
  delay(1000);

  servo1.write(servo1int - 20);             //車體右轉 
  delay(1000);
  
  myStepper.setSpeed(15);
  myStepper.step(-1 * stepsPerRevolution);
  delay(1000);   

  servo1.write(servo1int);                  //車體直行
  delay(1000);
  
  myStepper.setSpeed(15);
  myStepper.step(-1 * stepsPerRevolution);
  delay(1000);   

  servo2.write(servo2int + 90);             //機翼升起
  delay(1000);

  myStepper.setSpeed(15);
  myStepper.step(-4 * stepsPerRevolution);
  delay(1000);   
}

void initial(){
  servo1.write(servo1int);
  servo2.write(servo2int);
}
