/**
 * @file IDrive.h
 * @author Juul Bloemers
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef I_DRIVE_H
#define I_DRIVE_H


///////////////////////////////////////
// INTERFACES
///////////////////////////////////////

class IDrive {

  public:

    virtual ~IDrive() {}

    /**
     * @brief Drive forwards.
     * 
     */
    virtual void DriveForwards() = 0;

    /**
     * @brief Drive backwards.
     * 
     */
    virtual void DriveBackwards() = 0;

    /**
     * @brief Rotate left.
     * 
     */
    virtual void RotateLeft() = 0;

    /**
     * @brief Rotate right.
     * 
     */
    virtual void RotateRight() = 0;

    /**
     * @brief Stop all movement.
     * 
     */
    virtual void StopMovement() = 0;
};

#endif