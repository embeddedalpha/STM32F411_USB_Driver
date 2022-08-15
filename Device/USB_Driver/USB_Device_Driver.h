/*
 * USB_Device_Driver.h
 *
 *  Created on: Aug 7, 2022
 *      Author: Kunal
 */

#ifndef USB_DEVICE_DRIVER_H_
#define USB_DEVICE_DRIVER_H_


#include "main.h"
#include "GPIO.h"
#include "USB_Driver_Common.h"


void USB_Device_Pins_Init(void);

void USB_Device_Core_Init(void);

void USB_Device_Connect(void);

void USB_Device_Disconnect(void);

#endif /* USB_DEVICE_DRIVER_H_ */
