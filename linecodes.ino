// Group 16: Cyberspace 
// Teamwork Fabrication assignment
// Given the input of black or white from IR sensors, activate the attached motors to make proper adjustments
//
// define pins for H-bridge motors and sensors:
//
// enabler pins
#define enA 6 // right motor (i think)
#define enB 5 // left motor (i think)

// right motor 1 pins
#define in1 7 
#define in2 8 

// left motor 2 pins
#define in3 9 
#define in4 10 

// ir sensors
#define rightSensor 11// ir sensor right
#define leftSensor 12 // ir sensor left

// speed values - t for turn s for straight
int spT = 160;
int spS = 200;

void setup() // configures pin modes to either input or output and activates motor control
{ 

  TCCR0B = TCCR0B & B11111000 | B00000010 ;

  // declares sensors as an input
  pinMode(rightSensor, INPUT); 
  pinMode(leftSensor, INPUT); 

  // declares enA pin as an output
  pinMode(enA, OUTPUT); 
  // declares motor pins as outputs
  pinMode(in1, OUTPUT); // right motor forward
  pinMode(in2, OUTPUT); // right motor backward 
  pinMode(in3, OUTPUT); // left motor backward
  pinMode(in4, OUTPUT); // left motor forward
  // declares enB pin as output
  pinMode(enB, OUTPUT);
  // enable motor control by activating enable pins
  digitalWrite(enA, HIGH); 
  digitalWrite(enB, HIGH); 

  // delay(1000);

  Serial.begin(1500);
}


void loop() // constantly loops to check values of sensors, and calls the referenced function given the input
{  
  // find correct wheel adjustment function based on color
  if((digitalRead(rightSensor) == LOW) and (digitalRead(leftSensor) == LOW)) // if right sensor and left sensor are at white
    {
      forward(); // call forward function
      Serial.println("Forward");
    }   

  if((digitalRead(rightSensor) == LOW) and (digitalRead(leftSensor) == HIGH)) // if right sensor is black and left sensor is white
    {
      right(); // call right function
      Serial.println("Right");
    } 

  if((digitalRead(rightSensor) == HIGH) and (digitalRead(leftSensor) == LOW)) // if right sensor is white and left sensor is black
    {   
      left(); // call left function
      Serial.println("Left");
    }

  if((digitalRead(rightSensor) == HIGH) and (digitalRead(leftSensor) == HIGH)) // if right sensor and left sensor are black
    {
      stop(); // call stop function
      Serial.println("Stop");
    } 

}

void forward() // moves the robot forward by activating the forward pin on both motors
{  
  // right motor
  digitalWrite(in1, HIGH ); // forward is turned on
  digitalWrite(in2, LOW);  // backwards is turned off
  // left motor
  digitalWrite(in3, HIGH);  // backward is turned off 
  digitalWrite(in4, LOW); // forward is turned on
  // set speeds for motor
  analogWrite(enA, spS); 
  analogWrite(enB, spS);
}

void left() // turns the robot left by activating the right motor while reversing the left
{ 
  // right motor
  digitalWrite(in1, LOW);  // forward is turned on
  digitalWrite(in2, HIGH); // backwards is turned off 
  // left motor
  digitalWrite(in3, HIGH);  // backward is turned off  
  digitalWrite(in4, LOW); // forward is turned on 
  // set speeds for motor
  analogWrite(enA, spS); 
  analogWrite(enB, spT);
}

void right() // turns the robot left by activating the right motor while reversing the left
{
  // right motor
  digitalWrite(in1, HIGH); // forward is turned on 
  digitalWrite(in2, LOW);  // backwards is turned off
  // left motor
  digitalWrite(in3, LOW); // backward is turned off 
  digitalWrite(in4, HIGH);  // forward is turned on
  // set speeds for motor
  analogWrite(enA, spT); 
  analogWrite(enB, spS);
}

void stop() // stops the robot by turning off all motor activity
{ 
  // right motor
  digitalWrite(in1, LOW); // forward is turned off
  digitalWrite(in2, LOW); // backwards is turned off
  // left motor
  digitalWrite(in3, LOW); // backward is turned off 
  digitalWrite(in4, LOW); // forward is turned off

  analogWrite(enA, 0); 
  analogWrite(enB, 0);
}

