#pragma once
#include "../ports/OutputDevices.h"

class LEDOutput : public OutputDevices {
public:
    LEDOutput(int pinVerde, int pinRojo);
    void grantAccess() override;
    void denyAccess() override;
private:
    int verde, rojo;
};
