#include <AT89X52.h>

#define LED1							P1_0
#define BUTTON						    P3_2

#define LED_ON						    0
#define LED_OFF						    1

#define BTN_IS_PRESSED		            0


void main(void)
{
	/** Default LED1 is turn off */
    LED1 = LED_OFF;
	while(1)
	{
        /** Check if button is pressed, then turn on LED1, On the contrary, turn off LED1 */
        if(BUTTON == BTN_IS_PRESSED)
		{
			LED1 = 	LED_ON;
		}
        else
        {
            LED1 = LED_OFF;
        }
	}
}















