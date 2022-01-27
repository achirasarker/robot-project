int In1 = 7; //IN1 connected to D7 on arduino - right motor
int In2 = 8; //IN2 connected to D8 on arduino - left motor
int ENA = 5; //ENA connected to D5 on arduino
int SPEED = 240; //Initialize speed of motor

int triggerPin = 2;
int echoPin = 3;
long t;
int distance;

void setup() {
  Serial.begin(9600);

  //Arduino sends signal to sensor
  pinMode(triggerPin, OUTPUT); 
  //Arduino receives distance from sensor
  pinMode(echoPin, INPUT); 

  //Set all motor pins as output since arduino will send signals to the motor driver with these pins
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);

  //Since In1 and In2 pins decide polarity, we need to set one pin "HIGH" and the other "LOW"
  //Below is for clockwise direction
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

   //Set speed to 210
  //0 is lowest and 255 is highest speed
  analogWrite(ENA, SPEED);

}

void loop() {
  //Clear trigger pin by making it low for 2ms
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //Make it high for 10ms, so that sensor sends ultrasonic sound
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  //Clear trigger pin again
  digitalWrite(triggerPin, LOW);

  //Store time into the variable t
  t = pulseIn(echoPin, HIGH);
  //Distance is time*(speed/2) 
  //Speed of sound is 343m/second = 0.034cm/microsecond
  distance = t*0.034/2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  //If an object is in front of sensor, turn left
  if(distance <=20)
  {
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    //Greater the delay, more the robot turns left
    delay(500);
  }
  //Else keep moving
  else 
  {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
  }
  
}
