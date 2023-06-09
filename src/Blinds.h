#ifndef BLINDS_H
#define BLINDS_H

#define _USE_MATH_DEFINES
#include <math.h>

#include "Button.h"
#include "Encoder.h"
#include "StepperMotor.h"

enum MotorFunction{SLIDER, ROTATOR};
enum VelocityType{LINEAR_MM_SEC, ANGULAR_RPM};
enum OpenState{ALL_CLOSED, ALL_OPEN, SHADES_OPEN};

struct MechanicalAttribs {
	float drivePulleyRadiusMM = 0.0f;
	signed char encoderIncrement = 25;
	const unsigned char beltPitchmm = 2;
	const unsigned char pulleyTeeth = 16;
	const unsigned char rotateDegrees = 90;
	const unsigned short maxDistanceMM = 1524; //5ft

	Encoder encoder = Encoder();
	StepperMotor rotateMotor = StepperMotor();
	StepperMotor slideMotor = StepperMotor();
};

class Blinds {
private:
	//Velocities are mm/sec or RPM
	float velocity = 0.0f;
	float accelerationMM_Sec2 = 0.0f;
	float velocityTarget = 0.0f;
	float accelerationTargetMM_Sec2 = 0.0f;
	unsigned short positionMM = 0;
	OpenState openState = ALL_CLOSED;

	MechanicalAttribs attribs;

	float degreesTomm(float degrees);
	float mmToDegrees(float distanceMM);

public:
	Blinds();
	~Blinds() = default;

	void Open();
	void Close();
	void OpenShades();
	void CloseShades();
	void PressEncoder();
	void TurnEncoderLeft(unsigned char numClicks);
	void TurnEncoderRight(unsigned char numClicks);

	void SetEncoderIncrement(signed char value);
	void SetAccelerationTarget(MotorFunction function, float acceleration);
	void SetVelocityTarget(MotorFunction function, VelocityType velocityType, float velocity);

	float GetVelocity() const;
	float GetAcceleration() const;
	float GetVelocityTarget() const;
	float GetAccelerationTarget() const;
	unsigned short GetDistanceMM() const;
	unsigned short GetMaxDistanceMM() const;
	MechanicalAttribs GetMechanicalAttribs() const;
	OpenState GetState() const;

};

#endif //BLINDS_H
