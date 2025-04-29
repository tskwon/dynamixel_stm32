/*
 * control.c
 *
 *  Created on: Apr 30, 2025
 *      Author: james
 */

#include "dynamixel.h"

void controlDynamixelLED(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t on_off)
{
    write_instruction(huart, packet, id, DXL_ADDR_LED, on_off, 3);
}

void Torque_on(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t value)
{
    write_instruction(huart, packet, id, DXL_ADDR_TORQUE_ENABLE, value, 3);
}

void setOperatingMode(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint8_t mode)
{
    write_instruction(huart, packet, id, DXL_ADDR_OPERATING_MODE, mode, 3);
}

void move_motors(UART_HandleTypeDef *huart, DynamixelTxPacket packet, uint8_t id, uint32_t angle)
{
    float temp = (angle / 360.0f) * 4095.0f;
    uint32_t value = (uint32_t)(temp);

    if(value < 0) value = 0;
    else if(value >= 4096) value = 4096;

    write_instruction(huart, packet, id, DXL_ADDR_GOAL_POSITION, value, 6);
}
