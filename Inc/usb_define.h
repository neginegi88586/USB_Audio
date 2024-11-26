/*
 * usb_define.h
 *
 *  Created on: Nov 23, 2024
 *      Author: idune
 */

#include "stm32f723xx.h"

#ifndef INC_USB_DEFINE_H_
#define INC_USB_DEFINE_H_

#define USB_VERSION				0x0200
#define VENDER					0x9999
#define PRODUCT					0x9999
#define MANUFACT_INDEX			1U
#define PRODUCT_INDEX			2U
#define SERIAL_NUM_INDEX		3U

#define LANG_JP					0x0411

#define DEVICE_CLASS			0xef
#define DEVICE_SUB_CLASS		0x02

#define MAX_PACKET_SIZE0		64U
#define NUM_CONFIG				4U

#define NUM_INTERFACE			4
#define CONFIG_VALUE			5U
#define ATTRIBUTES				0x80
#define MAX_POWER				0xfa

#define FUNC_CLASS				0x01
#define FUNC_SUB_CLASS			0x00
#define FUNC_PROTCOL			0x20
#define FUNC_INDEX				6U

#define NUM_CHANNEL				4U
#define CHANNEL_CONFIG			0x0003
#define CHANNEL_NAME			7U

#define ADC_VERSION				0x0200
#define CATEGRY					0x0a
#define INTERFACE_INDEX			8U


#define MIN(x, y)				(x < y ? x : y)
#define PMA_SIZE				1024

typedef struct
{
	uint16_t addr_tx;
	uint16_t count_tx;
	uint16_t addr_rx;
	uint16_t count_rx;
}Packet_Buffer;

typedef struct
{
	uint16_t Setup_Packet;
	uint16_t Device_Desc;
}PMA_Offset;

typedef struct
{
	PMA_Offset Offset;
	uint16_t Sp;
}PMA_Info;

typedef struct
{
	uint16_t ptr;
	uint16_t len;
}Next_Xfer_Info;


typedef enum
{
	Device_Desc = 1,
	Config_Desc,
	String_Desc,
	Interface_Desc,
	Endpoint_Desc,
	Dev_Qualifier_Desc,
	Other_Speed_Desc,
	Interface_PWR_Desc,
	OTG_Desc,
	Debug_Desc,
	IA_Desc
}Descriptor_Type;

typedef enum
{
	GET_STATUS = 0,
	CLEAR_FEATURE,
	SET_FEATURE,
	SET_ADDRESS,
	GET_DESCRIPTOR,
	SET_DESCRIPTOR,
	GET_CONFIG,
	SET_CONFIG,
	GET_INTERFACE,
	SET_INTERFACE,
	SYNCH_FRAME
}USB_Setup_PacketRequest;

typedef enum
{
	ST_Reset = 0,
	Setup,
	In,
	Out,
	Status_In,
	Status_Out,
	St_Error
}EP0_FSM;

#endif /* INC_USB_DEFINE_H_ */
