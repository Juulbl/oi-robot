/**
 * @file Servo.cpp
 * @author Juul Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-11-22
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "Servo.h"

Servo::Servo(uint8_t pin, uint8_t minAngle, uint8_t maxAngle, uint8_t initialAngle)
  : pin(pin), minAngle(minAngle), maxAngle(maxAngle), dutyCycleStartMs(1.0), dutyCycleEndMs(2.0)
{
  //Setup pwm.
  if(Pwm::GetInstance()->InitPin(pin, 0))
  {
    throw std::runtime_error("Could not initialize pwm.");
  }

  //Set angle.
  this->SetAngle(initialAngle);
}

Servo::Servo(uint8_t pin, uint8_t minAngle, uint8_t maxAngle, uint8_t initialAngle, float dutyCycleStartMs, float dutyCycleEndMs)
  : pin(pin), minAngle(minAngle), maxAngle(maxAngle), dutyCycleStartMs(dutyCycleStartMs), dutyCycleEndMs(dutyCycleEndMs)
{
  //Setup pwm.
  if(Pwm::GetInstance()->InitPin(pin, 0))
  {
    throw std::runtime_error("Could not initialize pwm.");
  }

  //Set angle.
  this->SetAngle(initialAngle);
}

Servo::~Servo()
{

}

uint8_t Servo::GetAngle()
{
  return this->angle;
}

void Servo::SetAngle(uint8_t angle)
{
  //If angle not in range, clip angle.
  if(angle > this->maxAngle) angle = this->maxAngle;
  else if(angle < this->minAngle) angle = this->minAngle;

  //Set duty cycle.
  Pwm::GetInstance()->SetDutyCycle(this->pin, static_cast<uint16_t>(((((this->dutyCycleEndMs - this->dutyCycleStartMs) / 180.0) * angle) + this->dutyCycleStartMs) / (1000.0 / (SERVO_PWM_FREQUENCY * SERVO_PWM_PRESCALER))));
}