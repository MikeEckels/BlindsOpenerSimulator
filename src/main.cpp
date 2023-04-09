#include <conio.h>
#include <iostream>

#include "Blinds.h"

Button button = Button();
Blinds blinds = Blinds();

int main() {
	blinds.SetVelocityTarget(SLIDER, LINEAR_MM_SEC, 200.0f);
	blinds.SetVelocityTarget(ROTATOR, ANGULAR_RPM, 10.0f);
	char key = 'a';

	while (key != 'e') {
		key = _getch();

		switch (key) {
		case 'b':
			button.Press();
			break;
		case 'l':
			blinds.TurnEncoderLeft(1);
			break;
		case 'r':
			blinds.TurnEncoderRight(1);
			break;
		case 'o':
			blinds.OpenShades();
			break;
		case 'c':
			blinds.CloseShades();
			break;
		default:
			std::cout << "[!] Unrecognized command" << std::endl;
		}

		if (button.ReadState()) {
			if (blinds.GetState()) {
				blinds.Close();
			}
			else {
				blinds.Open();
			}
			std::cout << "SliderPositionMM: " << blinds.GetDistanceMM() << std::endl << std::endl;
		}
	}
}