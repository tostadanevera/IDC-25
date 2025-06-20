// arduino/src/adapters/SerialNotifier.cpp
#include "../../include/adapters/SerialNotifier.h"

#include <Arduino.h>

void SerialNotifier::notifyAccessGranted(const std::string& uid) {
    Serial.println("ACCESO CONCEDIDO: " + String(uid.c_str()));
}

void SerialNotifier::notifyAccessDenied(const std::string& uid) {
    Serial.println("ACCESO DENEGADO: " + String(uid.c_str()));
}
