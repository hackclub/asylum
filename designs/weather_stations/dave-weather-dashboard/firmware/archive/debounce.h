#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <Arduino.h>
#include <Bounce2.h>
#include "config.h"

Bounce bounce = Bounce();

void bouncesetup()
{
    bounce.attach(REFRESH_BUTTON, INPUT);
    bounce.interval(BOUNCE_INTERVAL);
}

void bounceloop()
{
    bounce.update();
    if (bounce.changed())
    {
        int debouncedInput = bounce.read();
        if (debouncedInput == LOW)
        {
            Serial.println("Button pressed!");
        }
    }
}

#endif