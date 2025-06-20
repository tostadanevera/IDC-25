#include "../../include/adapters/MQTTNotifier.h"

MQTTNotifier::MQTTNotifier(PubSubClient& client, const char* topic)
    : client(client), topic(topic) {}

void MQTTNotifier::notifyAccessGranted(const std::string& uid) {
    String message = String("{\"uid\":\"") + uid.c_str() + "\",\"access\":true}";
    client.publish(topic, message.c_str());
}

void MQTTNotifier::notifyAccessDenied(const std::string& uid) {
    String message = String("{\"uid\":\"") + uid.c_str() + "\",\"access\":false}";
    client.publish(topic, message.c_str());
}