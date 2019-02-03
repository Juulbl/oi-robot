/**
 * @file DriveSystem.cpp
 * @author Juul Bloemers
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "DriveSystem.h"

DriveSystem::DriveSystem(uint8_t wheelOne, uint8_t wheelTwo, uint8_t wheelThree)
{
  //Create servos.
  this->servos[0] = new Servo(wheelOne, 0, 180, 90);
  this->servos[1] = new Servo(wheelTwo, 0, 180, 90);
  this->servos[2] = new Servo(wheelThree, 0, 180, 90);
}

DriveSystem::~DriveSystem()
{
  //Destroy servos.
  for(int i = 0; i < 3; i++) 
  {
    delete servos[i];
  }
}

void DriveSystem::DriveForwards()
{
  this->SetWheelDirection(Wheels::WHEEL_ONE, Directions::COUNTERCLOCKWISE);
  this->SetWheelDirection(Wheels::WHEEL_TWO, Directions::CLOCKWISE);
  this->SetWheelDirection(Wheels::WHEEL_THREE, Directions::NONE);
}

void DriveSystem::DriveBackwards()
{
  this->SetWheelDirection(Wheels::WHEEL_ONE, Directions::CLOCKWISE);
  this->SetWheelDirection(Wheels::WHEEL_TWO, Directions::COUNTERCLOCKWISE);
  this->SetWheelDirection(Wheels::WHEEL_THREE, Directions::NONE);
}

void DriveSystem::RotateLeft()
{
  this->SetWheelDirection(Wheels::WHEEL_ONE | Wheels::WHEEL_TWO | Wheels::WHEEL_THREE, Directions::CLOCKWISE);
}

void DriveSystem::RotateRight()
{
  this->SetWheelDirection(Wheels::WHEEL_ONE | Wheels::WHEEL_TWO | Wheels::WHEEL_THREE, Directions::COUNTERCLOCKWISE);
}

void DriveSystem::StopMovement()
{
  this->SetWheelDirection(Wheels::WHEEL_ONE | Wheels::WHEEL_TWO | Wheels::WHEEL_THREE, Directions::NONE);
}

void DriveSystem::SetWheelDirection(uint8_t wheels, Directions direction)
{
  //The angle to set the wheels.
  uint8_t angle;

  switch(direction)
  {
    case Directions::CLOCKWISE:
      angle = 0;
      break;
    case Directions::COUNTERCLOCKWISE:
      angle = 180;
      break;
      case Directions::NONE:
    default:
      angle = 90;
      break;
  }

  //Check if needs to set wheel one.
  if(wheels & WHEEL_ONE) this->servos[0]->SetAngle(angle);

  //Check if needs to set wheel two.
  if(wheels & WHEEL_TWO) this->servos[1]->SetAngle(angle);

  //Check if needs to set wheel three.
  if(wheels & WHEEL_THREE) this->servos[2]->SetAngle(angle);
}

Directions DriveSystem::GetWheelDirection(Wheels wheel)
{
  return Directions::NONE;
}