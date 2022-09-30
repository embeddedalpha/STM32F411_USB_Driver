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

static void USB_Device_Configure_Endpoint0(uint8_t endpoint_size)
{
	USB_OTG_FS_DEVICE -> DAINTMSK |= (1 << 0) | (1 << 16);
	USB_OTG_FS_INEndpoint0 -> DIEPCTL &= ~0xFFFFFFFF;
	USB_OTG_FS_INEndpoint0 -> DIEPCTL |= _VAL2FLD(USB_OTG_DIEPCTL_MPSIZ,endpoint_size) << 0;
	USB_OTG_FS_INEndpoint0 -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK;
	USB_OTG_FS_OUTEndpoint0 -> DOEPCTL &= ~0xFFFFFFFF;
	USB_OTG_FS_OUTEndpoint0 -> DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;
}

static void USB_Device_Configure_IN_Endpoints(uint8_t endpoint_number, USB_Endpoints_Type endpoint_type, uint16_t endpoint_size)
{
	//Unmask all the interrupts of the endpoints we are working with:
	USB_OTG_FS_DEVICE -> DAINTMSK |= (1 << 16);
	USB_OTG_FS_INEndpoint0 -> DIEPCTL |= _VAL2FLD(USB_OTG_DIEPCTL_MPSIZ,endpoint_size) << 0;
	USB_OTG_FS_INEndpoint0 -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK | USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
	USB_OTG_FS_INEndpoint0 -> DIEPCTL |= _VAL2FLD(USB_OTG_DIEPCTL_EPTYP,endpoint_type);
}


static void USB_Device_Deconofigure_Endpoints(USB_OTG_INEndpointTypeDef *INendpoint,USB_OTG_OUTEndpointTypeDef *OUTendpoint,uint8_t endpoint_number)
{
	//Mask all interrupts for particular endpoint
	USB_OTG_FS_DEVICE -> DAINTMSK &= ~((1 << endpoint_number) | (1 << (16+endpoint_number)));

	//Clear all interrupts
	INendpoint -> DIEPINT = 0x28FB;
	OUTendpoint -> DOEPINT = 0x313B;

	//Disable endpoints
	if(INendpoint -> DIEPCTL & USB_OTG_DIEPCTL_EPENA)
	{
		INendpoint -> DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
	}
	//Deactivate endpoint
	INendpoint -> DIEPCTL &= ~USB_OTG_DIEPCTL_USBAEP;

	if(endpoint_number != 0)
	{
		if(OUTendpoint -> DIEPCTL & USB_OTG_DIEPCTL_EPENA)
		{
			OUTendpoint -> DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
		}
		//Deactivate endpoint
		OUTendpoint -> DIEPCTL &= ~USB_OTG_DIEPCTL_USBAEP;
	}

}


static void USB_Configure_RX_FIFO(uint16_t size)
{
	uint16_t temp;

	temp = 10 + (2 * ((size / 4) + 1));

	USB_OTG_FS_GLOBAL->GRXFSIZ = temp;
}

static void USB_Configure_TX_FIFO(uint8_t endpoint_number, uint16_t size )
{
	uint16_t temp = (size + 3)/4;

	if(endpoint_number == 0)
	{
		USB_OTG_FS_GLOBAL -> DIEPTXF0_HNPTXFSIZ = temp << 16;
	}
	else
	{
		USB_OTG_FS_GLOBAL -> DIEPTXF[endpoint_number -1] |= size << 16;
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
