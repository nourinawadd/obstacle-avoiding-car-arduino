#include <Servo.h>

Servo myservo;
int pos = 0;

int trig = 7;
int echo = 8;
unsigned int t, d;

int pwm =1;

int rf = 3;
int rb = 5;
int lf = 6;
int lb = 9;

int disRight, disLeft;

int getdistance();

void setup() {
myservo.attach(11);
  // setting up ultrasound pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // setting up motor pins
  pinMode(rf, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(lf, OUTPUT);
  pinMode(lb, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  d = getdistance();

  if(d<50) //if there is an obstacle
  {
    // move back
    digitalWrite(rf, LOW);  
    digitalWrite(rb, HIGH);
    digitalWrite(lf, LOW);  
    digitalWrite(lb, HIGH);  
    delay(500);

    // stop the car
    digitalWrite(rf, LOW);  
    digitalWrite(rb, LOW);  
    digitalWrite(lf, LOW);  
    digitalWrite(lb, LOW);
    delay(500);
    
    // look right and get distance
    myservo.write(179);
    disRight = getdistance();
    delay(500);
    // look left and get distance
    myservo.write(2);
    disLeft = getdistance();
    delay(500);

    // compare
    if(disRight >= disLeft)
    {
      myservo.write(90);
      delay(1000);
      // move right
      digitalWrite(rf, HIGH);  
      digitalWrite(rb, LOW);  
      digitalWrite(lf, LOW);  
      digitalWrite(lb, HIGH);
      delay(200);
    }
    
    else
    {
      myservo.write(90);
      delay(1000);
      // move left
      digitalWrite(rf, LOW);  
      digitalWrite(rb, HIGH);  
      digitalWrite(lf, HIGH);  
      digitalWrite(lb, LOW);
      delay(200);  
    }
    }
    else
    {
      // move forward
      delay(1500);
      digitalWrite(rf, HIGH);  
      digitalWrite(rb, LOW);  
      digitalWrite(lf, HIGH);  
      digitalWrite(lb, LOW);  
      delay(3000);
    }

}
// get distance funtion
int getdistance()
{
digitalWrite(trig, 0);
delayMicroseconds(2);
digitalWrite(trig, 1);
delayMicroseconds(10);
digitalWrite(trig, 0);
t = pulseIn(echo, 1);
d = (t*0.034)/2;
delay(500);
return d;
}
