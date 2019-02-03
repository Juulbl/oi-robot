/**
 * @file Robot.h
 * @author Juul Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-21
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef ROBOT_H
#define ROBOT_H


///////////////////////////////////////
// INCLUDES
///////////////////////////////////////

#include <stdint.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <unistd.h>

#include "Pwm.h"
#include "DriveSystem.h"
#include "MappingLogic.h"
#include "ComputerVision.h"
#include "ComputerVisionModule.h"
#include "FaceAnalyzer.h"
#include "IVision.h"
#include "ICvAnalyzer.h"
#include "RaspiCamera.h"
#include "ThreadHandler.h"


///////////////////////////////////////
// DEFINES
///////////////////////////////////////

#define CASCADE_FILE_FACE ("./haarcascades/haarcascade_frontalface_alt.xml")
#define CASCADE_FILE_EYES ("./haarcascades/haarcascade_eye_tree_eyeglasses.xml")
#define IMAGE_COUNT (2000)
#define FACE_ANALYZER_SCALE_FACTOR (1.85f)
#define FACE_ANALYZER_NEIGHBOR_COUNT (2)


///////////////////////////////////////
// CLASSES
///////////////////////////////////////

class Robot : public IDrive {

public:

  /**
   * @brief Construct a new Robot object.
   * 
   * @param wheelOne Front left wheel Wiring Pi pin number.
   * @param wheelTwo Front right wheel Wiring Pi pin number.
   * @param wheelThree Back wheel Wiring Pi pin number.
   */
  Robot(uint8_t wheelOne, uint8_t wheelTwo, uint8_t wheelThree);

  ~Robot();

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

private:

  //PWM.
  ThreadHandler<Pwm*>* pwmThread;

  //Mapping system.
  ThreadHandler<MappingLogic*>* mappingThread;
  MappingLogic* mappingSystem;

  //Drive system.
  DriveSystem* driveSystem;

  //Computer vision.
  ThreadHandler<ComputerVisionModule*>* cvThread;
  ICvCamera* raspiCam;
  ICvAnalyze* faceAnalyzer;
  IVision* computerVision;
  ComputerVisionModule* cvMod;

};

#endif