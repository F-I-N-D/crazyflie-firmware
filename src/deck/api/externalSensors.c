#include <stdint.h>
#include <stdlib.h>
#include "stm32fxxx.h"

#include "FreeRTOS.h"
#include "timers.h"

#include "deck.h"
#include "param.h"


static bool isInit;
/*variable for storing LDR sensor data*/
static float ldrData;


/* Main initialization */
static void externalSensorsInit()
{
    if(isInit)
        return;

    xTaskCreate(externalSensorsTask, "EXTERNALSENSORS", (2 * configMINIMAL_STACK_SIZE), NULL, 2, NULL);
    isInit = true;

}

void externalSensorsTask(void* arg)
{
    while (1) {
        ldrData = analogReadVoltage(LDRSensor);
    }
}

LOG_GROUP_START(ExternalSensors)
LOG_ADD(LOG_FLOAT, LDR, &ldrData)
LOG_GROUP_STOP(ExternalSensors)
