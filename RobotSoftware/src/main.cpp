#include <iostream>
#include <unistd.h>

#include <wiringPi.h>

#include "Robot.h"
#include "IClient.h"
#include "InputReader.h"
#include "Client.h"
#include "Port.h"


///////////////////////////////////////
// DEFINES
///////////////////////////////////////


#define IP_ADDRESS ("169.254.207.98")

#define WHEEL_ONE (4)
#define WHEEL_TWO (5)
#define WHEEL_THREE (6)


struct FunctionArgs
{
  IDrive& driver;
};


///////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////


void HandleUserInput(char c, void* args)
{
  IDrive& driver = ((FunctionArgs*) args)->driver;
  switch (c)
  {
    case 'w': 
      driver.DriveForwards();
      break;
    case 'a':
      driver.RotateLeft();
      break;
    case 'd':
      driver.RotateRight();
      break;
    case 's':
      driver.DriveBackwards();
      break;
    default:
      driver.StopMovement();
      break;
  }
}

int main(int argc, char** argv)
{
  if(wiringPiSetup() < 0)
  {
    std::cout << "DRIVE_MODULE: Error setting up wiring pi." << std::endl;
    exit(-1);
  }

  //Create robot.
  Robot robot(WHEEL_ONE, WHEEL_TWO, WHEEL_THREE);

  FunctionArgs args = {.driver = robot};

  InputReader handler(HandleUserInput, (void*)(&args));

  while (1) handler.PollInput();

  return 0;
}