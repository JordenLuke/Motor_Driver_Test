/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__
	
#include"project.h"
#define CLOCKWISE 0x02
#define ANTICLOCKWISE 0x4
#define STOP 0x7
#define MOTOR_A 0x00
#define MOTOR_B 0x01

struct MotorStruct
{
	uint16 speed;
	uint8 direction;  
	uint8 motor_id;
};
void setSpeed(uint16 speed, uint8_t motorID);
void setDirection(uint8_t direction, uint8_t motorID);
void rotate(uint8_t direction, uint8_t motor_position);
void rotateWithID(uint8_t direction, uint8_t motorID);
void goForward();
void goBackward();
void goLeft();
void goRight();
void stop_all();
void stop(uint8_t motorID);
#endif
/* [] END OF FILE */
