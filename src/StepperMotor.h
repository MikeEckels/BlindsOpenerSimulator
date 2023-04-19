#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "Delay.h"
#include "StepperDriver.h"

class StepperMotor {
private:
	float RPM = 0.0f;
	float position = 0.0f;;
	float stepDelayuS = 0.0f;
	float stepFrequency = 0.0f;
	float stepAngleDivisions = 0.0f;
	long numSteps = 0;

	const float stepAngle = 1.8f; //Datasheet
	StepperDriver driver = StepperDriver(SIXTEEN);

	void handleStep();
	
public:
	StepperMotor();
	~StepperMotor() = default;

	void Enable();
	void Disable();
	void MoveDegrees(float degrees);
	void MoveRadians(float radians);

	void SetRPM(float RPM);
	void SetDirection(MotorDirection direction);

	float GetRPM() const;
	float GetStepAngle() const;
	float GetStepDelayuS() const;
	float GetStepFrequency() const;
	float GetStepAngleDivisions() const;

	long GetPositionSteps() const;
	float GetPositionDegrees() const;
	MotorDirection GetDirection() const;
	StepperDriver GetStepperDriver() const;

};

#endif //STEPPER_MOTOR_H
