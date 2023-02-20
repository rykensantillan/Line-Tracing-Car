/*
   Ryken Santillan
   05/06/2022
   Code for Line-Tracing Robot 
   Project Members: George Chen, Jimmie So
*/

//-----Motor Connections

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

//-----LDR Connections
int valueMiddle = 0;
int valueRight = 0;
int middleSensor = A0;
int rightSensor = A1;

//-----LDR constant values
int blackMiddle = 200; //range for black tape
int blackRight = 200;

//-----Motor constant values
int turnSpeed = 80;
int straightSpeed = 70;

//-----Purpose: Initialize necessary components and their pins-----//
void setup() {

  //Set Photoresistors to Inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  //Set all motor control pins to output
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//-----Purpose: Infinite loop, keep robot in perpetual motion-----//
void loop() {
  detect(); //function to track LDR analog values
  movement(); //function for movement
}

//-----Purpose: Tracks LDR analog values and stores them into variables-----\\
void detect() { //sets LDRS
  valueMiddle = analogRead(A1);
  valueRight = analogRead(A0);
}

/*-----Purpose: Moves the robot depending on what LDRs detect-----
1.) Middle = Black, Right = White: Robot moves forward
2.) Middle = Black, Right = Black; Robot turns right until only middle is black
3.) Middle = White, Right = White, Robot turns left until middle reads black
*/
void movement() { 
  if (valueMiddle <= blackMiddle && valueRight > blackRight) { // ONLY middle = black
    //-- move straight
    analogWrite(enA, straightSpeed);  //set speed
    analogWrite(enB, straightSpeed);
    digitalWrite(in1,HIGH); //RIGHT MOTOR FORWARD ON
    digitalWrite(in2,LOW); //RIGHT MOTOR BACKWARD OFF
    digitalWrite(in3,HIGH);  //LEFT MOTOR FORWARD ON
    digitalWrite(in4,LOW);  //LEFT MOTOR BACKWARD OFF
  } else if (valueMiddle <= blackMiddle && valueRight <= blackRight) { // middle and right detect black
    //-- turn RIGHT
    analogWrite(enA, turnSpeed);  //set speed
    analogWrite(enB, turnSpeed);
    digitalWrite(in1,LOW); //RIGHT MOTOR FORWARD OFF
    digitalWrite(in2,HIGH); //RIGHT MOTOR BACKWARD ON
    digitalWrite(in3,HIGH);  //LEFT MOTOR FORWARD ON
    digitalWrite(in4,LOW);  //LEFT MOTOR BACKWARD OFF
  } else { //middle and right detect white
    Serial.println(turnLeft);
    analogWrite(enA, turnSpeed);  //set speed
    analogWrite(enB, turnSpeed);
    digitalWrite(in1,HIGH); //RIGHT MOTOR FORWARD OFF
    digitalWrite(in2,LOW); //RIGHT MOTOR BACKWARD ON
    digitalWrite(in3,LOW);  //LEFT MOTOR FORWARD ON
    digitalWrite(in4,HIGH);  //LEFT MOTOR BACKWARD OFF
  }
}
