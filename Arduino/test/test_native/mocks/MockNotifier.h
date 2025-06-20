#pragma once
#include <string>
using std::string;
#include "../../../include/ports/Notifier.h"

class MockNotifier : public Notifier {
private:
    std::string lastNotification;
    int grantedCount = 0;
    int deniedCount = 0;
public:
    void notifyAccessGranted(const std::string& uid) override {
        lastNotification = "GRANTED: " + uid;
        grantedCount++;
    }
    
    void notifyAccessDenied(const std::string& uid) override {
        lastNotification = "DENIED: " + uid;
        deniedCount++;
    }
    
    void reset() {
        lastNotification.clear();
        grantedCount = 0;
        deniedCount = 0;
    }
    
    std::string getLastNotification() const { return lastNotification; }
    int getGrantedCount() const { return grantedCount; }
    int getDeniedCount() const { return deniedCount; }
};