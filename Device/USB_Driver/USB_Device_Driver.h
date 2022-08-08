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

#define USB_Device_FS_GLOBAL  ((USB_OTG_GlobalTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_GLOBAL_BASE))
#define USB_Device_FS_DEVICE  ((USB_OTG_DeviceTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_DEVICE_BASE))
#define USB_Device_FS_PCGCCTL ((uint32_t *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))



void USB_Device_Pins_Init(void);

void USB_Device_Core_Init(void);

void USB_Device_Connect(void);

void USB_Device_Disconnect(void);

#endif /* USB_DEVICE_DRIVER_H_ */
