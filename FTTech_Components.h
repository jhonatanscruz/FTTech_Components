#ifndef FTTech_Components_H
#define FTTech_Components_H

//LIBRARIES
#include <Arduino.h>

/* Essa biblioteca auxilia o desenvolvedor a realizar conexões e ações com os diversos
   componentes utilizados na FTtech. Lembrando que é importante ativar as portas da
   respectiva placa que está sendo utilizada */

/**************************************************************************/
/*!
    @brief  Class that defines functions for interacting with a passing motor
*/
/**************************************************************************/

class FT_Stepper{

    private:
      // MEMBER VARIABLES
      int driverPUL;        // keep the PUL - pin
      int driverDIR;        // keep the DIR - pin
      int driverENA;        // keep the ENA - pin
      int microsteps;       // keep the number of microsteps
      int stepPosition;     // keep the motor position in Steps
      float stepError;      // keep the motor error position in Steps
      float degreePosition; // keep the motor position in Steps
      int pulseDelay;       // keep the delay time before rising or falling edge
      bool setDIR;          // keep the motor rotation direction
      bool setENA;          // keep the motor state (ON or OFF)

    //--------------------------------------------------

    public:
      // CONSTRUCTOR
      FT_Stepper(int pinPUL, int pinDIR, int pinENA, int microstepsNumb);
      //--------------------------------------------------

      // MOTOR INICIALIZATION
      /* the motor inicialization must be placed in the setup() function*/
      void begin();
      //--------------------------------------------------

      // MOTOR RESET
      void reset();
      //--------------------------------------------------
      
      // TO STOP THE MOTOR
      void stop();
      //--------------------------------------------------
      
      // ALLOW THE MOTOR TO RUN
      void start();
      //--------------------------------------------------
      
      // GET THE MOTOR POSITION IN STEPS
      int getStepPosition();
      //--------------------------------------------------

      // GET THE MOTOR ERROR POSITION IN STEPS
      float getStepError();
      //--------------------------------------------------

      // GET THE MOTOR POSITION IN DEGREES
      float getDegreePosition();
      //--------------------------------------------------

      // SET THE PULSE DELAY
      void setPulseDelay(int newPulseDelay);
      //--------------------------------------------------
      
      // SET THE MOTOR DIRECTION OF ROTATION
      void changeDIR(int newDIR);
      //--------------------------------------------------
      
      // IT SENDS A PULSE TO THE driverPUL PORT
      /*The Motor needs pulses to jump to the next step.
      Each pulse represents one Motor step. */
      void pulse();
      //--------------------------------------------------
      
      // MOTOR MAKES SOME NUMBER OF ROTATIONS
      /*The motor rotates as much as the turnNumber variable*/
      void run(int turnNumber);
      //--------------------------------------------------
      
      // MOTOR RUNS TO POSITION IN DEGREES
      /*The motor rotates to the position in degrees specified in the degrees variable*/
      void runningUntil(int toDegrees);
      //--------------------------------------------------

      // MOTOR RUNS TO POSITION IN DEGREES
      /*The motor rotates to the position in degrees specified in the degrees variable*/
      void runTo(int toDegrees);
      //--------------------------------------------------
};

// ###############################################################################################

class FT_Encoder{

    private:
      // MEMBER VARIABLES
      byte pinA;                   // keep the A - pin
      byte pinB;                   // keep the B - pin
      byte pinZ;                   // keep the Z - pin
      int laps;                    // keep the laps number of Encoder
      volatile int long position;  // Encoder position
      byte dir;                    // Encoder direction of rotation
      byte pinA_LastState;         // Encoder last state of pinA
      byte pinB_LastState;         // Encoder last state of pinB
      byte pinA_CurrState;         // Encoder cuurent state of pinA
      byte pinB_CurrState;         // Encoder current state of pinB

    //--------------------------------------------------

    public:
      // CONSTRUCTOR
      FT_Encoder(byte _pinA, byte _pinB, byte _pinZ);
      //--------------------------------------------------

      // ENCODER BEGIN
      /* */
      void begin();
      //--------------------------------------------------

      // ENCODER RESET
      /* */
      void reset();
      //--------------------------------------------------

      // ACTION WHEN THERE IS A CHANGE ON PIN A
      /* */
      void PinA_OnChange();
      //--------------------------------------------------

      // ACTION WHEN THERE IS A CHANGE ON PIN B
      /* */
      void PinB_OnChange();
      //--------------------------------------------------

      // ACTION WHEN THERE IS A RISING EDGE ON PIN Z
      /* */
      void PinZ_OnRising();
      //--------------------------------------------------

      // ENCODER RETURNS ITS POSITION
      /* */
      volatile int long getPosition();
      //--------------------------------------------------

      // ENCODER CHANGES ITS POSITION
      /* */
      void changePosition(volatile int long newPos);
      //--------------------------------------------------

      // ENCODER RETURNS ITS NUMBER OF LAPS
      /* */
      int getLaps();
      //--------------------------------------------------

      // ENCODER RETURNS PIN A CURRENT VALUE
      /* */
      byte readPinA();
      //--------------------------------------------------

      // ENCODER RETURNS PIN B CURRENT VALUE
      /* */
      byte readPinB();
      //--------------------------------------------------

      // ENCODER RETURNS PIN Z CURRENT VALUE
      /* */
      byte readPinZ();
      //--------------------------------------------------
};

// ###############################################################################################

class FT_Encoder2{

    private:
      // MEMBER VARIABLES
      byte pinA;                   // keep the A - pin
      byte pinB;                   // keep the B - pin
      int laps;                    // keep the laps number of Encoder
      volatile int long position;  // Encoder position
      byte dir;                    // Encoder direction of rotation
      byte pinA_LastState;         // Encoder last state of pinA
      byte pinB_LastState;         // Encoder last state of pinB
      byte pinA_CurrState;         // Encoder cuurent state of pinA
      byte pinB_CurrState;         // Encoder current state of pinB

    //--------------------------------------------------

    public:
      // CONSTRUCTOR
      FT_Encoder2(byte _pinA, byte _pinB);
      //--------------------------------------------------

      // ENCODER BEGIN
      /* */
      void begin();
      //--------------------------------------------------

      // ENCODER RESET
      /* */
      void reset();
      //--------------------------------------------------

      // ACTION WHEN THERE IS A CHANGE ON PIN A
      /* */
      void PinA_OnChange();
      //--------------------------------------------------

      // ACTION WHEN THERE IS A CHANGE ON PIN B
      /* */
      void PinB_OnChange();
      //--------------------------------------------------

      // ENCODER RETURNS ITS POSITION
      /* */
      volatile int long getPosition();
      //--------------------------------------------------

      // ENCODER CHANGES ITS POSITION
      /* */
      void changePosition(volatile int long newPos);
      //--------------------------------------------------

      // ENCODER RETURNS ITS NUMBER OF LAPS
      /* */
      int getLaps();
      //--------------------------------------------------

      // ENCODER RETURNS PIN A CURRENT VALUE
      /* */
      byte readPinA();
      //--------------------------------------------------

      // ENCODER RETURNS PIN B CURRENT VALUE
      /* */
      byte readPinB();
      //--------------------------------------------------
};

#endif
