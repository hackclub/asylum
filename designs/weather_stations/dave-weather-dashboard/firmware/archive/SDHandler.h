#idndef SDHANDLER_H
#define SDHANDLER_H

#include <Arduino.h>
#include <SD.h>
#include <FS.h>
#include "config.h"

if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    return;
}



#endif