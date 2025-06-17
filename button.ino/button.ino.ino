// Define pin for the button
const int buttonPin =26;

//Variable to store the button state
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  //Start the serial communication
  Serial.begin(115200);
  // Set the button pin as input with internal pull-up resistor
  pinMode(buttonPin,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read the state of thebutton (it will be LOW when pressed, HIGH when not pressed)
  buttonState = digitalRead(buttonPin);
  
  // Print only the button state to the Serial Monitor for plotting
  Serial.println(buttonState);

  // Add a small dealy for the readability in the plot
  delay(100);
}
