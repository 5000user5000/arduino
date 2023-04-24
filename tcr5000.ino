

  
int AnalogPin1 = A0;
int AnalogPin2 = A1;
int AnalogPin3 = A2;
int AnalogPin4 = A3;
      

void setup()
{
  Serial.begin(115200);
  //pinMode(DigitalPin1, INPUT); // 設定數位Pin為輸入
  pinMode(AnalogPin1, INPUT); // 設定類比Pin為輸入  
  pinMode(AnalogPin2, INPUT); // 設定類比Pin為輸入  
  pinMode(AnalogPin3, INPUT); // 設定類比Pin為輸入  
  pinMode(AnalogPin4, INPUT); // 設定類比Pin為輸入  
 
}
void loop()
{
  //boolean D_val = digitalRead(DigitalPin1); // 讀取數位Pin的值
  int A_val = analogRead(AnalogPin1);
  int A_val2 = analogRead(AnalogPin2);
  int A_val3 = analogRead(AnalogPin3);
  int A_val4 = analogRead(AnalogPin4);

  Serial.print("Analog data1 = "+A_val);
  Serial.print(" data2 = "+A_val2);
  Serial.print(" data3 = "+A_val3);
  Serial.print(" data4 = "+A_val4);
  Serial.println("=========");//隔開
  // Serial.println(A_val); 
  //測試用
  if(A_val>300)
  {
     Serial.println("black");
  }
  else
  {
     Serial.println("white");
    }

  delay(300); 
}
