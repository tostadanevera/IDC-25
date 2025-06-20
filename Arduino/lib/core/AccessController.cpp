#include "core/AccessController.h"
#include "ports/OutputDevices.h"
#include "ports/Database.h"
#include "ports/Notifier.h"
#include <string>
using std::string;

AccessController::AccessController(Database& db, Notifier& notifier, OutputDevices& output)
    : db(db), notifier(notifier), output(output) {}

void AccessController::begin() {
    // Inicialización si hiciera falta
}

bool AccessController::onCardRead(const std::string& uid) {
    if (db.isAuthorized(uid)) {
        output.grantAccess();
        notifier.notifyAccessGranted(uid);
    } else {
        output.denyAccess();
        notifier.notifyAccessDenied(uid);
    }

    return db.isAuthorized(uid);
}

bool AccessController::registerCard(const std::string& uid) {
    return db.addCard(uid);
}
