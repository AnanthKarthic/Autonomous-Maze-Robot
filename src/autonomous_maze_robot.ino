/*
 * Autonomous Maze-Solving Robot
 *
 * Author: Ananth Karthic
 *
 * Description:
 * Arduino robot that autonomously navigates obstacles
 * using an ultrasonic sensor and a finite state machine.
 */


// Motor pins

// Right motor
const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;

// Left motor
const int BIN1 = 8;
const int BIN2 = 9;
const int PWMB = 10;


// Distance sensor

const int trigPin = 6;
const int echoPin = 5;


// RGB LED

const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;


// Buttons

const int startButton = 0;
const int stopButton = 7;


// Robot behavior

float distance = 0;

const int backupTime = 250;
const int turnRightTime = 340;
const int turnLeftTime = 700;

bool robotActive = false;


// State machine

enum RobotState {
  GO_STRAIGHT,
  TURN_RIGHT,
  CHECK_PATH,
  TURN_LEFT
};

RobotState state = GO_STRAIGHT;



void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(startButton, INPUT_PULLUP);
  pinMode(stopButton, INPUT_PULLUP);


  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);


  Serial.begin(9600);
  Serial.println("Robot Initialized");

  setLED(128,0,255);
}



void loop()
{

  if(digitalRead(startButton) == LOW)
  {
    robotActive = true;
  }


  if(digitalRead(stopButton) == LOW)
  {
    robotActive = false;
    stopMotors();
    setLED(128,0,255);
  }


  distance = getDistance();


  Serial.print("Distance: ");
  Serial.println(distance);



  if(!robotActive)
  {
    stopMotors();
    delay(200);
    return;
  }



  switch(state)
  {


    case GO_STRAIGHT:

      setLED(0,255,0);

      rightMotor(135);
      leftMotor(135);


      if(distance <= 4)
      {
        setLED(255,0,0);

        stopMotors();
        delay(300);

        rightMotor(-125);
        leftMotor(-125);

        delay(backupTime);

        state = TURN_RIGHT;
      }

      break;



    case TURN_RIGHT:

      rightMotor(-125);
      leftMotor(125);

      delay(turnRightTime);

      state = CHECK_PATH;

      break;



    case CHECK_PATH:


      rightMotor(100);
      leftMotor(100);

      delay(100);


      distance = getDistance();


      if(distance <= 11)
      {
        rightMotor(-125);
        leftMotor(-125);

        delay(backupTime);

        state = TURN_LEFT;
      }

      else
      {
        state = GO_STRAIGHT;
      }

      break;



    case TURN_LEFT:

      rightMotor(125);
      leftMotor(-125);

      delay(turnLeftTime);

      state = GO_STRAIGHT;

      break;

  }


  delay(200);

}




void rightMotor(int speed)
{

  if(speed > 0)
  {
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,LOW);
  }

  else if(speed < 0)
  {
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,HIGH);
  }

  else
  {
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,LOW);
  }


  analogWrite(PWMA, abs(speed));

}




void leftMotor(int speed)
{

  if(speed > 0)
  {
    digitalWrite(BIN1,HIGH);
    digitalWrite(BIN2,LOW);
  }

  else if(speed < 0)
  {
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,HIGH);
  }

  else
  {
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,LOW);
  }


  analogWrite(PWMB, abs(speed));

}




void stopMotors()
{
  rightMotor(0);
  leftMotor(0);
}




float getDistance()
{

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin,LOW);


  float echoTime = pulseIn(echoPin,HIGH);

  return echoTime / 148.0;

}




void setLED(int r, int g, int b)
{
  analogWrite(redPin,r);
  analogWrite(greenPin,g);
  analogWrite(bluePin,b);
}
