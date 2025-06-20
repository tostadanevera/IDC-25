#include "../../include/adapters/RFIDInput.h"
#include <SPI.h>
#include <Arduino.h>

RFIDInput::RFIDInput(uint8_t ssPin, uint8_t rstPin) : rfid(ssPin, rstPin) {}

void RFIDInput::begin() {
    SPI.begin();
    rfid.PCD_Init();
}

bool RFIDInput::readCard(String& uid) {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
        return false;
    }

    uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();

    while (rfid.PICC_IsNewCardPresent() || rfid.PICC_ReadCardSerial()) {
        delay(50);
    }

    return true;
}
