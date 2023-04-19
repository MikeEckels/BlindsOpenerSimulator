#include "Blinds.h"

Blinds::Blinds() {
	this->attribs.encoder.SetIncrement(this->attribs.encoderIncrement);
	this->attribs.drivePulleyRadiusMM = ((((float)this->attribs.pulleyTeeth * (float)this->attribs.beltPitchmm) / (float)M_PI) / 2.0f);
}

float Blinds::degreesTomm(float degrees) {
	return (((float)M_PI / 180.0f) * degrees * this->attribs.drivePulleyRadiusMM);
}

float Blinds::mmToDegrees(float distanceMM) {
	return (180.0f * distanceMM) / ((float)M_PI * this->attribs.drivePulleyRadiusMM);
}

void Blinds::Open() {
	if (this->openState != ALL_OPEN) {
		Blinds::OpenShades();
		this->attribs.slideMotor.SetDirection(CW);
		this->attribs.slideMotor.Enable();
		this->attribs.slideMotor.MoveDegrees(Blinds::mmToDegrees(this->attribs.maxDistanceMM));
		this->attribs.slideMotor.Disable();
		std::cout << "[+] Opened - SlideMotor PosDeg: " << this->attribs.slideMotor.GetPositionDegrees() << " | PosSteps: " << this->attribs.slideMotor.GetPositionSteps() << std::endl;
	}
	else {
		std::cout << "[!] Blinds and shades are already open" << std::endl;
	}
	this->openState = ALL_OPEN;
	this->positionMM = (unsigned short)Blinds::degreesTomm(this->attribs.slideMotor.GetPositionDegrees());
}

void Blinds::Close() {
	if (this->openState != ALL_CLOSED) {
		this->attribs.slideMotor.SetDirection(CCW);
		this->attribs.slideMotor.Enable();
		this->attribs.slideMotor.MoveDegrees(Blinds::mmToDegrees((float)this->attribs.maxDistanceMM));
		this->attribs.slideMotor.Disable();
		std::cout << "[+] Closed - SlideMotor PosDeg: " << this->attribs.slideMotor.GetPositionDegrees() << " | PosSteps: " << this->attribs.slideMotor.GetPositionSteps() << std::endl;
		Blinds::CloseShades();
	}
	else if (this->openState == SHADES_OPEN) {
		Blinds::CloseShades();
	}
	else {
		std::cout << "[!] Blinds and shades are already closed" << std::endl;
	}
	this->openState = ALL_CLOSED;
	this->positionMM = (unsigned short)Blinds::degreesTomm(this->attribs.slideMotor.GetPositionDegrees());
}

void Blinds::OpenShades() {
	if (this->openState == ALL_CLOSED) {
		this->attribs.rotateMotor.SetDirection(CW);
		this->attribs.rotateMotor.Enable();
		this->attribs.rotateMotor.MoveDegrees((float)this->attribs.rotateDegrees);
		this->attribs.rotateMotor.Disable();
		std::cout << "[+] OpenedShades - RotateMotor PosDeg: " << this->attribs.rotateMotor.GetPositionDegrees() << " | PosSteps: " << this->attribs.rotateMotor.GetPositionSteps() << std::endl;
	}
	else {
		std::cout << "[!] Shades are already open" << std::endl;
	}
	this->openState = SHADES_OPEN;
}

void Blinds::CloseShades() {
	if (this->openState == SHADES_OPEN) {
		this->attribs.rotateMotor.SetDirection(CCW);
		this->attribs.rotateMotor.Enable();
		this->attribs.rotateMotor.MoveDegrees((float)this->attribs.rotateDegrees);
		this->attribs.rotateMotor.Disable();
		this->openState = ALL_CLOSED;
		std::cout << "[+] ClosedShades - RotateMotor Pos: " << this->attribs.rotateMotor.GetPositionDegrees() << " | PosSteps: " << this->attribs.rotateMotor.GetPositionSteps() << std::endl;
	}
	else if (this->openState == ALL_CLOSED) {
		std::cout << "[!] Shades are already closed" << std::endl;
	}
	else if (this->openState == ALL_OPEN) {
		std::cout << "[!] Can not close shades with slider open" << std::endl;
	}
}

void Blinds::PressEncoder() {
	this->attribs.encoder.PressButton();
}

void Blinds::TurnEncoderLeft(unsigned char numClicks) {
	this->attribs.encoder.TurnLeft(numClicks);
}

void Blinds::TurnEncoderRight(unsigned char numClicks) {
	this->attribs.encoder.TurnRight(numClicks);
}

void Blinds::SetEncoderIncrement(signed char value) {
	Blinds::GetMechanicalAttribs().encoder.SetIncrement(value);
}

void Blinds::SetAccelerationTarget(MotorFunction function, float mmPerSec2) {
	//TODO
}

void Blinds::SetVelocityTarget(MotorFunction function, VelocityType velocityType, float velocity) {
	//AngularVelocity = RPM
	//LinearVelocity = ((2 * PI) / 60) * radius * RPM

	float rpm = velocity;
	const char* debugStr = "[+] SetRotatorVelocity ";
	StepperMotor motor = (function == SLIDER) ? this->attribs.slideMotor : this->attribs.rotateMotor;
	if (velocityType == LINEAR_MM_SEC) {
		rpm = (velocity / (((2.0f * (float)M_PI) / 60.0f) * this->attribs.drivePulleyRadiusMM)); //mm/sec
		debugStr = "[+] SetSliderVelocity: ";
	}

	std::cout << debugStr << std::endl;
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
	return this->attribs.maxDistanceMM;
}

MechanicalAttribs Blinds::GetMechanicalAttribs() const {
	return this->attribs;
}

OpenState Blinds::GetState() const {
	return this->openState;
}
