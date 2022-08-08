/*
 * USB_Device_Driver.c
 *
 *  Created on: Aug 7, 2022
 *      Author: Kunal
 */


#include "USB_Device_Driver.h"


void USB_Device_Pins_Init(void)
{
	GPIO_Pin_Setup(GPIOA, 11, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 10);
	GPIO_Pin_Setup(GPIOA, 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 10);
}

void USB_Device_Core_Init(void)
{
	RCC -> AHB1ENR |= RCC_AHB2ENR_OTGFSEN;	//enable the clock for USB Core

	USB_Device_FS_GLOBAL -> GUSBCFG |= USB_OTG_GUSBCFG_FDMOD; //force device USB Core in device mode

	USB_Device_FS_GLOBAL -> GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL; //force select internal embedded PHY

	USB_Device_FS_GLOBAL -> GUSBCFG |= USB_OTG_GUSBCFG_TRDT_3 | USB_OTG_GUSBCFG_TRDT_0; //TRDT minimum value = 21.8 to 24 MHz

	USB_Device_FS_DEVICE -> DCFG |= USB_OTG_DCFG_DSPD;	//set USB Core to Full speed

	USB_Device_FS_GLOBAL -> GCCFG |= USB_OTG_GCCFG_VBUSBSEN; //enable VBUS sense

//	Unmask Following Interrupts
//	– USB reset
//	– Enumeration done
//	– Early suspend
//	– USB suspend
//	– SOF

	USB_Device_FS_GLOBAL -> GINTMSK |= USB_OTG_GINTMSK_USBRST | USB_OTG_GINTMSK_ENUMDNEM |
			                           USB_OTG_GINTMSK_ESUSPM | USB_OTG_GINTMSK_USBSUSPM |
									   USB_OTG_GINTMSK_SOFM | USB_OTG_GINTMSK_WUIM | USB_OTG_GINTMSK_IEPINT |
									   USB_OTG_GINTMSK_RXFLVLM;

	USB_Device_FS_GLOBAL -> GINTSTS = 0xFFFFFFFF; //reset all interrupts on startup

	USB_Device_FS_GLOBAL -> GAHBCFG = USB_OTG_GAHBCFG_GINT; //unmask global interrupt

}

void USB_Device_Connect(void)
{
	USB_Device_FS_GLOBAL -> GCCFG |= USB_OTG_GCCFG_PWRDWN; //disable power down of core

	USB_Device_FS_DEVICE -> DCTL &= ~USB_OTG_DCTL_SDIS;	//disable soft disconnect
}

void USB_Device_Disconnect(void)
{
	USB_Device_FS_GLOBAL -> GCCFG &= ~USB_OTG_GCCFG_PWRDWN;	//enable power down of core

	USB_Device_FS_DEVICE -> DCTL |= USB_OTG_DCTL_SDIS; //enable software disconnect
}
