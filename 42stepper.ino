// for 42 stepper
#define dirPin 2
#define stepPin 3
int pulse_speed;
int mspeed;

void setup() {
    Serial.begin (9600);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

}

void loop() {
  mspeed = analogRead(A4); //可變電阻
  pulse_speed = map(mspeed, 0, 1023, 500, 3000);
  Serial.println(pulse_speed);
  digitalWrite(dirPin, HIGH);
  for(int x = 0; x < 200; x++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulse_speed); 
      digitalWrite(stepPin, LOW);
      delayMicroseconds(pulse_speed);
    }
    delay(1500); // Wait a second
}
