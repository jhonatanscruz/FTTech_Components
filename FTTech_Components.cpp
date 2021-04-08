//LIBRARIES
#include <FTTech_Components.h>

// FT_Stepper ----------------------------------------------------------------

FT_Stepper::FT_Stepper(int pinPUL, int pinDIR, int pinENA, int microstepsNumb)
{
    this->driverPUL = pinPUL;
    this->driverDIR = pinDIR;
    this->driverENA = pinENA;
    this->microsteps = microstepsNumb;
    this->pulseDelay = 750;
    this->setDIR = 0;
    this->setENA = 0;
    this->stepPosition = 0;
    this->stepError = 0;
    this->degreePosition = 0;
}
//--------------------------------------------------

// MOTOR INICIALIZATION
/* the motor inicialization must be placed in the setup() function*/
void FT_Stepper::begin(){
    pinMode(this->driverPUL, OUTPUT);
    pinMode(this->driverDIR, OUTPUT);
    pinMode(this->driverENA, OUTPUT);
    digitalWrite(this->driverENA, this->setENA);
    digitalWrite(this->driverDIR, this->setDIR);
}
//--------------------------------------------------

// TO RESET THE MOTOR
void FT_Stepper::reset(){
    this->setDIR = 0;
    this->stepPosition = 0;
    this->stepError = 0;
    this->degreePosition = 0;
    digitalWrite(this->driverDIR, this->setDIR);
}
//--------------------------------------------------

// TO STOP THE MOTOR
void FT_Stepper::stop(){
    this->setENA = 0;
    digitalWrite(this->driverENA, this->setENA);
}
//--------------------------------------------------

// ALLOW THE MOTOR TO RUN
void FT_Stepper::start(){
    this->setENA = 1;
    digitalWrite(this->driverENA, this->setENA);
}
//--------------------------------------------------

// GET THE MOTOR POSITION IN STEPS
int FT_Stepper::getStepPosition(){

    int stepPosition = this->stepPosition;
    return stepPosition;
}
//--------------------------------------------------

// GET THE MOTOR ERROR POSITION IN STEPS
float FT_Stepper::getStepError(){

    float stepError = this->stepError;
    return stepError;
}
//--------------------------------------------------

// GET THE MOTOR POSITION IN DEGREES
float FT_Stepper::getDegreePosition(){

    float degreePosition = this->degreePosition;
    return degreePosition;
}
//--------------------------------------------------

// SET THE PULSE DELAY
void FT_Stepper::setPulseDelay(int newPulseDelay){
    this->pulseDelay = newPulseDelay;
}
//--------------------------------------------------

// SET THE MOTOR DIRECTION OF ROTATION
void FT_Stepper::changeDIR(int newDIR){
    if(newDIR != this->setDIR){
        this->setDIR = newDIR;
        digitalWrite(this->driverDIR,newDIR);
    }
}
//--------------------------------------------------

// IT SENDS A PULSE TO THE 'driverPUL' PORT
/*The Motor needs pulses to jump to the next step.
Each pulse represents one Motor step. */
void FT_Stepper::pulse(){
    digitalWrite(this->driverPUL,HIGH);
    delayMicroseconds(this->pulseDelay);
    digitalWrite(this->driverPUL,LOW);
    delayMicroseconds(this->pulseDelay);

    if(this->setENA){
        if(!this->setDIR){
            this->stepPosition++;
            this->degreePosition = this->degreePosition + (360./this->microsteps);
        }
        else{
            this->stepPosition--;
            this->degreePosition = this->degreePosition - (360./this->microsteps);
        }
        if(this->stepPosition == this->microsteps || this->stepPosition == -(this->microsteps)){
            this->stepPosition = 0;
            this->degreePosition = 0;
        }
    }
}
//--------------------------------------------------

// MOTOR MAKES SOME NUMBER OF ROTATIONS
/*The motor rotates as much as the turnNumber variable*/
void FT_Stepper::run(int turnNumber){

    int totalTurn = turnNumber*this->microsteps;
    for(int i = 0; i < totalTurn; i++){
        this->pulse();
    }
}
//--------------------------------------------------

// MOTOR RUNS TO POSITION IN DEGREES
/* 
The motor rotates to the position in degrees specified in the 'toDegrees' variable
*/
void FT_Stepper::runTo(int toDegrees){

    int shiftDegrees = round(toDegrees - this->degreePosition);
    float shiftSteps = shiftDegrees * (this->microsteps / 360.);
    bool changeError;

    // Evaluates whether the user wants to change the position
    // Evaluates stepper direction change
    if(shiftDegrees > 0){
        changeError = 1;
        this->changeDIR(0);
    }
    else if(shiftDegrees < 0){
        changeError = 1;
        this->changeDIR(1);
    }
    else if(shiftDegrees == 0){
        changeError = 0;
    }

    //It Creates the turning logic for the stepper in both cw and ccw directions    
    if(!this->setDIR){
        for(int i = 0; i < round(shiftSteps + this->stepError); i++){
            this->pulse();
        }
    }
    else{
        for(int i = 0; i > round(shiftSteps + this->stepError); i--){
            this->pulse();
        }
    }

    // Change the error value
    if(changeError){
        this->stepError = (shiftSteps + this->stepError) - round(shiftSteps + this->stepError);
    }

}
//--------------------------------------------------

// FT_Encoder ----------------------------------------------------------------

FT_Encoder::FT_Encoder(const byte _pinA, const byte _pinB, const byte _pinZ)
{
    this->pinA = _pinA;    // keep the pin A
    this->pinB = _pinB;    // keep the pin B
    this->pinZ = _pinZ;    // keep the pin Z
    this->position = 0;    // Encoder position (-4000 to 4000)
    this->dir = 0;         // Encoder direction of rotation
    this->laps = 0;        // keep the laps number of Encoder
}
//--------------------------------------------------

