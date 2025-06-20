#include "../../include/adapters/FileDatabase.h"
#include <LittleFS.h>
#include <Arduino.h>

FileDatabase::FileDatabase(const char* filename) : file(filename) {
    LittleFS.begin(true);  // Monta el sistema de archivos
    loadFromFile();
}

void FileDatabase::loadFromFile() {
    authorized.clear();
    File f = LittleFS.open(file, "r");
    if (!f) return;

    while (f.available()) {
        String line = f.readStringUntil('\n');
        line.trim();
        if (line.length() > 0) {
            authorized.insert(line.c_str());
        }
    }
    f.close();
}

void FileDatabase::saveToFile() {
    File f = LittleFS.open(file, "w");
    if (!f) return;

    for (const auto& uid : authorized) {
        f.println(uid.c_str());
    }
    f.close();
}

bool FileDatabase::isAuthorized(const std::string& uid) {
    return authorized.count(uid) > 0;
}

bool FileDatabase::addCard(const std::string& uid) {
    if (authorized.insert(uid).second) {
        saveToFile();
        return true;
    }
    return false;
}

bool FileDatabase::removeCard(const std::string& uid) {
    if (authorized.erase(uid)) {
        saveToFile();
        return true;
    }
    return false;
}
