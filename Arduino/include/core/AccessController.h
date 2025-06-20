#pragma once

#include "../ports/Database.h"
#include "../ports/Notifier.h"
#include "../ports/OutputDevices.h"

class AccessController {
public:
    AccessController(Database& db, Notifier& notifier, OutputDevices& output);
    void begin();
    bool onCardRead(const std::string& uid);
    bool registerCard(const std::string& uid);
private:
    Database& db;
    Notifier& notifier;
    OutputDevices& output;
};
