#pragma once
#include "../../../include/ports/OutputDevices.h"
#include <string>
using std::string;

class MockOutput : public OutputDevices {
private:
    std::string lastAction;
    int grantCount = 0;
    int denyCount = 0;
public:
    void grantAccess() override {
        lastAction = "GRANTED";
        grantCount++;
    }
    
    void denyAccess() override {
        lastAction = "DENIED";
        denyCount++;
    }
    
    void reset() {
        lastAction.clear();
        grantCount = 0;
        denyCount = 0;
    }
    
    std::string getLastAction() const { return lastAction; }
    int getGrantCount() const { return grantCount; }
    int getDenyCount() const { return denyCount; }
};