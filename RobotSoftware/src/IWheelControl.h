/**
 * @file IWheelControl.h
 * @author Juul Bloemers
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef I_WHEEL_CONTROL_H
#define I_WHEEL_CONTROL_H


///////////////////////////////////////
// INCLUDES
///////////////////////////////////////

#include "stdint.h"

#include "Wheels.h"
#include "Directions.h"


///////////////////////////////////////
// INTERFACES
///////////////////////////////////////

class IWheelControl {

  public:

    virtual ~IWheelControl() {}

    /**
     * @brief Set direction of wheels.
     * 
     * @param uint8_t Wheels to set the direction of.
     * @param direction The direction the wheel needs to turn.
     */
    virtual void SetWheelDirection(uint8_t wheels, Directions direction) = 0;

    /**
     * @brief Get The direction of a wheel.
     * 
     * @params Wheel to get the direction from.
     * 
     * @returns Directions The wheel its direction.
     */
    virtual Directions GetWheelDirection(Wheels wheel) = 0;

};

#endif