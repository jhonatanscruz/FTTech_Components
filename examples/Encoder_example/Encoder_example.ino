// LIBRARIES
#include "FTTech_SAMD51Clicks.h"
#include "FTTech_Components.h"
// ------------------------------------------------------------------------

// PIN DEFINITION
const byte pinA = 10;
const byte pinB = 51;
const byte pinZ = 44;

FT_Encoder encoder(pinA, pinB, pinZ); // It Instantiates the encoder object

// ------------------------------------------------------------------------

void setup() {

  FTClicks.ON_5V(); // Enable 5V Output
  FTClicks.ONN(1);  // Step-Up 5-24V Click

  encoder.begin();

  // SERIAL START
  Serial.begin(9600);
  while(!Serial);

  // INTERRUPTIONS
  
  // AttachInterrupt0, digital PinA, Signal A
  // It Activates interruption on any signal change
  attachInterrupt(digitalPinToInterrupt(pinA), PinA_OnChange, CHANGE);

  // AttachInterrupt1, digital PinB, Signal B
  // It Activates interruption on any signal change
  attachInterrupt(digitalPinToInterrupt(pinB), PinB_OnChange, CHANGE);

  //AttachInterrupt2, digital PinZ, Signal Z
  // It Activates interruption at the falling edge of the signal
  attachInterrupt(digitalPinToInterrupt(pinZ), PinZ_OnFalling, FALLING);
  
}
// ------------------------------------------------------------------------

void loop() {

  //It Prints the encoder position (-4000 to 4000 for a encoder with resolution = 1000p)
  Serial.println("Position: " + (String)encoder.getPosition());
  
  //It Prints the encoder number of laps to the cw or ccw direction
  Serial.println("laps: " + (String)encoder.getLaps());
}
// ------------------------------------------------------------------------

// -------------------- GLOBAL FUNCTIONS --------------------

void PinA_OnChange(){
  encoder.PinA_OnChange();
}
// ---------------------------

void PinB_OnChange(){
  encoder.PinB_OnChange();
}
// ---------------------------

void PinZ_OnFalling(){
  encoder.PinZ_OnFalling();
}