// Encoder INICIALIZATION
/* the encoder inicialization must be placed in the setup() function */
void FT_Encoder::begin(){
    pinMode(this->pinA,INPUT_PULLUP);
    pinMode(this->pinB,INPUT_PULLUP);
    pinMode(this->pinZ,INPUT_PULLUP);

    this->pinA_LastState = this->readPinA();
    this->pinB_LastState = this->readPinB();
    this->pinA_CurrState =this->readPinA();
    this->pinB_CurrState = this->readPinB();
}
//--------------------------------------------------

// AttachInterrupt0, Signal A - Any change at the edge (CHANGE)
void FT_Encoder::PinA_OnChange() {

    this->pinA_LastState = this->pinA_CurrState;
    this->pinB_LastState = this->pinB_CurrState;
    this->pinA_CurrState = this->readPinA();
    this->pinB_CurrState = this->readPinB();

// ----------------------------- FIRST STATE ----------------------------
    if(this->pinA_LastState == HIGH && this->pinB_LastState == LOW){

        if(this->pinA_CurrState == HIGH && this->pinB_CurrState == HIGH){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == LOW && this->pinB_CurrState == LOW){
            this->dir = 0;
            this->position--;
        }
    }
// ------------------------------------------------------------------------

// ----------------------------- SECOND STATE -----------------------------
    else if(this->pinA_LastState == HIGH && this->pinB_LastState == HIGH){

        if(this->pinA_CurrState == LOW && this->pinB_CurrState == HIGH){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == HIGH && this->pinB_CurrState == LOW){
            this->dir = 0;
            this->position--;
        }
    }
// ------------------------------------------------------------------------

// ----------------------------- THIRD STATE ----------------------------
    else if(this->pinA_LastState == LOW && this->pinB_LastState == HIGH){

        if(this->pinA_CurrState == LOW && this->pinB_CurrState == LOW){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == HIGH && this->pinB_CurrState == HIGH){
            this->dir = 0;
            this->position--;
        }
    }
// ------------------------------------------------------------------------

// ----------------------------- LAST STATE ------------------------------
    else if(this->pinA_LastState == LOW && this->pinB_LastState == LOW){

        if(this->pinA_CurrState == HIGH && this->pinB_CurrState == LOW){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == LOW && this->pinB_CurrState == HIGH){
            this->dir = 0;
            this->position--;
        }
    }
}
// ------------------------------------------------------------------------

// AttachInterrupt1, Signal B - Any change at the edge (CHANGE)
void FT_Encoder::PinB_OnChange() {

    this->pinA_LastState = this->pinA_CurrState;
    this->pinB_LastState = this->pinB_CurrState;
    this->pinA_CurrState = this->readPinA();
    this->pinB_CurrState = this->readPinB();

// -----------------------------  FIRST STATE ----------------------------
    if(this->pinA_LastState == HIGH && this->pinB_LastState == LOW){

        if(this->pinA_CurrState == HIGH && this->pinB_CurrState == HIGH){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == LOW && this->pinB_CurrState == LOW){
            this->dir = 0;
            this->position--;
        }
    }
// ------------------------------------------------------------------------

// ----------------------------- SECOND STATE -----------------------------
    else if(this->pinA_LastState == HIGH && this->pinB_LastState == HIGH){

        if(this->pinA_CurrState == LOW && this->pinB_CurrState == HIGH){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == HIGH && this->pinB_CurrState == LOW){
            this->dir = 0;
            this->position--;
        }
    }
// ------------------------------------------------------------------------

// ----------------------------- THIRD STATE ----------------------------
    else if(this->pinA_LastState == LOW && this->pinB_LastState == HIGH){

        if(this->pinA_CurrState == LOW && this->pinB_CurrState == LOW){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == HIGH && this->pinB_CurrState == HIGH){
            this->dir = 0;
            this->position--;
        }
    }
// ------------------------------------------------------------------------

// ----------------------------- LAST STATE ------------------------------
    else if(this->pinA_LastState == LOW && this->pinB_LastState == LOW){

        if(this->pinA_CurrState == HIGH && this->pinB_CurrState == LOW){
            this->dir = 1;
            this->position++;
        }
        else if(this->pinA_CurrState == LOW && this->pinB_CurrState == HIGH){
            this->dir = 0;
            this->position--;
        }
    }

}
// ------------------------------------------------------------------------

// AttachInterrupt2, Signal Z - It changes on the falling edge (FALLING)
// It Counts the laps of the Encoder
void FT_Encoder::PinZ_OnFalling() {
    if(dir) laps++;
    else laps--;

    this->position = 0;
}
// ------------------------------------------------------------------------

// ENCODER POSITION
/* the encoder inicialization must be placed in the setup() function*/
volatile int long FT_Encoder::getPosition(){

    return this->position;
}
//--------------------------------------------------

// ENCODER LAPS
/* the encoder inicialization must be placed in the setup() function*/
int FT_Encoder::getLaps(){

    return this->laps;
}
//--------------------------------------------------

// Returns the current value at output A
byte FT_Encoder::readPinA() {
    return digitalRead(this->pinA);
}
// ------------------------------------------------------------------------

// Returns the current value at output B
byte FT_Encoder::readPinB() {
    return digitalRead(this->pinB);
}
// ------------------------------------------------------------------------

// Returns the current value at output Z
byte FT_Encoder::readPinZ() {
    return digitalRead(this->pinZ);
}
// ------------------------------------------------------------------------