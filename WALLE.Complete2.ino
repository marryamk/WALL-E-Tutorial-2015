#define trigPin 13
#define echoPin 12
#include <Servo.h> 

/////////////////LIGHTS///////////////
int redPin1 = 6; //red cable
int greenPin1 = 10; //blue cable
int bluePin1 = 7; // yellow cable
int redPin2 = 11; //white cable
int greenPin2 = 9; //orange cable
int bluePin2 = 8; // blue cable
/////////////////END///////////////

/////////////////HANDS///////////////
int servo1Pin = 5;
int servo2Pin = 4;
int handPos = 0; // Set initial hads position
Servo myservo1;  // Create RIGHT HAND
Servo myservo2;  // Create LEFT HAND
/////////////////END///////////////

/////////////////HEAD///////////////
int servo3Pin = 2;
//int servo4Pin = 3;
int headPos = 0; // Set initial hads position
Servo myservo3;  // Create HEAD
//Servo myservo4;
/////////////////END///////////////

int pos = 0; 

void setup() 
{
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redPin1, OUTPUT);
    pinMode(greenPin1, OUTPUT);
    pinMode(bluePin1, OUTPUT);  
    pinMode(redPin2, OUTPUT);
    pinMode(greenPin2, OUTPUT);
    pinMode(bluePin2, OUTPUT);
    
    myservo1.attach(servo1Pin);
    myservo2.attach(servo2Pin);
    
    myservo3.attach(servo3Pin);
    //myservo4.attach(servo4Pin);
}

void loop()
{
    eyeMood(); //Separate function used for better code flexibility
    
}

/////////////////HANDS///////////////

//Put the hands up
void handsUP()
{
    for(handPos; handPos <= 180; handPos++) // hands moving UP
    {
        //Put right hand UP
        myservo1.write(handPos);
        //Reverse motion for left hand to go up as well
        myservo2.write(180-handPos); 
        //Set motion speed
        delay(10);
    }
}

//Put the hands down
void handsDOWN()
{
    for(handPos; handPos >= 0; handPos--)
    {                                
        myservo1.write(handPos);
        myservo2.write(180-handPos);
        delay(10);
    }
}


/////////////////HEAD///////////////
void headUP()
{
    for(headPos; headPos <= 50; headPos++) // head moving UP
    {
        myservo3.write(headPos);
        //myservo4.write(50-headPos); 
        delay(20);
    }
}

void headDOWN()
{
    for(headPos; headPos >= 0; headPos--)
    {                                
        myservo3.write(headPos);
        //myservo4.write(50-headPos);
        delay(20);
    }
}

/////////////////EYES///////////////

//Make BLUE eyes
void blueEyes()
{
    setColor(0, 0, 255); //blue 
}

//Make GREEN eyes
void greenEyes()
{
    setColor(0, 255, 0); //green
}

//Make RED eyes
void redEyes()
{
    setColor(255, 0, 0); //red
}

//Make eyes OFF
void eyesOff()
{
   setColor(0, 0, 0); //off
}

/////////////////GENERAL///////////////

//Change eye color depending on the distance to closest obstacle
void eyeMood()
{
    long duration, distance;      
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW );
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
  
    if (distance <= 10) 
    {
        redEyes();
        handsUP();
        headDOWN();
    } 

    else if (distance > 10 && distance <= 15) 
    {
        greenEyes();
        handsDOWN();
        headUP();
    }

    else if (distance > 15 && distance <= 30) 
    { 
        blueEyes();
    }
    else if (distance >= 30)
    {   
      eyesOff();
      handsDOWN();
      headDOWN();
    }
    delay(200);
}
//Turn the proper color ON
void setColor(int red, int green, int blue)
{
    analogWrite(redPin1, red);
    analogWrite(greenPin1, green);
    analogWrite(bluePin1, blue);  
    analogWrite(redPin2, red);
    analogWrite(greenPin2, green);
    analogWrite(bluePin2, blue); 
}
