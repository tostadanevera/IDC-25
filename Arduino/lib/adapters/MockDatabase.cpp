// arduino/src/adapters/MockDatabase.cpp
#include "../../include/adapters/MockDatabase.h"

MockDatabase::MockDatabase() {
    authorized.insert("ABC123");
}

bool MockDatabase::isAuthorized(const std::string& uid) {
    return authorized.count(uid) > 0;
}

bool MockDatabase::addCard(const std::string& uid) {
    return authorized.insert(uid).second;
}

bool MockDatabase::removeCard(const std::string& uid) {
    return authorized.erase(uid) > 0;
}
