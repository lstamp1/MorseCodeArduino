// Liam Stamp
// August 2023
// International Morse Code Transmitter
// Arduino Uno
// LED Pin 7
// Serial input New Line 9600
// User can input capital A-Z, a-z (automatically capitalized) and 0-9
// Time interval may be adjusted with the MORSE_T_Default value (ms)
 
const int LEDpin=7; // LED connected to d7
int MORSE_T_Default = 500; // define time constant
String last_input = ""; //global last input

enum State {
  IDLE,
  MORSE
};

State currentState = IDLE; // Start in idle mode

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LEDpin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(currentState){
    case IDLE:
      handleSerialInput();
      break;
    case MORSE:
    Serial.println("(Transmitting)"+last_input);
      for (int i = 0; i < last_input.length(); i++){
        morse_lookup(toupper(last_input.charAt(i))); // convert to uppercase letters
      }
      delay(MORSE_T_Default * 4);
      handleSerialInput();
      break;
  }

}

void handleSerialInput() {
  if (Serial.available()) {
    last_input = Serial.readStringUntil('\n');
    last_input.trim();  // Remove any trailing whitespace
    if (last_input == "*") {
      Serial.println("Entering IDLE mode");
      currentState = IDLE;
    } else {
      //Serial.println("Received: " + last_input);
      currentState = MORSE;
    }
  }
}

void morse_lookup(char input){
  //Serial.println("Input = "+input);
  if      (input == 'A') {dot(); dash();}
  else if (input == 'B') {dash(); dot(); dot(); dot();}
  else if (input == 'C') {dash(); dot(); dash(); dot(); }
  else if (input == 'D') {dash(); dot(); dot(); }
  else if (input == 'E') {dot(); }
  else if (input == 'F') {dot(); dot(); dash(); dot(); }
  else if (input == 'G') {dash(); dash(); dot(); }
  else if (input == 'H') {dot(); dot(); dot(); dot(); }
  else if (input == 'I') {dot(); dot(); }
  else if (input == 'J') {dot(); dash(); dash(); dash(); }
  else if (input == 'K') {dash(); dot(); dash(); }
  else if (input == 'L') {dot(); dash(); dot(); dot(); }
  else if (input == 'M') {dash(); dash(); }
  else if (input == 'N') {dash(); dot(); }
  else if (input == 'O') {dash(); dash(); dash(); }
  else if (input == 'P') {dot(); dash(); dash(); dot(); }
  else if (input == 'Q') {dash(); dash(); dot(); dash(); }
  else if (input == 'R') {dot(); dash(); dot(); }
  else if (input == 'S') {dot(); dot(); dot(); }
  else if (input == 'T') {dash(); }
  else if (input == 'U') {dot(); dot(); dash(); }
  else if (input == 'V') {dot(); dot(); dot(); dash(); }
  else if (input == 'W') {dot(); dash(); dash(); }
  else if (input == 'X') {dash(); dot(); dot(); dash(); }
  else if (input == 'Y') {dash(); dot(); dash(); dash(); }
  else if (input == 'Z') {dash(); dash(); dot(); dot(); }
  else if (input == '1') {dot(); dash(); dash(); dash(); dash(); }
  else if (input == '2') {dot(); dot(); dash(); dash(); dash(); }
  else if (input == '3') {dot(); dot(); dot(); dash(); dash(); }
  else if (input == '4') {dot(); dot(); dot(); dot(); dash(); }
  else if (input == '5') {dot(); dot(); dot(); dot(); dot(); }
  else if (input == '6') {dash(); dot(); dot(); dot(); dot(); }
  else if (input == '7') {dash(); dash(); dot(); dot(); dot(); }
  else if (input == '8') {dash(); dash(); dash(); dot(); dot(); }
  else if (input == '9') {dash(); dash(); dash(); dash(); dot(); }
  else if (input == '0') {dash(); dash(); dash(); dash(); dash(); }
  else if (input == ' '){ delay(MORSE_T_Default * 2);} // 3 at end of last letter and 2 after this so 7 total 
  else{}
  delay(MORSE_T_Default * 2); // add the delay between letters, one is already accounted for so there is 3 total units of delay being off
}

void dot(void){
  digitalWrite(LEDpin, HIGH);
  delay(MORSE_T_Default);
  digitalWrite(LEDpin, LOW);
  delay(MORSE_T_Default);
}

void dash(void){
  digitalWrite(LEDpin, HIGH);
  delay(MORSE_T_Default*3); // dash is 3x 
  digitalWrite(LEDpin, LOW);
  delay(MORSE_T_Default);
}
