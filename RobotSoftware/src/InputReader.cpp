#include "InputReader.h"

InputReader::InputReader(void_funct_char_pvoid_t InputHandler, void* args)
    :Args(args), InputHandler(InputHandler)
{
    //Get erminal attributes
    tcgetattr(fileno(stdin), &this->oldSettings);
    //Create a copy
    this->newSettings = this->oldSettings;
    //Set the flags
    this->newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &this->newSettings);
}


InputReader::~InputReader()
{
    //Reset the new settings
    tcsetattr(fileno(stdin), TCSANOW, &this->oldSettings);
}

void InputReader::PollInput()
{
    struct timeval timeOut = INPUT_READ_TIMEOUT;
    FD_ZERO(&this->descriptor);
    FD_SET(fileno(stdin), &this->descriptor);
    int8_t response = select(fileno(stdin) + 1, &this->descriptor, NULL, NULL, &timeOut);

    if (response > 0)
    {
        char pressedChar;
        read(fileno(stdin), &pressedChar, sizeof(pressedChar));
        this->InputHandler(pressedChar, this->Args);
    }
    else if (response == 0)
    {
        
    }
    else 
    {
        std::cout << "Can't select descripter" << std::endl; 
    }
}