#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Define the keypad layout
const byte ROW_NUM = 4; //four rows
const byte COL_NUM = 4; //three columns
char keys[ROW_NUM][COL_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COL_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

// Initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COL_NUM);

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address

int buzzerPin = 12;
Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  
  myservo.attach(10); // attaches the servo on pin 9
  
  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    
    if (key == '#') {
      // Check if the entered password matches
      String password = "1234A#"; // Example password including letter A
      if (password == "1234A#") {
        unlockDoor();
      } else {
        playIncorrectPasswordSound();
      }
    }
  }
}

void unlockDoor() {
  digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  delay(1000); // Wait for a second
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  
  myservo.write(90); // Open the door
  delay(5000); // Keep the door open for 2 seconds
  myservo.write(0); // Close the door
  
  lcd.clear(); // Clear the LCD before printing the welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome Desire");
  delay(3000); // Display the welcome message for 3 seconds
  lcd.clear(); // Clear the LCD after displaying the message
}

void playIncorrectPasswordSound() {
  digitalWrite(buzzerPin, HIGH); // Incorrect password
  delay(500); // Wait half a second
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  
  lcd.clear(); // Clear the LCD before printing the error message
  lcd.setCursor(0, 0);
  lcd.print("Wrong Password");
  delay(3000); // Display the error message for 3 seconds
  lcd.clear(); // Clear the LCD after displaying the message
  }
