/**
 * @file Pwm.h
 * @author Lars Bloemers & Juul Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-11-22
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef PWM_H
#define PWM_H

///////////////////////////////////////
// INCLUDES
///////////////////////////////////////

#include <iostream>
#include <stdint.h>
#include <map>

#include <wiringPi.h>

///////////////////////////////////////
// CLASSES
///////////////////////////////////////

class Pwm 
{
  public:
    static Pwm* GetInstance();

    /**
     * @brief Initialize pwm.
     * 
     * @param frequency Number of cycles each second.
     * @param prescaler Number of steps one section (1000ms / frequency) is devided in.
     * @return int8_t Lower than 0 on error.
     */
    int8_t Init(double frequency, uint16_t prescaler);

    /**
     * @brief Registers a pin as a PWM pin.
     * 
     * @param pin Pin to initialize.
     * @param initialValue Value the pin is set to.
     * @return int8_t Lower than 0 on error. 
     */
    int8_t InitPin(uint8_t pin, uint16_t initialValue);

    /**
     * @brief Remove pin from PWM pins.
     * 
     * @param pin Pin to remove.
     * @return int8_t Lower than 0 on error.
     */
    int8_t UnInitPin(uint8_t pin);

    /**
     * @brief Set duty cycle.
     * 
     * @param pin Pin to set the duty cycle of.
     * @param dutyCycle Value between 0 and the rescaler.
     * @return int8_t Lower than 0 on error.
     */
    int8_t SetDutyCycle(uint8_t pin, uint16_t dutyCycle);

    /**
     * @brief Update PWM GPIOs.
     * 
     */
    void Update();

  private:
    static Pwm* instance;

    std::map<uint8_t, uint16_t> pins;

    uint64_t lastTimePulsed;
    uint16_t prescaler;
    uint16_t currentTick;
    uint64_t tickTimeMicro;

    void PwmTick();
};

#endif