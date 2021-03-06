#Project
PROJECT_NAME = DriveModule

#Build
BUILD_DIR = ./build

#Compiler
CXX = g++

#Flags
CFLAGS = 	-Wall -ggdb -O0 -std=c++11 -lwiringPi -lpthread \
					-I/usr/local/include/ -lraspicam -lraspicam_cv -lopencv_core \
					-lopencv_imgcodecs -lopencv_objdetect -lopencv_imgproc

#Sources
SRC_DIR = ./src

SOURCES = $(SRC_DIR)/main.cpp \
					$(SRC_DIR)/InputReader.cpp \
					$(SRC_DIR)/Client.cpp \
					$(SRC_DIR)/Robot.cpp \
					$(SRC_DIR)/Servo.cpp \
					$(SRC_DIR)/Pwm.cpp \
					$(SRC_DIR)/DriveSystem.cpp \
					$(SRC_DIR)/MappingLogic.cpp \
					$(SRC_DIR)/Uart.cpp \
					$(SRC_DIR)/ComputerVision.cpp \
					$(SRC_DIR)/ComputerVisionModule.cpp \
					$(SRC_DIR)/Face.cpp \
					$(SRC_DIR)/FaceAnalyzer.cpp \
					$(SRC_DIR)/RaspiCamera.cpp \
					$(SRC_DIR)/Point.cpp \
					$(SRC_DIR)/Size.cpp 

#Objects
OBJ_DIR = ./obj

OBJECTS = $(subst $(SRC_DIR),$(OBJ_DIR),$(SOURCES:.cpp=.o))

#Phony
.PHONY: all $(PROJECT_NAME)Clean create_dirs

#All
all: $(PROJECT_NAME)

#Build
$(PROJECT_NAME): create_dirs $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(BUILD_DIR)/$@

#Dirs
create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BUILD_DIR)

#Clean
clean: $(PROJECT_NAME)Clean

$(PROJECT_NAME)Clean:
	@rm -f $(OBJECTS)
	@rm -f $(PROJECT_NAME)

#Targets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@