/**
 * @file Uart.cpp
 * @author Glenn Stamminger
 * @brief 
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 *
 */
#include "Uart.h"

//Constructor.
Uart::Uart()
{
  this->InitSerial();
}

//Destructor.
Uart::~Uart()
{
  this->DeInitSerial();
}

//Read distance data from Grove TF mini lidar.
void Uart::TfMiniDistance()
{
  while (serialDataAvail(this->fd) > 0)
  {
    //Check if data is available.
    this->currentByte = serialGetchar(this->fd);
    if (this->currentByte >= 0)
    {
      if (this->isReadingData)
      {
        this->readDataSymbols++;
        if (this->readDataSymbols == 1)
        {
          this->recievedBuffer = this->currentByte;
        }
        else if (this->recievedBuffer >= 2)
        {
          //Convert data bytes into usable distance.
          this->recievedBuffer |= (static_cast<uint16_t>(this->currentByte) << 8);

          //Check if recieved distance is not out of bounds.
          if(this->recievedBuffer <= 1440)
          {
            this->recievedDistance = this->recievedBuffer;
          }
          this->isReadingData = false;
        }
      }
      if (this->currentByte == 0x59)
      {
        this->readStartSymbols++;
        if (this->readStartSymbols >= 2)
        {
          this->readStartSymbols = 0;
          this->readDataSymbols = 0;
          this->isReadingData = true;
        }
      }
    }
  }
}

//Return the distance.
const uint16_t& Uart::ReturnDistance() const
{
  return this->recievedDistance;
}

//Initialise serial reading.
void Uart::InitSerial()
{
  this->currentByte = 0;
  this->readStartSymbols = 0;
  this->readDataSymbols = 0;
  this->recievedBuffer = 0;
  this->isReadingData = false;

  if ((this->fd = serialOpen("/dev/ttyAMA0", 115200)) < 0)
  {
    fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    return;
  }
  else
  {
    std::cout<<"serial active"<<std::endl;
  }
}

//Close serial.
void Uart::DeInitSerial()
{
  serialClose(this->fd);
  std::cout << "serial closed" << std::endl;
}