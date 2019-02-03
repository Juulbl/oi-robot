#ifndef CLIENT_H
#define CLIENT_H

#include "Connection.h"
#include "IClient.h"

#include <arpa/inet.h>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class Client : public IClient
{
    public:

        /**
         * @brief Construct a new Client object
         * 
         * @param messageBufferSize 
         * @param ipAddress 
         * @param portNumber
         * 
         * @throw invalid_argument Ipaddress is not correct
         * @throw runtime_error Can't connect 
         * @throw domain_error Cannot create socket
         */
        Client(size_t messageBufferSize, const std::string& ipAddress, 
            uint32_t portNumber, double timeout);

        /**
         * @brief Prevents copying the object
         * 
         * @param other 
         */
        Client(const Client& other) = delete;

        /**
         * @brief Prevents creating a new 
         * 
         * @param other
         */
        Client(Client&& other) = delete;

        ~Client() noexcept;

        /**
         * @brief Connects the client to a given ipAddress
         * 
         * @param ipAddress 
         * 
         * @throw invalid_argument Ipaddress is not correct
         * @throw runtime_error Can't connect
         */
        void Connect(const std::string& ipAddress);

        /**
         * @brief Disconnectes Client from the server
         * 
         */
        void Disconnect();

        /**
         * @brief Returns if the client is connected to the socket
         * 
         * @return true If client is still connected
         * @return false If client is disconnected
         */
        bool GetIsConnected() const;

        /**
         * @brief Sends a message to the server
         * 
         * @param message 
         */
        void SendMessage(std::string& message) const;
        void SendMessage(std::string&& message) const;

        /**
         * @brief Reads the incomming bytes of the socket
         * 
         * @return std::string Response 
         * 
         * @post Returns "" if nothing came in, otherwise it'll return the received message
         */
        std::string ReadMessage();

        /**
         * @brief 
         * 
         * @param other 
         * @return Client& 
         */
        Client& operator= (const Client& other);

        /**
         * @brief 
         * 
         * @param other 
         * @return Client& 
         */
        Client& operator= (Client&& other);

    private:
    
        char* messageBuffer;
        const size_t MessageBufferSize;
        const std::string IpAddress;
        bool isConnected;
        const uint32_t PortNumber;
        int16_t selfSocket;
        fd_set server;
        struct sockaddr_in socketAddress;
        struct timeval timeout;

        /**
         * @brief Create the client socket
         * 
         * @throw domain_error Cannot create socket
         */
        void CreateOwnSocket();

        /**
         * @brief Create a Socket Address Struct object
         * 
         * @param family 
         * @param portNumber 
         * @param inAddrType 
         */
        void CreateSocketAddressStruct(uint8_t family, uint32_t portNumber, uint64_t inAddrType);
};

#endif