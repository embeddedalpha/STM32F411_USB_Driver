/*
 * USB_Device_Framework.c
 *
 *  Created on: Aug 7, 2022
 *      Author: Kunal
 */


#include "USB_Device_Framework.h"




void USB_Device_Mode_Init(void)
{
	USB_Device_Pins_Init();
#if USB_DEVICE_FRAMEWORK_H_
	Print_Log("USB Pins initialization done \r\n");
#endif

	USB_Device_Core_Init();
#if USB_DEVICE_FRAMEWORK_H_
	Print_Log("USB Core initialization done \r\n");
#endif

	USB_Device_Connect();
#if USB_DEVICE_FRAMEWORK_H_
	Print_Log("USB Connect initialized \r\n");
#endif
}
