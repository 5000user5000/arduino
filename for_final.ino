#include <Servo.h>

// for 42 stepper
#define dirPin 2
#define stepPin 3
#define wheelDia 52 //輪子直徑(mm)
const int spr = 200; //一圈 200 steps (steps per round)
const int total_steps = 1000 / (52 * 3.1416) * spr; //走1公尺所需的steps
int pulse_speed;//數字越小stepper越快，最快可以調到400 (車速)

//TCR5000 循跡
const int AnalogPin1 = A0;
const int AnalogPin2 = A1;
const int AnalogPin3 = A2;
const int AnalogPin4 = A3;
const int threshold  = 300 ; //判斷黑白的門檻，當類比讀值超過門檻就算黑色，其餘白色。(得實際測試才知道多少) 

Servo servo1;  //控制車體方向
Servo servo2;  //控制機翼升降

//定義伺服馬達腳位
#define servo1Pin 12 
#define servo2Pin 13 

#define servo1int 83 //定義伺服馬達1的初始位置，即為前輪方向置中的位置
#define servo2int 10  //定義伺服馬達2的初始位置，即為機翼未升起的位置

#define wingrise 125 //機翼升起的角度

//可變電阻
const int VR = A4;
int m_speed; A4腳位類比數值，用來換算成車速

//函數宣告
void initial(int delaytime=5000);
void Stepper_forward(int steps,int delaytime=1000);
void Servo_turn(int angle,int delaytime=1000);
void Servo_updown(int current_angle ,int next_angle,int delaytime=250);
void track_finging(int steps);

void setup() {
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);

    //42 stepper
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    //TCR5000
    Serial.begin(115200);
    pinMode(AnalogPin1, INPUT); // 設定類比Pin為輸入  
    pinMode(AnalogPin2, INPUT);   
    pinMode(AnalogPin3, INPUT);  
    pinMode(AnalogPin4, INPUT); 


}

void loop() {
    initial();        // 馬達位置歸零
    
    Stepper_forward(total_steps); //前進1m，剛好能到風區起點
    delay(2000); //讓load cell紀錄當前重量
    
    Servo_updown(servo2int , servo2int + wingrise , 50); //機翼升起
    delay(3000); //讓load cell紀錄當前重量
    
    Stepper_forward(total_steps); //前進1m
    Servo_updown(servo2int + wingrise , servo2int , 50); //收起機翼
    exit(0); //跳離
  
}

//回到初始位置
void initial(int delaytime=5000){
    servo1.write(servo1int);
    servo2.write(servo2int);
    delay(delaytime);      // 預設等待5秒
}
//步進馬達前進
void Stepper_forward(int steps,int delaytime=1500)
{
    digitalWrite(dirPin, HIGH); // 設定轉向為前進
    
    mspeed = analogRead(A4); //讀取可變電阻的類比訊號值
    pulse_speed = map(mspeed, 0, 1023, 500, 3000); //將訊號值轉成車速
    
    // Spin motor quickly，發出pulse(High->delay->Low->delay，即為一次pulse )，其間的delay越短，pulse的頻率越高，stepper轉速越快。1個steps = 1個脈衝，轉1.8度，頻率500 Hz->150 
    for(int x = 0; x < steps; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulse_speed); 
      digitalWrite(stepPin, LOW);
      delayMicroseconds(pulse_speed);
    }
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

//TCR5000，循跡演算法，可用可不用
void track_finging(int steps)
{
  //4個TCR5000讀值，這裡假定A是車體最左邊，依序到D最右邊。
  int A = analogRead(AnalogPin1);
  int B = analogRead(AnalogPin2);
  int C = analogRead(AnalogPin3);
  int D = analogRead(AnalogPin4);

  int angle = 10;//當偏離時，矯正回去的角度

  //輸出值
//  Serial.print("Analog data1 = ");
//  Serial.println(A);
//  Serial.print(" data2 = ");
//  Serial.println(B);
//  Serial.print(" data3 = ");
//  Serial.println(C);
//  Serial.print(" data4 = ");
//  Serial.println(D);
//  Serial.println("=========");//隔開

  //假設B、C都會接觸到黑線，A、D不會。
  //如果在正常軌道的話，就直直走
  if( B > threshold || C > threshold)  
  {
    //servo1.write(servo1int);
    Stepper_forward(steps);
    
    }
  //車往右偏
  else if( A > threshold)
  {
    servo1.write(servo1int-angle); //往左轉
    Stepper_forward(0.5*steps);
    servo1.write(servo1int); //調回原本的角度
    Stepper_forward(0.5*steps);
    
    }
   //車往左偏
  else if( D > threshold)
  {
    servo1.write(servo1int+angle); //往右轉
    Stepper_forward(0.5*steps);
    servo1.write(servo1int); //調回原本的角度
    Stepper_forward(0.5*steps);
    
    }
  //這個是完全沒看到白線
  else
  {
    //構思中...
    }
  
}
