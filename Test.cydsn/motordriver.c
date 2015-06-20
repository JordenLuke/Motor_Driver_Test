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
#include"motordriver.h"
#include"project.h"

void setSpeed(uint16 speed, uint8_t motorID)
{
    if(motorID == MOTOR_A)
    {
        EN_A_PWM_WriteCompare(speed);
    } 
    else
    {
        EN_B_PWM_WriteCompare(speed);
    }
}
void setDirection(uint8_t direction, uint8_t motorID)
{
    uint8_t temp;
    
    if(motorID == MOTOR_A)
    {
        temp = Motor_A_Read();
        temp = temp & 0x1;
        temp = temp | direction;
        Motor_A_Write(temp);
    }
    else
    {
        temp = Motor_B_Read();
        temp = temp & 0x1;
        temp = temp | direction;
        Motor_B_Write(temp);    
    }
}
void rotateMotor(uint8_t direction, uint8_t motorID)
{
    uint8_t temp = 0x1;
    if(motorID == MOTOR_A)
    {
        
        temp = temp | direction;
        Motor_A_Write(temp);        
    }
    else
    {
        
        temp = temp | direction;
        Motor_B_Write(temp);
    }
}
void goForward()
{
     rotateMotor(ANTICLOCKWISE,MOTOR_A);
     rotateMotor(ANTICLOCKWISE,MOTOR_B);  
}
void goBackward()
{
     rotateMotor(CLOCKWISE,MOTOR_A);
     rotateMotor(CLOCKWISE,MOTOR_B); 
}
void goLeft()
{
    rotateMotor(CLOCKWISE,MOTOR_A);
    rotateMotor(ANTICLOCKWISE, MOTOR_B);
}
void goRight()
{
    rotateMotor(CLOCKWISE,MOTOR_B);
    rotateMotor(ANTICLOCKWISE, MOTOR_A);
}
void stop_all()
{
    Motor_A_Write(0);
    Motor_B_Write(0);
}
void stop(uint8_t motorID)
{
    if(motorID == MOTOR_A)
    {
        Motor_A_Write(0);
    }
    else
    {
        Motor_B_Write(0);   
    }
}

/* [] END OF FILE */
