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

	USB_OTG_FS_GLOBAL -> GUSBCFG |= USB_OTG_GUSBCFG_FDMOD; //force device USB Core in device mode

	USB_OTG_FS_GLOBAL -> GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL; //force select internal embedded PHY

	USB_OTG_FS_GLOBAL -> GUSBCFG |= USB_OTG_GUSBCFG_TRDT_3 | USB_OTG_GUSBCFG_TRDT_0; //TRDT minimum value = 21.8 to 24 MHz

	USB_OTG_FS_DEVICE -> DCFG |= USB_OTG_DCFG_DSPD;	//set USB Core to Full speed

	USB_OTG_FS_GLOBAL -> GCCFG |= USB_OTG_GCCFG_VBUSBSEN; //enable VBUS sense

//	Unmask Following Interrupts
//	– USB reset
//	– Enumeration done
//	– Early suspend
//	– USB suspend
//	– SOF

	USB_OTG_FS_GLOBAL -> GINTMSK |= USB_OTG_GINTMSK_USBRST | USB_OTG_GINTMSK_ENUMDNEM |
			                           USB_OTG_GINTMSK_ESUSPM | USB_OTG_GINTMSK_USBSUSPM |
									   USB_OTG_GINTMSK_SOFM | USB_OTG_GINTMSK_WUIM | USB_OTG_GINTMSK_IEPINT |
									   USB_OTG_GINTMSK_RXFLVLM | USB_OTG_GINTMSK_OEPINT;

	USB_OTG_FS_GLOBAL -> GINTSTS = 0xFFFFFFFF; //reset all interrupts on startup

	USB_OTG_FS_GLOBAL -> GAHBCFG = USB_OTG_GAHBCFG_GINT; //unmask global interrupt

}

void USB_Device_Connect(void)
{
	USB_OTG_FS_GLOBAL -> GCCFG |= USB_OTG_GCCFG_PWRDWN; //disable power down of core

	USB_OTG_FS_DEVICE -> DCTL &= ~USB_OTG_DCTL_SDIS;	//disable soft disconnect
}

void USB_Device_Disconnect(void)
{
	USB_OTG_FS_GLOBAL -> GCCFG &= ~USB_OTG_GCCFG_PWRDWN;	//enable power down of core

	USB_OTG_FS_DEVICE -> DCTL |= USB_OTG_DCTL_SDIS; //enable software disconnect
}

static void USB_Device_Configure_Endpoints(uint8_t endpoint_number, uint8_t endpoint_size)
{
	USB_OTG_FS_DEVICE -> DAINTMSK |= (1 << endpoint_number) | (1 << (16 + endpoint_number));

	switch (endpoint_number) {
		case 0:
		{
			USB_OTG_FS_INEndpoint0 -> DIEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_INEndpoint0 -> DIEPCTL |= endpoint_size << 0;
			USB_OTG_FS_INEndpoint0 -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK;

			USB_OTG_FS_OUTEndpoint0 -> DOEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_OUTEndpoint0 -> DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;
		}
			break;

		case 1:
		{
			USB_OTG_FS_INEndpoint1 -> DIEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_INEndpoint1 -> DIEPCTL |= endpoint_size << 0;
			USB_OTG_FS_INEndpoint1 -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK;

			USB_OTG_FS_OUTEndpoint1 -> DOEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_OUTEndpoint1 -> DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;
		}
			break;
		case 2:
		{
			USB_OTG_FS_INEndpoint2 -> DIEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_INEndpoint2 -> DIEPCTL |= endpoint_size << 0;
			USB_OTG_FS_INEndpoint2 -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK;

			USB_OTG_FS_OUTEndpoint2 -> DOEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_OUTEndpoint2 -> DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;
		}
			break;
		case 3:
		{
			USB_OTG_FS_INEndpoint3 -> DIEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_INEndpoint3 -> DIEPCTL |= endpoint_size << 0;
			USB_OTG_FS_INEndpoint3 -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK;

			USB_OTG_FS_OUTEndpoint3 -> DOEPCTL &= ~0xFFFFFFFF;
			USB_OTG_FS_OUTEndpoint3 -> DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;
		}
			break;
	}
}


void USB_Device_Global_Interrupt_Handler(void)
{
	if((USB_OTG_FS_GLOBAL -> GINTSTS) & USB_OTG_GINTSTS_USBRST)
	{

		//Clear interrupt
		USB_OTG_FS_GLOBAL -> GINTSTS |= USB_OTG_GINTSTS_USBRST;

	} else
		if((USB_OTG_FS_GLOBAL -> GINTSTS) & USB_OTG_GINTSTS_ENUMDNE)
		{
/*
 * Iterate through all endpoints.
 * STM32F411CE has the following EPs:
 *		1. 1 bidirectional control endpoint0
 *		2. 3 IN endpoints
 *		3. 3 OUT endpoints
 */


			//Clear interrupt
			USB_OTG_FS_GLOBAL -> GINTSTS |= USB_OTG_GINTSTS_ENUMDNE;
		} else
			if((USB_OTG_FS_GLOBAL -> GINTSTS) & USB_OTG_GINTSTS_RXFLVL)
			{

				//Clear interrupt
				USB_OTG_FS_GLOBAL -> GINTSTS |= USB_OTG_GINTSTS_RXFLVL;
			}else
				if((USB_OTG_FS_GLOBAL -> GINTSTS) & USB_OTG_GINTSTS_IEPINT)
				{

					//Clear interrupt
					USB_OTG_FS_GLOBAL -> GINTSTS |= USB_OTG_GINTSTS_IEPINT;
				}else
					if((USB_OTG_FS_GLOBAL -> GINTSTS) & USB_OTG_GINTSTS_OEPINT)
					{

						//Clear interrupt
						USB_OTG_FS_GLOBAL -> GINTSTS |= USB_OTG_GINTSTS_OEPINT;
					}
}
