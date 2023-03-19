//這是控制2個servo和一個stepper的程式

#include <Servo.h>
#include <Stepper.h>

const int stepsPerRevolution = 2038;

Servo servo1;  
Servo servo2;
Stepper myStepper = Stepper(stepsPerRevolution, 4, 5, 6, 7); // 驅動板的 pin 1~4 接到 arduino 的pin 4~7

void setup() {
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);
}

void loop() {
  initial();        // 馬達位置歸零
  myStepper.setSpeed(5);
  myStepper.step(stepsPerRevolution);
  delay(2000);      // 執行後停止兩秒
  
  turn();    // 左右伺服馬達同樣各轉90度        
  delay(2000);      // 執行後停止兩秒
  
  
  exit(0); //跳離，這樣就會停止loop
  
}

/* 以下為副程式宣告 */

void initial(){
  servo1.write(0);
  servo2.write(0);
}

void turn() {
  servo1.write(90);
  servo2.write(90);
}
