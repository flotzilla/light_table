#include <Arduino.h>
#include "AnalogButtonHandler.h"

using namespace std;

AnalogButtonHandler::AnalogButtonHandler(int pin, int delay, void (*OnActionCallBack)(), void (*OffActionCallBack)()) : ButtonHandler(pin, delay, *OnActionCallBack, *OffActionCallBack)
{
    buttonPin = pin;
    delayVal = delay;

    OnAction = OnActionCallBack;
    OffAction = OffActionCallBack;
}

void AnalogButtonHandler::Update(unsigned long currentMills)
{
    if ((currentMills - lastUpdateTime) > delayVal)
    {
        lastUpdateTime = currentMills;

        int reading = analogRead(buttonPin);

        buttonState = reading;

        OnAction();
        // OffAction();
    }
}