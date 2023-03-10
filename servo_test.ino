/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val = 0;    // variable to read the value from the analog pin 
int times = 0;  //轉的圈數

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(0);                  // sets the servo position according to the scaled value
  delay(5000);                           // waits for the servo to get there
  myservo.write(90);
  delay(50); //一定要delay，不用的話，servo就不會轉90度，而只會停留在0度
  exit(0); //跳離，這樣就會停止loop
  //下面是轉動用，不過應該用不到
//  val = val +10;
//  if(val>=180)
//  {
//    val = 0;
//    times++;
//    }
//  if(times>=3)
//     exit(0);//停止
}
