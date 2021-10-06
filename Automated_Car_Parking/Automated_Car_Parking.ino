#include <LiquidCrystal.h>// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#include <Servo.h> //includes the servo library
#include <Keypad.h>

#define len 5
int buzzer = 8;
int pos = 0;


/////for keypad//////////////////////////////////////////////////////////////////////////////////////
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads

char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', 'D'},
  {'4', '5', '6', 'M'},
  {'1', '2', '3', 'S'},
  {'C', '0', '=', 'A'}
};



byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad



//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char user[len];
char password[len] = "2021";
byte count;
char key;

//////////////////////////////////////////////////////////////////////////////////////////////////////////

Servo myservo1;
Servo myservo2;


const int trigPin = 49; //trig pin connection
const int echoPin = 50;  //echopin connection

long duration;
int distance;

int Space;

void setup() {
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo1.attach(3);
  myservo2.attach(4);
  
  lcd.begin(16, 2);
  lcd.setCursor (0, 0);
  lcd.print("  Car  Parking  ");
  lcd.setCursor (0, 1);
  lcd.print("     System     ");
  delay (50);
  lcd.clear();
  Space = 2;
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (digitalRead (A15) == 0) {

    lcd.setCursor (0, 0);
    lcd.print("Total Space: ");
    lcd.print("2");

    lcd.setCursor (0, 1);
    lcd.print("Left Space: ");
    lcd.print(Space);
    delay(20);
    lcd.clear();
  }
 
  if (digitalRead (A15) != 0) {
    if (Space > 0) {
      if (distance < 500) {

        tone(buzzer, 1000);
        delay(20);
        lcd.setCursor(0, 0);
        lcd.print("Distance:");
        lcd.print(distance);
        lcd.print(" Cm ");
        lcd.setCursor(0, 1);
        lcd.print("go back");
        delay(30);
        lcd.clear();
      }
      else
      {
        noTone(buzzer);
        delay(50);
        lcd.setCursor (0, 0);
        lcd.print("Enter password");
        key = customKeypad.getKey();
        if (key)
        { user[count] = key;
          lcd.setCursor(count, 1);
          lcd.print(user[count]);
          count++;
        }

        if (count == len - 1)
        {
          if (!strcmp(user, password)) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Password Matched");
            delay(50);
            count = 0;
            myservo1.write(0);

            for (pos = 0; pos <= 90; pos = pos + 1) { // goes from 0 degrees to 90 degrees
              // in steps of 1 degree
              myservo1.write(pos);              // tell servo to go to position in variable 'pos'
              delay(50);                       // waits 50ms for the servo to reach the position
            }

            for (pos = 90; pos >= 0; pos = pos - 1) { // goes from 90 degrees to 0 degrees
              myservo1.write(pos);              // tell servo to go to position in variable 'pos'
              delay(20);                       // waits 20ms for the servo to reach the position
            }

            Space = Space - 1;

          }

          else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Wrong Password");
            delay(50);
            count = 0;
          }
        }

      }
    }
    else {
      lcd.clear();
      lcd.setCursor (0, 0);
      lcd.print(" Sorry no Space ");
      lcd.setCursor (0, 1);
      lcd.print("    Available    ");
      delay (50);
    }
  }

  if (digitalRead (A14) != 0) {

    if (Space < 5) {
      Space = Space + 1;

      lcd.setCursor (0, 0);
      lcd.print("Total Space: ");
      lcd.print("2");

      lcd.setCursor (0, 1);
      lcd.print("Left  Space: ");
      lcd.print(Space);
      delay(50);
      myservo1.write(0);

      for (pos = 0; pos <= 90; pos = pos + 1) { // goes from 0 degrees to 90 degrees
        // in steps of 1 degree
        myservo2.write(pos);              // tell servo to go to position in variable 'pos'
        delay(50);                       // waits 20ms for the servo to reach the position
      }

      for (pos = 90; pos >= 0; pos = pos - 1) { // goes from 90 degrees to 0 degrees
        myservo2.write(pos);              // tell servo to go to position in variable 'pos'
        delay(20);                       // waits 20ms for the servo to reach the position
      }
      lcd.clear();

    }
  }
}
