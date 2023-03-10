#include <Unistep2.h>
//來源網址: https://blog.jmaker.com.tw/uln2003-28byj-48/
Unistep2 stepper(8, 9, 10, 11, 4096, 1000);// IN1, IN2, IN3, IN4, 總step數, 每步的延遲(in micros)

void setup()
{

}

void loop()
{
  stepper.run();  //步進機啟動

  if ( stepper.stepsToGo() == 0 ){ // 如果stepsToGo=0，表示步進馬達已轉完應走的step了
    delay(500);
    stepper.move(4096);    //正轉一圈
    //stepper.move(-4096);  //負數就是反轉，反轉一圈
  }

}
