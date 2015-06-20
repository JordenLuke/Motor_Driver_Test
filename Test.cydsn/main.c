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
#include <project.h>
#include "motordriver.h"

void init();
int main()
{
   CyGlobalIntEnable; /* Enable global interrupts. */
init();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
        setSpeed(30000,MOTOR_A);
        setSpeed(30000,MOTOR_B);
    for(;;)
    {
       
        goForward();
        CyDelay(2000);
        stop_all();
        CyDelay(2000);
        goBackward();
        CyDelay(2000);
        stop_all();
        CyDelay(2000);
        goLeft();
        CyDelay(2000);
        stop_all();
        CyDelay(2000);
        goRight();
        CyDelay(2000);
        stop_all();
        CyDelay(2000);
    }
}
void init()
{
    EN_B_PWM_Start();
    EN_A_PWM_Start();
}
/* [] END OF FILE */
