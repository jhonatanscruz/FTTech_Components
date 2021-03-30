//LIBRARIES
#include <FTTech_Components.h>

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

    // Avalia se o usuário quer mudar a posição do motor
    // Avalia a alteração da direção do motor
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

    // Cria a lógica de giro para o motor em ambos os sentidos
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

    // Altera o valor do erro
    if(changeError){
        this->stepError = (shiftSteps + this->stepError) - round(shiftSteps + this->stepError);
    }

}
//--------------------------------------------------