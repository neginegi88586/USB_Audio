/*
 * usb_device.h
 *
 *  Created on: Nov 23, 2024
 *      Author: idune
 */

#ifndef INC_USB_DESC_H_
#define INC_USB_DESC_H_

#include "usb_define.h"

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
}USB_Device_DescTypedef;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumInterface;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	uint8_t bmAttributes;
	uint8_t bMaxPower;
}USB_Cfg_DescTypeDef;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
}USB_STD_AC_Interface_DescTypeDef;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
}USB_STD_AS_Interface_DescTypeDef;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
}USB_STD_ACINT_EP_DescTypeDef;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
}USB_STD_ASISO_EP_DescTypeDef;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bFirstInterface;
	uint8_t bInterfaceCount;
	uint8_t bFunctionClass;
	uint8_t bFunctionSubClass;
	uint8_t bFunctionProtocol;
	uint8_t iFunction;
}USB_IA_DescTypeDef;

typedef struct
{
	USB_Device_DescTypedef device_desc;
	USB_Cfg_DescTypeDef cfg_desc;
	USB_STD_AC_Interface_DescTypeDef std_ac_interface_desc;
	USB_STD_AS_Interface_DescTypeDef std_as_interface_desc[4];
	USB_STD_ACINT_EP_DescTypeDef std_acint_ep_desc;
	USB_STD_ASISO_EP_DescTypeDef std_asiso_ep_desc[4];
	USB_IA_DescTypeDef ia_desc;
}USB_DescTypedef;

#endif /* INC_USB_DESC_H_ */
