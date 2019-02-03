/**
 * @file Robot.cpp
 * @author Juul Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-21
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "Robot.h"


///////////////////////////////////////
// STATIC FUNCTIONS
///////////////////////////////////////

static void PWMUpdate(Pwm* pwm)
{
  while(1) pwm->Update();
}

static void MappingSystemUpdate(MappingLogic* mapper)
{
  while(1) mapper->Update();
}

static void CvSystemUpdate(ComputerVisionModule* cvMod)
{
  while (1) cvMod->Update();
}


///////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////

Robot::Robot(uint8_t wheelOne, uint8_t wheelTwo, uint8_t wheelThree)
{

  //Init pwm.
  Pwm::GetInstance()->Init(50, 1024);

  //
  //Set pwm on new thread.
  //
  this->pwmThread = new ThreadHandler<Pwm*>(PWMUpdate, Pwm::GetInstance());

  //
  //Create new drive system.
  //
  this->driveSystem = new DriveSystem(wheelOne, wheelTwo, wheelThree);

  //
  //Create new mapping system.
  //
  this->mappingSystem = new MappingLogic();

  //Create mapping thread.
  this->mappingThread = new ThreadHandler<MappingLogic*>(MappingSystemUpdate, this->mappingSystem);

  //
  //Create computer vision.
  //
  this->raspiCam = new RaspiCamera(320, 240);
  this->faceAnalyzer = new FaceAnalyzer(CASCADE_FILE_FACE, FACE_ANALYZER_NEIGHBOR_COUNT, FACE_ANALYZER_SCALE_FACTOR);
  this->computerVision = new ComputerVision(*this->raspiCam, *this->faceAnalyzer);
  this->cvMod = new ComputerVisionModule(*this->raspiCam, *this->computerVision);

  //Create cv thread.
  this->cvThread = new ThreadHandler<ComputerVisionModule*>(CvSystemUpdate, this->cvMod);

}

Robot::~Robot()
{

  //Delete cv thread.
  delete this->cvThread;

  //Delete cv system.
  delete this->cvMod;
  delete this->computerVision;
  delete this->faceAnalyzer;
  delete this->raspiCam;


  //Delete mapping thread.
  delete this->mappingThread;

  //Delete mapper.
  delete this->mappingSystem;


  //Delete drive system.
  delete this->driveSystem;


  //Delete pwm thread.
  delete this->pwmThread;

}

void Robot::DriveForwards()
{
  this->driveSystem->DriveForwards();
}

void Robot::DriveBackwards()
{
  this->driveSystem->DriveBackwards();
}

void Robot::RotateLeft()
{
  this->driveSystem->RotateLeft();
}

void Robot::RotateRight()
{
  this->driveSystem->RotateRight();
}

void Robot::StopMovement()
{
  this->driveSystem->StopMovement();
}