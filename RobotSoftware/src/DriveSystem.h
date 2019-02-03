/**
 * @file DriveSystem.h
 * @author Juul Bloemers
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef DRIVE_SYSTEM_H
#define DRIVE_SYSTEM_H


///////////////////////////////////////
// INCLUDES
///////////////////////////////////////

#include <stdint.h>

#include "IDrive.h"
#include "IWheelControl.h"
#include "Wheels.h"
#include "Directions.h"
#include "Servo.h"
#include "Pwm.h"


///////////////////////////////////////
// CLASSES
///////////////////////////////////////

class DriveSystem : public IDrive, IWheelControl {

  public:
    
    /**
     * @brief Construct a new Drive System object
     * 
     * @param wheelOne Pin wheel one is connected to.
     * @param wheelTwo Pin wheel two is connected to.
     * @param wheelThree Pin wheel three is connected to.
     */
    DriveSystem(uint8_t wheelOne, uint8_t wheelTwo, uint8_t wheelThree);

    ~DriveSystem();

    /**
     * @brief Drive forwards.
     * 
     */
    void DriveForwards();

    /**
     * @brief Drive backwards.
     * 
     */
    void DriveBackwards();

    /**
     * @brief Rotate left.
     * 
     */
    void RotateLeft();

    /**
     * @brief Rotate right.
     * 
     */
    void RotateRight();

    /**
     * @brief Stop all movement.
     * 
     */
    void StopMovement();

    /**
     * @brief Set direction of wheels.
     * 
     * @param uint8_t Wheels to set the direction of. To set multiple wheel directions use the '|' to combine wheels. Example: 'Wheels::WHEEL_ONE | Wheels::WHEEL_TWO' to set the direction of wheel one and two.
     * @param direction The direction the wheel needs to turn.
     */
    void SetWheelDirection(uint8_t wheels, Directions direction);

    /**
     * @brief Get The direction of a wheel.
     * 
     * @params Wheel to get the direction from.
     * 
     * @returns Directions The wheel its direction.
     */
    Directions GetWheelDirection(Wheels wheel);

  private:

    Servo* servos[3];

};

#endif