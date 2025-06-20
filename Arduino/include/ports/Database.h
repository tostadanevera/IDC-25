#pragma once

#include <string>

class Database {
public:
    virtual bool isAuthorized(const std::string& uid) = 0;
    virtual bool addCard(const std::string& uid) = 0;
    virtual bool removeCard(const std::string& uid) = 0;
    virtual ~Database() = default;
};
