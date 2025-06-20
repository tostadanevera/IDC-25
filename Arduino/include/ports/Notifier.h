#pragma once

#include <string>

class Notifier {
public:
    virtual void notifyAccessGranted(const std::string& uid) = 0;
    virtual void notifyAccessDenied(const std::string& uid) = 0;
    virtual ~Notifier() = default;
};
