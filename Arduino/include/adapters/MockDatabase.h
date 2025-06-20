#pragma once
#include "../ports/Database.h"
#include <set>

class MockDatabase : public Database {
public:
    MockDatabase();
    bool isAuthorized(const std::string& uid) override;
    bool addCard(const std::string& uid) override;
    bool removeCard(const std::string& uid) override;
private:
    std::set<std::string> authorized;
};
