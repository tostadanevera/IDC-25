#pragma once
#include <string>
using std::string;
#include <unordered_set>
#include "../../../include/ports/Database.h"

class MockDatabase : public Database {
private:
    std::unordered_set<std::string> authorizedCards;
public:
    bool isAuthorized(const std::string& uid) override {
        return authorizedCards.count(uid) > 0;
    }
    
    bool addCard(const std::string& uid) override {
        return authorizedCards.insert(uid).second;
    }
    
    bool removeCard(const std::string& uid) override {
        return authorizedCards.erase(uid) > 0;
    }
    
    void setTestData(const std::string& uid, bool authorized) {
        if(authorized) {
            authorizedCards.insert(uid);
        } else {
            authorizedCards.erase(uid);
        }
    }
};