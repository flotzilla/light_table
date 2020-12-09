#ifndef ANALOG_BUTTON_HANDLER_H
#define ANALOG_BUTTON_HANDLER_H

#include "ButtonHandler.h"

class AnalogButtonHandler : public ButtonHandler
{
public:
    unsigned int delayVal = 10;

    AnalogButtonHandler(int pin, int delay, void (*OnActionCallBack)(), void (*OffActionCallBack)());

    void Update(unsigned long currentMills);
};

#endif