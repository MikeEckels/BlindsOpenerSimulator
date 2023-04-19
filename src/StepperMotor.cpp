#include "StepperMotor.h"

StepperMotor::StepperMotor() {
	//driver.BindStepCallback([this]() {handleStep(); });
	this->driver.BindStepCallback(std::bind(&StepperMotor::handleStep, this));
	this->stepAngleDivisions = (this->stepAngle / this->driver.GetMicroSteps());
}

void StepperMotor::handleStep() {
	MotorDirection direction = StepperMotor::GetDirection();
	if (direction != CW) {
		this->numSteps = (this->numSteps-- <= (long)0) ? (long)0 : numSteps--;
		this->position = (this->position - this->stepAngleDivisions <= 0.0f) ? 0.0f : this->position - this->stepAngleDivisions;
	}
	else {
		this->numSteps = (this->numSteps++ >= ULONG_MAX) ? ULONG_MAX : numSteps++;
		this->position = (this->position + this->stepAngleDivisions >= FLT_MAX) ? FLT_MAX : this->position + this->stepAngleDivisions;
	}
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
		
		for (long i = 0; i < numSteps; i++) {
			this->driver.Step();
			Delay::delayMicros(this->stepDelayuS * 2.0f); //x2 for period. We arent actually toggling a step pin
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
	this->stepDelayuS = (((1.0f / this->stepFrequency) * 1000000.0f) / 2.0f);

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

float StepperMotor::GetRPM() const {
	return this->RPM;
}

float StepperMotor::GetStepAngle() const {
	return this->stepAngle;
}

float StepperMotor::GetStepDelayuS() const {
	return this->stepDelayuS;
}

float StepperMotor::GetStepFrequency() const {
	return this->stepFrequency;
}

float StepperMotor::GetStepAngleDivisions() const {
	return this->stepAngleDivisions;
}

long StepperMotor::GetPositionSteps() const {
	return this->numSteps;
}

float StepperMotor::GetPositionDegrees() const {
	return this->position;
}

MotorDirection StepperMotor::GetDirection() const {
	return this->driver.GetDirection();
}

StepperDriver StepperMotor::GetStepperDriver() const {
	return this->driver;
}