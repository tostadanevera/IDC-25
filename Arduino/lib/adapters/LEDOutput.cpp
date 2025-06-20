// arduino/src/adapters/LEDOutput.cpp
#include "../../include/adapters/LEDOutput.h"
#include <Arduino.h>

LEDOutput::LEDOutput(int pinVerde, int pinRojo) : verde(pinVerde), rojo(pinRojo) {
    pinMode(verde, OUTPUT);
    pinMode(rojo, OUTPUT);
}

void LEDOutput::grantAccess() {
    digitalWrite(rojo, LOW);
    digitalWrite(verde, HIGH);
    delay(1000);
    digitalWrite(verde, LOW);
}

void LEDOutput::denyAccess() {
    digitalWrite(verde, LOW);
    digitalWrite(rojo, HIGH);
    delay(1000);
    digitalWrite(rojo, LOW);
}
