#include "Blinds.h"

Blinds::Blinds() {
	this->encoder.SetIncrement(25);
	this->drivePulleyRadiusMM = ((((float)this->pulleyTeeth * (float)this->beltPitchmm) / (float)M_PI) / 2);
}

float Blinds::degreesTomm(float degrees) {
	return (((float)M_PI / 180.0f) * degrees * this->drivePulleyRadiusMM);
}

float Blinds::mmToDegrees(float distanceMM) {
	return (180.0f * distanceMM) / ((float)M_PI * this->drivePulleyRadiusMM);
}

void Blinds::Open() {
	if (this->openState != ALL_OPEN) {
		Blinds::OpenShades();
		this->slideMotor.SetDirection(CW);
		this->slideMotor.Enable();
		this->slideMotor.MoveDegrees(Blinds::mmToDegrees(this->maxDistanceMM));
		this->slideMotor.Disable();
		std::cout << "[+] Opened - SlideMotor PosDeg: " << this->slideMotor.GetPositionDegrees() << " | PosSteps: " << this->slideMotor.GetPositionSteps() << std::endl;
	}
	else {
		std::cout << "[!] Blinds and shades are already open" << std::endl;
	}
	this->openState = ALL_OPEN;
	this->positionMM = (unsigned short)Blinds::degreesTomm(this->slideMotor.GetPositionDegrees());
}

void Blinds::Close() {
	if (this->openState != ALL_CLOSED) {
		this->slideMotor.SetDirection(CCW);
		this->slideMotor.Enable();
		this->slideMotor.MoveDegrees(Blinds::mmToDegrees(this->maxDistanceMM));
		this->slideMotor.Disable();
		std::cout << "[+] Closed - SlideMotor PosDeg: " << this->slideMotor.GetPositionDegrees() << " | PosSteps: " << this->slideMotor.GetPositionSteps() << std::endl;
		Blinds::CloseShades();
	}
	else if (this->openState == SHADES_OPEN) {
		Blinds::CloseShades();
	}
	else {
		std::cout << "[!] Blinds and shades are already closed" << std::endl;
	}
	this->positionMM = (unsigned short)Blinds::degreesTomm(this->slideMotor.GetPositionDegrees());
}

void Blinds::OpenShades() {
	if (this->openState == ALL_CLOSED) {
		this->rotateMotor.SetDirection(CW);
		this->rotateMotor.Enable();
		this->rotateMotor.MoveDegrees(90.0f);
		this->rotateMotor.Disable();
		this->openState = SHADES_OPEN;
		std::cout << "[+] OpenedShades - RotateMotor PosDeg: " << this->rotateMotor.GetPositionDegrees() << " | PosSteps: " << this->rotateMotor.GetPositionSteps() << std::endl;
	}
	else {
		std::cout << "[!] Shades are already open" << std::endl;
	}
}

void Blinds::CloseShades() {
	if (this->openState == SHADES_OPEN) {
		this->rotateMotor.SetDirection(CCW);
		this->rotateMotor.Enable();
		this->rotateMotor.MoveDegrees(90.0f);
		this->rotateMotor.Disable();
		std::cout << "[+] ClosedShades - RotateMotor Pos: " << this->rotateMotor.GetPositionDegrees() << " | PosSteps: " << this->rotateMotor.GetPositionSteps() << std::endl;
	}
	else if (this->openState == ALL_CLOSED) {
		std::cout << "[!] Shades are already closed" << std::endl;
	}
	this->openState = ALL_CLOSED;
}

void Blinds::PressEncoder() {
	this->encoder.PressButton();
}

void Blinds::TurnEncoderLeft(unsigned char numClicks) {
	this->encoder.TurnLeft(numClicks);
}

void Blinds::TurnEncoderRight(unsigned char numClicks) {
	this->encoder.TurnRight(numClicks);
}

void Blinds::SetAccelerationTarget(MotorFunction function, float mmPerSec2) {

}

void Blinds::SetVelocityTarget(MotorFunction function, VelocityType velocityType, float velocity) {
	//AngularVelocity = RPM
	//LinearVelocity = ((2 * PI) / 60) * radius * RPM
	
	float rpm = velocity;
	const char* debugStr = "[+] SetRotatorVelocity ";
	StepperMotor motor = (function == SLIDER) ? this->slideMotor:this->rotateMotor;
	if (velocityType == LINEAR_MM_SEC) {
		rpm = (velocity / (((2.0f * (float)M_PI) / 60.0f) * this->drivePulleyRadiusMM)); //mm/sec
		debugStr = "[+] SetSliderVelocity: ";
	}

	std::cout << debugStr << std::endl; //DEBUG
	motor.SetRPM(rpm);
}

float Blinds::GetVelocity() const {
	return this->velocity;
}

float Blinds::GetAcceleration() const {
	return this->accelerationMM_Sec2;
}

float Blinds::GetVelocityTarget() const {
	return this->velocityTarget;
}

float Blinds::GetAccelerationTarget() const {
	return this->accelerationTargetMM_Sec2;
}

unsigned short Blinds::GetDistanceMM() const {
	return this->positionMM;
}

unsigned short Blinds::GetMaxDistanceMM() const {
	return this->maxDistanceMM;
}

OpenState Blinds::GetState() const {
	return this->openState;
}
