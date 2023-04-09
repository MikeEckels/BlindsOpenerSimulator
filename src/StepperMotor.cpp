#include "StepperMotor.h"

StepperMotor::StepperMotor() {
	//driver.BindStepCallback([this]() {handleStep(); });
	this->driver.BindStepCallback(std::bind(&StepperMotor::handleStep, this));
	this->stepAngleDivisions = (this->stepAngle / this->driver.GetMicroSteps());
}

void StepperMotor::handleStep() {
	MotorDirection direction = StepperMotor::GetDirection();
	if (direction != CW) {
		this->numSteps = (this->numSteps-- <= 0) ? 0 : numSteps--;
	}
	else {
		this->numSteps = (this->numSteps++ >= ULONG_MAX) ? ULONG_MAX : numSteps++;
	}
	
	this->position = (this->driver.GetDirection()) ? this->position + this->stepAngleDivisions : this->position - this->stepAngleDivisions;
}

void StepperMotor::Enable() {
	this->driver.Enable();
}

void StepperMotor::Disable() {
	this->driver.Disable();
}

void StepperMotor::MoveDegrees(float degrees) {
	if (this->driver.GetEnabledState()) {
		long numSteps = (long) (degrees / this->stepAngleDivisions);
		
		for (int i = 0; i < numSteps; i++) {
			this->driver.Step();
			Delay::delayMicros(this->stepDelayuS * 2); //x2 for period. We arent actually toggling a step pin
		}

	}
	else {
		std::cout << "[!] Cannot move, motor is disabled" << std::endl;
	}
}

void StepperMotor::MoveRadians(float radians) {
	StepperMotor::MoveDegrees(radians * (180.0f / (float)M_PI));
}

void StepperMotor::SetRPM(float RPM) {
	this->RPM = RPM;
	this->stepFrequency = ((6.0f * RPM) / (this->stepAngleDivisions));
	this->stepDelayuS = (((1.0f / this->stepFrequency) * 1000000.0f) / 2);
	//DEBUG
	std::cout << "########## Kinematics Info ##########" << std::endl;
	std::cout << "RPM: " << this->RPM << std::endl;
	std::cout << "Freq: " << this->stepFrequency << std::endl;
	std::cout << "DelayUs: " << this->stepDelayuS << std::endl;
	std::cout << "#####################################" << std::endl << std::endl;

	//RPM = stepAngle / 360 * f * 60
	//f = (6 * RPM) / stepAngle
	//stepDelayuS = ((1/f) * 1,000,000) / 2
}

void StepperMotor::SetDirection(MotorDirection direction) {
	this->driver.SetDirection(direction);
}

MotorDirection StepperMotor::GetDirection() const {
	return this->driver.GetDirection();
}

float StepperMotor::GetPositionDegrees() const {
	return this->position;
}

long StepperMotor::GetPositionSteps() const {
	return this->numSteps;
}