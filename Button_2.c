#include <AT89X52.h>

#define LED_PORT						P1
#define BUTTON						    P3_2

#define LED_OFF_ALL						0xFF

#define BTN_IS_PRESSED		            0

unsigned char BtnIsPressed(void);


void main(void)
{
    unsigned char u8Cnt = 0;
    
	/** Default LED is turn off */
    LED_PORT = LED_OFF_ALL;
	while(1)
	{
        /** If button is pressed, then increment u8Cnt*/
        if(BtnIsPressed() == 1)
        {
            u8Cnt++;
            if(u8Cnt > 8)
            {
                u8Cnt = 0;
            }
        }
        /** Turn on LED */
        LED_PORT = ~((1<<u8Cnt) - 1);
	}
}


/** Function check button is pressed or not.
    Return 0 if buttons is not pressed.
    Return 1 if buttons is pressed.
 */
unsigned char BtnIsPressed(void)
{
    /** variable stores  current button status: is pressed or not */
    unsigned char u8CurrBtnValue = !BTN_IS_PRESSED;
    /** variable stores  previous button status: is pressed or not */
    static unsigned char u8preBtnValue = !BTN_IS_PRESSED;
    unsigned char u8BtnStatus = 0;
    
    /** Read button */
    u8CurrBtnValue = BUTTON;
    if(u8preBtnValue != u8CurrBtnValue)
    {
        if(BTN_IS_PRESSED == u8CurrBtnValue)
        {
            u8BtnStatus = 1;
        }
        u8preBtnValue = u8CurrBtnValue;
    }
    
    return u8BtnStatus;
}











