/******************************************************************************

 @file  sensortag_hum.h

 @brief This file contains the Sensor Tag sample application,
        Humidity part, for use with the TI Bluetooth Low
        Energy Protocol Stack.

 Group: WCS, BTS
 Target Device: CC2650, CC2640, CC1350

 ******************************************************************************
 
 Copyright (c) 2015-2016, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: ble_sdk_2_02_01_18
 Release Date: 2016-10-26 15:20:04
 *****************************************************************************/

#ifndef SENSORTAGHUM_H
#define SENSORTAGHUM_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "sensortag.h"

/*********************************************************************
 * CONSTANTS
 */
static int termtable[31][21] = {{16, 16, 17, 17, 17, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 21, 21, 21, 21, 21, 21 },
                               {18, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 22, 22 ,22 ,22, 22, 23 },
                               {19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23 ,23 ,23, 23, 24 },
                               {20, 20, 20, 20, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24 ,24 ,24, 25, 25 },
                               {21, 21, 22, 22, 22, 22, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25 ,26 ,26, 26, 26 },
                               {22, 23, 23, 23, 24, 24, 24, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27 ,27 ,28, 28 },
                               {24, 24, 24, 24, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 29 ,29 ,29, 30 },
                               {25, 25, 25, 25, 26, 26, 26, 27, 27, 27, 27, 28, 28, 29, 29, 30, 30, 31 ,31 ,31, 33 },
                               {26, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 31, 32, 32, 33 ,34 ,34, 36 },
                               {26, 26, 27, 27, 27, 28, 29, 29, 29, 29, 30, 30, 31, 33, 33, 34, 35, 35 ,37 ,38, 40 },
                               {27, 27, 28, 28, 28, 28, 29, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 39 ,40 ,41, 45 },
                               {28, 28, 29, 29, 29, 29, 30, 31, 31, 31, 33, 34, 35, 36, 37, 39, 40, 41 ,45 ,45, 50 },
                               {29, 29, 29, 29, 30, 31, 31, 33, 33, 34, 35, 35, 37, 39, 40, 42, 44, 45 ,51 ,51, 55 },
                               {29, 29, 30, 30, 31, 33, 33, 34, 34, 35, 36, 38, 39, 42, 43, 45, 49, 49 ,53 ,54, 55 },
                               {30, 30, 31, 31, 32, 34, 34, 35, 36, 37, 38, 41, 42, 44, 47, 48, 50, 52 ,55 ,-1 ,-1 },
                               {31, 32, 32, 32, 33, 35, 35, 37, 37, 40, 40, 44, 45, 47, 51, 52, 55 ,-1 ,-1 ,-1 ,-1 },
                               {32, 33, 33, 34, 35, 36, 37, 39, 39, 42, 43, 46, 49, 50, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {32, 33, 34, 35, 36, 38, 38, 41, 41, 44, 46, 49, 51, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {33, 34, 35, 36, 37, 39, 40, 43, 44, 47, 49, 51, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {34, 35, 36, 37, 38, 41, 41, 44, 46, 50, 50, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {35, 36, 37, 39, 40, 43, 43, 47, 49, 53, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {35, 36, 38, 40, 41, 44, 45, 49, 50, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {36, 37, 39, 41, 42, 45, 47, 50, 52, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {37, 38, 40, 42, 44, 47, 49, 53 ,55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {38, 39, 41, 44, 45, 49, 52, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {38, 40, 42, 45, 47, 50, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {39, 41, 43, 45, 49, 51, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {40, 42, 44, 47, 51, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {41, 43, 45, 49, 53, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {42, 45, 47, 50, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                               {42, 45, 48, 50, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 }
                               };

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */
#ifndef EXCLUDE_HUM

/*
 * Create the Humidity sensor task
 */
extern void SensorTagHum_createTask(void);

/*
 * Initialize Humidity sensor module
 */
extern void SensorTagHum_init(void);

/*
 * Task Event Processor for characteristic changes
 */
extern void SensorTagHum_processCharChangeEvt(uint8_t paramID);


/*
 * Reset Humidity sensor module
 */
extern void SensorTagHum_reset(void);

#else

/* Humidity module not included */

#define SensorTagHum_createTask()
#define SensorTagHum_init()
#define SensorTagHum_processCharChangeEvt(paramID)
#define SensorTagHum_reset()

#endif // EXCLUDE_TMP

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SENSORTAGHUM_H */
