#include "StepperDriver.h"

StepperDriver::StepperDriver(uSteps microSteps) : microSteps(microSteps) {}

void StepperDriver::Step() {
	this->stepCallback();
}

void StepperDriver::Enable() {
	this->enabled = true;
}

void StepperDriver::Disable() {
	this->enabled = false;
}

void StepperDriver::BindStepCallback(Callback callback) {
	this->stepCallback = callback;
}

void StepperDriver::UnbindStepCallback() {
	this->stepCallback = this->nullCallback;
}

void StepperDriver::SetDirection(MotorDirection direction) {
	this->direction = direction;
}

uSteps StepperDriver::GetMicroSteps() const {
	return this->microSteps;
}

MotorDirection StepperDriver::GetDirection() const {
	return this->direction;
}

bool StepperDriver::GetEnabledState() const {
	return this->enabled;
}
