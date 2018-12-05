#include <Servo.h>
#include <WemosInit.h>

#define Echo D5
#define Trig D4 
#define m2   D2
#define m1   D3
Servo motor1;
Servo motor2;
int state = 0; // 0 = forward, 1 = turning
bool debug = true;
int lStop = 82;
int rStop = 90;
int throttle = 29;

void setup() {
  motor1.attach(m1);
  motor2.attach(m2);
  motor1.write(90);
  motor2.write(90);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  if(debug){Serial.begin(9600);}
}

void loop() {
  if(ultrasonicPing(Trig,Echo) < 900){ //check if obstacle is roughly 4in away
    state = 1;
  }
  else{
    state = 0;
  }
  if (state == 1) { //if its close, go right, then straight, then left
    int t = 1500;
    motor1.write(97);
    motor2.write(97);
    delay(t);
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle);
    delay(t/2);
    motor1.write(86);
    motor2.write(86);
    delay(t);
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle);
    if(debug){Serial.println("swerve");}
  }
  else if(state == 0){ //otherwise go straight
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle);
    if(debug){Serial.println("moving forward");}
  }
  if(debug){Serial.println(ultrasonicPing(Trig,Echo));}
}


