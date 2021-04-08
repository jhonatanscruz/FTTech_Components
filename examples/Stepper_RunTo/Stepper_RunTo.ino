// LIBRARIES
#include "FTTech_Components.h"

//IT IS NECESSARY TO INCLUDE THE LIBRARY TO COMMUNICATE WITH THE BOARD
#include "FTTech_SAMD51_Clicks.h"
//-------------------------------------------------------------------------------------

// IT CREATES THE STEP MOTOR OBJECT WITH THE PORTS AND TOTAL STEPS OF THE MOTOR
// FT_Stepper(int pinPUL, int pinDIR, int pinENA, int microstepsNumb)
FT_Stepper motor(4, 46, 41, 1600);
//-------------------------------------------------------------------------------------

void setup() {

  //IT ALLOWS THE BOARD OUTPUTS
  FTClicks.ON_5V(); // Enbale 5V Output
  //FTClicks.ONN(1);
  //FTClicks.ONN(2);
  FTClicks.ONN(3);   // Step-Up 5-24V Click

  //INITIAL STEPPER MOTOR SETTINGS
  motor.begin();

  // IT STARTS SERIAL COMMUNICATION
  Serial.begin(9600);
  while(!Serial);

  Serial.print("DEGREES POSITION: " + (String)round(motor.getDegreePosition()) + "º");
  Serial.println(" | REAL DEGREES POSITION " + (String)motor.getDegreePosition() + "º");
  Serial.print("STEPS POSITION: " + (String)motor.getStepPosition());
  Serial.println(" | REAL STEPS POSITION " + (String)(motor.getStepPosition()+motor.getDegreePosition()));
  Serial.println("ERROR: " + (String)motor.getStepError());
  Serial.println("-----------------------------------------------------------------------------");

}
// ---------------------------------------------------------------------------------------------------------------

void loop() {

motor.start(); // PUT THE MOTOR ON (setENA = 1)
motor.runTo(30); // MOTOR RUNS TO 30º POSITION
motor.stop(); // PUT THE MOTOR OFF (setENA = 0)

// PRINT
Serial.print("DEGREES POSITION: " + (String)round(motor.getDegreePosition()) + "º");
Serial.println(" | REAL DEGREES POSITION " + (String)motor.getDegreePosition() + "º");
Serial.print("STEPS POSITION: " + (String)motor.getStepPosition());
Serial.println(" | REAL STEPS POSITION " + (String)(motor.getStepPosition()+motor.getDegreePosition()));
Serial.println("ERROR: " + (String)motor.getStepError());
Serial.println("-----------------------------------------------------------------------------");
delay(1000);

motor.start(); // PUT THE MOTOR ON (setENA = 1)
motor.runTo(180); // MOTOR RUNS TO 180º POSITION
motor.stop(); // PUT THE MOTOR OFF (setENA = 0)

// PRINT
Serial.print("DEGREES POSITION: " + (String)round(motor.getDegreePosition()) + "º");
Serial.println(" | REAL DEGREES POSITION " + (String)motor.getDegreePosition() + "º");
Serial.print("STEPS POSITION: " + (String)motor.getStepPosition());
Serial.println(" | REAL STEPS POSITION " + (String)(motor.getStepPosition()+motor.getDegreePosition()));
Serial.println("ERROR: " + (String)motor.getStepError());
Serial.println("-----------------------------------------------------------------------------");
delay(2000);

motor.start(); // PUT THE MOTOR ON (setENA = 1)
motor.runTo(270); // MOTOR RUNS TO 270º POSITION
motor.stop(); // PUT THE MOTOR OFF (setENA = 0)

// PRINT
Serial.print("DEGREES POSITION: " + (String)round(motor.getDegreePosition()) + "º");
Serial.println(" | REAL DEGREES POSITION " + (String)motor.getDegreePosition() + "º");
Serial.print("STEPS POSITION: " + (String)motor.getStepPosition());
Serial.println(" | REAL STEPS POSITION " + (String)(motor.getStepPosition()+motor.getDegreePosition()));
Serial.println("ERROR: " + (String)motor.getStepError());
Serial.println("-----------------------------------------------------------------------------");
delay(2000);

motor.start(); // PUT THE MOTOR ON (setENA = 1)
motor.runTo(90); // MOTOR RUNS TO 90º POSITION
motor.stop(); // PUT THE MOTOR OFF (setENA = 0)

// PRINT
Serial.print("DEGREES POSITION: " + (String)round(motor.getDegreePosition()) + "º");
Serial.println(" | REAL DEGREES POSITION " + (String)motor.getDegreePosition() + "º");
Serial.print("STEPS POSITION: " + (String)motor.getStepPosition());
Serial.println(" | REAL STEPS POSITION " + (String)(motor.getStepPosition()+motor.getDegreePosition()));
Serial.println("ERROR: " + (String)motor.getStepError());
Serial.println("-----------------------------------------------------------------------------");
delay(2000);

motor.start(); // PUT THE MOTOR ON (setENA = 1)
motor.run(2); // MOTOR MAKES 2 COMPLETE TURNS.
motor.stop(); // PUT THE MOTOR OFF (setENA = 0)

// PRINT
Serial.print("DEGREES POSITION: " + (String)round(motor.getDegreePosition()) + "º");
Serial.println(" | REAL DEGREES POSITION " + (String)motor.getDegreePosition() + "º");
Serial.print("STEPS POSITION: " + (String)motor.getStepPosition());
Serial.println(" | REAL STEPS POSITION " + (String)(motor.getStepPosition()+motor.getDegreePosition()));
Serial.println("ERROR: " + (String)motor.getStepError());
Serial.println("-----------------------------------------------------------------------------");
delay(2000);

motor.start(); // PUT THE MOTOR ON (setENA = 1)
motor.runTo(0); // MOTOR RUNS TO 0º POSITION
motor.stop(); // PUT THE MOTOR OFF (setENA = 0)

// PRINT
Serial.print("DEGREES POSITION: " + (String)round(motor.getDegreePosition()) + "º");
Serial.println(" | REAL DEGREES POSITION " + (String)motor.getDegreePosition() + "º");
Serial.print("STEPS POSITION: " + (String)motor.getStepPosition());
Serial.println(" | REAL STEPS POSITION " + (String)(motor.getStepPosition()+motor.getDegreePosition()));
Serial.println("ERROR: " + (String)motor.getStepError());
Serial.println("-----------------------------------------------------------------------------");
delay(2000);

}
