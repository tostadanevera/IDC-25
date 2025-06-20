#include "../../include/core/AccessController.h"

AccessController::AccessController(Database& db, OutputDevices& output)
    : db(db), output(output) {}

void AccessController::addNotifier(Notifier* notifier) {
    notifiers.push_back(notifier);
}

void AccessController::begin() {}

bool AccessController::onCardRead(const std::string& uid) {
    bool authorized = db.isAuthorized(uid);
    if (authorized) {
        output.grantAccess();
        for (auto n : notifiers) {
            n->notifyAccessGranted(uid);
        }
    } else {
        output.denyAccess();
        for (auto n : notifiers) {
            n->notifyAccessDenied(uid);
        }
    }
    return authorized;
}

bool AccessController::registerCard(const std::string& uid) {
    return db.addCard(uid);
}