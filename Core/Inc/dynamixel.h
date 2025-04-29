/*
 * dynamixel.h
 *
 *  Created on: Apr 29, 2025
 *      Author: james
 */

#ifndef INC_DYNAMIXEL_H_
#define INC_DYNAMIXEL_H_

#include "main.h"
#include <stdint.h>
#include <string.h>

//----------- 상수 정의 -----------
// 다이나믹셀 레지스터 주소
#define DXL_ADDR_OPERATING_MODE    0x0B
#define DXL_ADDR_TORQUE_ENABLE     0x40
#define DXL_ADDR_LED               0x41
#define DXL_ADDR_GOAL_POSITION     0x74

// 다이나믹셀 명령어
#define DXL_INST_PING          0x01
#define DXL_INST_READ          0x02
#define DXL_INST_WRITE         0x03
#define DXL_INST_REG_WRITE     0x04
#define DXL_INST_ACTION        0x05
#define DXL_INST_RESET         0x06
#define DXL_INST_REBOOT        0x08
#define DXL_INST_STATUS        0x55
#define DXL_INST_SYNC_READ     0x82
#define DXL_INST_SYNC_WRITE    0x83
#define DXL_INST_BULK_READ     0x92
#define DXL_INST_BULK_WRITE    0x93

//----------- 패킷 구조체 정의 -----------
typedef struct {
    uint8_t header[3];
    uint8_t reserved;
    uint8_t id;
    uint8_t lengthL;
    uint8_t lengthH;
    uint8_t instruction;
    uint8_t parameters[255];
    uint16_t crc;
} DynamixelTxPacket;

//----------- 함수 선언 -----------

// 패킷 관련 함수
unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);
void initDynamixelTxPacket(DynamixelTxPacket *packet, uint8_t id, uint8_t instruction, uint8_t *params, uint16_t param_len);
void sendDynamixelPacket(UART_HandleTypeDef *huart, DynamixelTxPacket *packet, uint16_t param_len);
void sendDynamixel(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t instruction, uint8_t *params, uint16_t param_len);
void write_instruction(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t RAM_ADD, int32_t value, uint8_t param_len);

// 제어 함수
void controlDynamixelLED(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t on_off);
void Torque_on(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t value);
void setOperatingMode(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t mode);
void move_motors(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint32_t angle);

#endif

 /* INC_DYNAMIXEL_H_ */
