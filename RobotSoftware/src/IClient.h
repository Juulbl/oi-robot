#ifndef ICLIENT_H
#define ICLIENT_H

#include <stddef.h>
#include <string>

class IClient
{
    public:
        virtual ~IClient() {};

        virtual void Connect(const std::string& ipAddress) = 0;
        virtual void Disconnect() = 0;
        virtual bool GetIsConnected() const = 0;
        virtual void SendMessage(std::string& message) const = 0;
        virtual void SendMessage(std::string&& message) const = 0;
        virtual std::string ReadMessage() = 0;
};

#endif