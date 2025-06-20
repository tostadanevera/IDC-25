#pragma once
#include "../ports/Notifier.h"

class SerialNotifier : public Notifier {
public:
    void notifyAccessGranted(const std::string& uid) override;
    void notifyAccessDenied(const std::string& uid) override;
};
