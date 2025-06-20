#pragma once
#include "../ports/Database.h"
#include <string>
#include <set>

class FileDatabase: public Database {
public:
    FileDatabase(const char* filename);
    bool isAuthorized(const std::string& uid);
    bool addCard(const std::string& uid);
    bool removeCard(const std::string& uid);

private:
    std::set<std::string> authorized;
    const char* file;
    void loadFromFile();
    void saveToFile();
};
