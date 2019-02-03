#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <fcntl.h>
#include <iostream>
#include <termio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>

#define INPUT_READ_MICROS (10)
#define INPUT_READ_SECS (00)
#define INPUT_READ_TIMEOUT ((struct timeval){.tv_sec = INPUT_READ_SECS, .tv_usec = INPUT_READ_MICROS})

//Declare handler function
typedef void (*void_funct_char_pvoid_t)(char, void*);

class InputReader
{
    public:
        /**
         * @brief Construct a new Input Reader object
         * 
         * @param inputHandler A void function that takes a char as param, to handle the pressed button
         */
        InputReader(void_funct_char_pvoid_t inputHandler, void* args);
        ~InputReader();

        void PollInput();

    private:

        void* Args;
        fd_set descriptor;
        void_funct_char_pvoid_t InputHandler;
        struct termios newSettings;
        struct termios oldSettings;

};

#endif