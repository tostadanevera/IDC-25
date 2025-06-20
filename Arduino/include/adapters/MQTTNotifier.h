#include "../ports/Notifier.h"
#include <PubSubClient.h>

class MQTTNotifier : public Notifier {
  public:
    MQTTNotifier(PubSubClient& client, const char* topic);
    void notifyAccessGranted(const std::string& uid) override;
    void notifyAccessDenied(const std::string& uid) override;

private:
    PubSubClient& client;
    const char* topic;
};