//automatic night light
//turn on the LED when the light levels get lower than a specific value

const int ledPowerPin = 8; //LED pin
const int sensor_pin = A0; //light dependant sensor pin
int sensor; //reading of the light dependant sensor
const int threshold = 700; //threshold to turn on the LED
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPowerPin, OUTPUT); //set the LED as output
  Serial.begin(9600);//set up serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor = analogRead(sensor_pin);
  Serial.println(sensor);
  if(sensor > threshold){
    digitalWrite(ledPowerPin, HIGH);
    Serial.println("Low Light");
  }
  else if (sensor < threshold){
    digitalWrite(ledPowerPin, LOW);
    Serial.println("Ampient Light");
  }
//  delay(1000);
}
