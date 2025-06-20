#pragma once
#include <MFRC522.h>

class RFIDInput {
public:
    RFIDInput(uint8_t ssPin, uint8_t rstPin);
    void begin();
    bool readCard(String& uid);  // Devuelve true si se leyó una tarjeta

private:
    MFRC522 rfid;
};
