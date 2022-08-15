/*
 * USB_Driver_Common.h
 *
 *  Created on: Aug 14, 2022
 *      Author: Kunal
 */

#ifndef USB_DRIVER_COMMON_H_
#define USB_DRIVER_COMMON_H_

#include "main.h"



#define USB_OTG_FS_GLOBAL     ((USB_OTG_GlobalTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_GLOBAL_BASE))
#define USB_OTG_FS_DEVICE     ((USB_OTG_DeviceTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_DEVICE_BASE))

#define USB_OTG_FS_INEndpoint0 ((USB_OTG_INEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (0x20 * 0)))
#define USB_OTG_FS_INEndpoint1 ((USB_OTG_INEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (0x20 * 1)))
#define USB_OTG_FS_INEndpoint2 ((USB_OTG_INEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (0x20 * 2)))
#define USB_OTG_FS_INEndpoint3 ((USB_OTG_INEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (0x20 * 3)))

#define USB_OTG_FS_OUTEndpoint0 ((USB_OTG_OUTEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (0x20 * 0)))
#define USB_OTG_FS_OUTEndpoint1 ((USB_OTG_OUTEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (0x20 * 1)))
#define USB_OTG_FS_OUTEndpoint2 ((USB_OTG_OUTEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (0x20 * 2)))
#define USB_OTG_FS_OUTEndpoint3 ((USB_OTG_OUTEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (0x20 * 3)))

#define USB_OTG_FS_PCGCCTL ((uint32_t *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))



#endif /* USB_DRIVER_COMMON_H_ */
