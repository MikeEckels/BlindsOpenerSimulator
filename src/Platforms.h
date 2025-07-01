#ifndef PLATFORMS_H
#define PLATFORMS_H

//#define ESP32
#define _WIN323
#if defined(_WIN323)
#include "WindowsHAL.h"
HAL* hal = new WindowsHAL();
#elif defined(ESP32) || defined(ESP8266) || defined(AVR)
#include "ArduinoHAL.h"
//#include "Arduino.h"
HAL* hal = new ArduinoHAL();
#else
#error "Unsupported platform selected."
#endif

#endif //PLATFORMS_H
