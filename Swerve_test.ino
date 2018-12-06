#include <Servo.h>
#include <WemosInit.h>

/*Pin Definitions: 
 * Echo/Trig belong to the ultrasonic sensor
 * m1 and m2 belong to motor 1 (left) and motor 2 (right) respectively
 */
#define Echo D5
#define Trig D4 
#define m2   D2
#define m1   D3

//initialize the motor objects
Servo motor1;
Servo motor2;

enum states {STRAIGHT, TURN}; //all possible things the bot could do
int phase = 0; //represents what state the bot is currently in
bool debug = true; //if true: prints states to the serial monitor
int lStop = 82; //"stops" trimmed for drift so the bot drives straight
int rStop = 90; 
int throttle = 29;

/*Initialization procedure:
 * Setup motors, stop the bot from moving, connect any sensors, setup debugging
 */
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
  if(ultrasonicPing(Trig,Echo) < 900){ //check if obstacle is roughly 4in away, start turning procedure if true
    phase = TURN;
  }
  else{
    phase = STRAIGHT;
  }
  if (phase == TURN) { //if an object close, go right, then straight, then left
    int t = 1500; //default unit of time to uniformly allow bot to turn, adjust variable for changing turn radius
    motor1.write(97);
    motor2.write(97); //turn right
    delay(t);
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle); //go straight
    delay(t/2);
    motor1.write(86);
    motor2.write(86); //turn left
    delay(t);
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle); //go straight
    if(debug){Serial.println("swerve");}
  }
  else if(phase == STRAIGHT){ //otherwise go straight
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle);
    if(debug){Serial.println("moving forward");}
  }
  if(debug){Serial.println(ultrasonicPing(Trig,Echo));}
}
