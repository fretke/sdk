#ifndef MESSAGE_FORMATTER
#define MESSAGE_FORMATTER

#include <ArduinoJson.h>

struct MessageDetails
{
    int method = -1;
    int seq = -1;

    MessageDetails()
    {
        Serial.println("constructor call");
    };

    MessageDetails(const MessageDetails &other) : method(other.method), seq(other.seq)
    {
        Serial.println("copying");
    }
};

class MessageFormatter
{
public:
    MessageFormatter() = delete;
    template <typename T>
    static void FormatUpdate(char *emptyContainer, char *method, T &value, int &seq)
    {
        DynamicJsonDocument doc(1024);
        doc["kind"] = method;
        doc["value"] = value;
        doc["seq"] = seq;

        char dst[100];

        serializeJson(doc, dst);

        sprintf(emptyContainer, "%s", dst);
    }

    static void FormatAction(char *emptyContainer, char *destination, const int &method, int &seq)
    {
        DynamicJsonDocument doc(1024);
        doc["dst"] = destination;
        doc["method"] = method;
        doc["seq"] = seq;

        char dst[100];

        serializeJson(doc, dst);

        sprintf(emptyContainer, "%s", dst);
    }

    static MessageDetails getMessageDetails(uint8_t *payload)
    {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);

        MessageDetails details;
        details.method = doc["method"];
        details.seq = doc["seq"];

        return details;
    }
};

#endif