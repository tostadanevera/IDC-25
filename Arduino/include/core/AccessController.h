#pragma once
#include <vector>
#include <string>
#include "ports/Database.h"
#include "ports/OutputDevices.h"
#include "ports/Notifier.h"

class AccessController {
public:
    AccessController(Database& db, OutputDevices& output);
    void addNotifier(Notifier* notifier);  // Nuevo método
    void begin();
    bool onCardRead(const std::string& uid);
    bool registerCard(const std::string& uid);

private:
    Database& db;
    OutputDevices& output;
    std::vector<Notifier*> notifiers;  // Ahora hay múltiples notifiers
};
