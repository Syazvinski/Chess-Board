//screen prerequesets
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// defining stepper pin numbers
const int stepPinX = 3; 
const int dirPinX = 52; 

const int stepPinY = 2; 
const int dirPinY = 53; 

//defining magnet pin
const int magPin = 22;

//buzzer pin
const int buzzPin = 50;

//limit swtiches
const int limitX = 45;
const int limitY = 46;

//3 buttons
const int leftButton = 40;
const int rightButton = 41;
const int goButton = 42;

//

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {

  // Write to display
  lcd.setCursor(4,2);
  lcd.print("Initializing");

  //start serial connection
  Serial.begin(9600);

  // Setting stepper pins as output
  pinMode(stepPinX,OUTPUT); 
  pinMode(dirPinX,OUTPUT);

  pinMode(stepPinY,OUTPUT); 
  pinMode(dirPinY,OUTPUT);

  // setting magent pin as output
  pinMode(magPin,OUTPUT);

  //limit switches
  pinMode(limitX,INPUT_PULLUP);
  pinMode(limitY,INPUT_PULLUP);

  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight
  lcd.setBacklight((uint8_t)1);

  //stepper home
  if (autoHome() != true){
    lcd.setCursor(3,2);
    lcd.print("Failure During");
    lcd.setCursor(5,2);
    lcd.print("Auto Home");
    buzz(200,3);
  }
}

void loop() {

  
  moveStepsX(200,1,500);
  moveStepsY(200,1,500);
  delay(500);
  moveStepsX(200,0,500);
  moveStepsY(200,0,500);
  delay(500);
  buzz(100,2); 
}

  //Auto Home
  bool autoHome(){

    //moving x axis to home position
    while(readX() != true){
      moveStepsX(1,1,800);
      lcd.setCursor(1,2);
      lcd.print("calibrating X axis");
    }else{
      lcd.setCursor(3,2);
      lcd.print("X limit reached");
      buzz(100,1);
    }

    //moving y axis to home position
    while (readY() != true){
      moveStepsY(1,1,800);
      lcd.setCursor(1,2);
      lcd.print("calibrating Y axis");
    }else{
      lcd.setCursor(3,2);
      lcd.print("Y limit reached");
      buzz(100,1);
    }
  }

  //X stepper move function
  void moveStepsX(int steps,int dir, int stepSpeed){

    /* 
    steps 
    direction, 0 = clockwise 1 = Counterwise
    speed
    */
    if (dir == 0){
      digitalWrite(dirPinX,HIGH); // CLockwise
      Serial.println("Right");
    }else if (dir == 1){
      digitalWrite(dirPinX,LOW); // Cunterclockwise
      Serial.println("Left");
    }
      
    
    //for loop move steps, 200 == full rotation
    for(int x = 0; x < steps; x++) {
      digitalWrite(stepPinX,HIGH); 
      delayMicroseconds(stepSpeed); 
      digitalWrite(stepPinX,LOW); 
      delayMicroseconds(stepSpeed); 
    }
 }
 
  //Y stepper move funcrion
  void moveStepsY(int steps,int dir, int stepSpeed){

  /* 
    steps 
    direction, 0 = clockwise 1 = Counterwise
    speed
    */
    if (dir == 0){
      digitalWrite(dirPinY,HIGH); // CLockwise
      Serial.println("Right");
    }else if (dir == 1){
      digitalWrite(dirPinY,LOW); // Cunterclockwise
      Serial.println("Left");
    }
      
    
    //for loop move steps, 200 == full rotation
    for(int x = 0; x < steps; x++) {
      digitalWrite(stepPinY,HIGH); 
      delayMicroseconds(stepSpeed); 
      digitalWrite(stepPinY,LOW); 
      delayMicroseconds(stepSpeed); 
    }
 }

  //buzzer function
  void buzz(int buzzTime,int buzzes){

    for (int x = 0; x < buzzes; x++){

      //debug
      Serial.println("Buzzed");

      //buzzes
      digitalWrite(buzzPin,HIGH);
      delay(buzzTime);
      digitalWrite(buzzPin,LOW);

      //dont delay on last buzz
      if(buzzes != 1){
        delay(buzzTime);
      }

    }
    
  }
  
  //read x limit switch
  bool readX(){
    if (digitalRead(limitX) == 1){
      return true
    }else if (digitalRead(limitX) == 0){
      return false
    }
  }

  //read y limit switch
  bool readY(){
    if (digitalRead(limitY) == 1){
      return true
    }else if (digitalRead(limitY) == 0){
      return false
    }
  }
