#include "Client.h"

Client::Client(size_t messageBufferSize, const std::string& ipAddress, 
            uint32_t portNumber, double timeout)
    : messageBuffer(new char[messageBufferSize]), MessageBufferSize(messageBufferSize),
    IpAddress(ipAddress), PortNumber(portNumber)
{
    //Set timeout
    memset(&this->timeout, 0, sizeof(this->timeout));
    int16_t seconds = static_cast<uint16_t>(timeout);
    timeout -= seconds;
    this->timeout.tv_sec = seconds;
    this->timeout.tv_usec = timeout * 1000000;

    std::cout << "Port: " << PortNumber << std::endl;   

    //Create a socket
    CreateOwnSocket();
    
    //Set the address of the socket
    CreateSocketAddressStruct(AF_INET, this->PortNumber, 0);

    //Connect the socket to the server
    Connect(this->IpAddress);
}



Client::~Client()
{
    delete[] this->messageBuffer;
    this->messageBuffer = NULL;
    Disconnect();
}

void Client::Connect(const std::string& ipAddress)
{
    if (isConnected == true) return;

    //Check if a connection is possible
    int16_t connectionResult = inet_pton(AF_INET, ipAddress.c_str(), &this->socketAddress.sin_addr);
    
    //Check if successful
    if(connectionResult != 1)
    {
        throw std::invalid_argument("Ip is not valid");
    }
    else 
    {
        //Connect to server
        connectionResult = connect(this->selfSocket, (struct sockaddr*)&this->socketAddress, sizeof(this->socketAddress));

        if (connectionResult < 0) 
        {
            throw std::runtime_error("Can't connect");
        }
        else
        {
            std::cout << "Connected to " << ipAddress << "!" <<std::endl;
            this->isConnected = true;
        }
    }
}

void Client::Disconnect()
{
    if (isConnected == false) return;

    std::cout << "Disconnected" << std::endl;
    this->isConnected = false;
    close(this->selfSocket);
}

bool Client::GetIsConnected() const { return this->isConnected; }

void Client::SendMessage(std::string& message) const
{
    size_t numberOfBytes = send(this->selfSocket, message.c_str(), message.size(), 0);

    if (numberOfBytes != message.size())
    {
        std::cerr << "Could not send all bytes (" << numberOfBytes 
        << "/" << message.size() << ")" << std::endl;
    }

    std::cout << "Message: " << message << std::endl;
}

void Client::SendMessage(std::string&& message) const 
{
    SendMessage(message);
}

std::string Client::ReadMessage()
{
    std::string message = "";

    //Clear buffer
    this->messageBuffer[0] = '\0';

    //Reset server
    FD_ZERO(&this->server);

    //Add client to server
    FD_SET(this->selfSocket, &this->server);

    //Create new timer interval
    struct timeval interval = {this->timeout.tv_sec, this->timeout.tv_usec};

    int16_t activity = select(this->selfSocket + 1, &this->server, NULL, NULL, &interval);

    //Check activity
    if (activity < 0)
    {   
        std::cerr << "Error getting server data" << std::endl;
    }
    else 
    {
        if (FD_ISSET(this->selfSocket, &this->server))
        {
            ssize_t numberOfBytes = read(this->selfSocket, this->messageBuffer, 
            this->MessageBufferSize - 1);

            messageBuffer[numberOfBytes] = '\0';
            
            //Check if server is still online
            if (numberOfBytes > 0)
            {
                //Concat null termincator
                this->messageBuffer[this->MessageBufferSize] = '\0';
                message = this->messageBuffer;
                std::cout << "Message: " << message << std::endl;

                std::cout << "Received " << numberOfBytes << " bytes: " << message << std::endl;;
            }
            else if (numberOfBytes == 0) 
            {
                std::cout << "Disconnected from server" << std::endl;
                this->isConnected = false;
            }
            else 
            {
                std::cerr << "Connection error, disconnecting!" << std::endl;
                this->isConnected = false;
            }

        }
    
    }

    return message;
}

Client& Client::operator= (const Client& other)
{
    return *this;
}

Client& Client::operator= (Client&& other)
{
    return *this;
}

//////////////////////////////////
//Private methods
//////////////////////////////////

void Client::CreateOwnSocket()
{
    this->selfSocket = socket(CONNECTION_FAMILY, CONNECTION_TYPE, CONNECTION_PROTOCOL);
    if (this->selfSocket < 0)
    {
        throw std::domain_error("Cannot create socket");
    }
}

void Client::CreateSocketAddressStruct(uint8_t family, uint32_t portNumber, uint64_t inAddrType)
{
    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = family;
    socketAddress.sin_port = htons(portNumber);
    socketAddress.sin_addr.s_addr = htonl(inAddrType);
}