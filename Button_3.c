#include <AT89X52.h>

#define LED_PORT						P1
#define BUTTON						    P3_2

#define LED_OFF_ALL						0xFF

#define BTN_IS_PRESSED                  0
#define BTN_SHORT_PRESS                 1
#define BTN_LONG_PRESS                  2
#define BTN_NO_PRESS                    3

void Timer0_Init(void);
void StartTimer0(void);
void StopTimer0(void);
void EnableInterrupt(void);
unsigned char GetBtnPressType(void);


volatile unsigned long u32Timer10msCnt = 0;


void main(void)
{
    unsigned char u8GetBtnPressType = 0;
    
	/** Default LED is turn off */
    LED_PORT = LED_OFF_ALL;
    
    Timer0_Init();
    EnableInterrupt();
    
	while(1)
	{
       /** get button press type */
       u8GetBtnPressType = GetBtnPressType();
       if(BTN_SHORT_PRESS == u8GetBtnPressType)
       {
           LED_PORT ^= 0x1;
       } else if(BTN_LONG_PRESS == u8GetBtnPressType)
       {
           LED_PORT ^= 0xFF;
       }
	}
}


/** Function get type of press button: short press or long press.
    Return short press if timer for press button is lower 2s
    Return long press if timer for press button is greater or equal 3s
 */
unsigned char GetBtnPressType(void)
{
    unsigned char u8BtnPressType = BTN_NO_PRESS;
    
    /** If button is pressed, then clear timer valueand start timer 0*/
    if(BUTTON == BTN_IS_PRESSED)
    {
        u32Timer10msCnt = 0;
        StartTimer0();
        /** Wait button is released, the stop timer and  check timer value */
        while(BUTTON == BTN_IS_PRESSED);
        StopTimer0();
        if(u32Timer10msCnt > 0)
        {
            if(u32Timer10msCnt < 100)   //100= 1000ms/10ms
            {
                u8BtnPressType = BTN_SHORT_PRESS;
            } else if(u32Timer10msCnt >= 200) //200= 2000ms/10ms
            {
                u8BtnPressType = BTN_LONG_PRESS;
            }
        }

    }
    
    return u8BtnPressType;
}

/** Timer0 used to create period interrupt each 10ms.
 */
void Timer0_Init(void)
{
    TMOD = 0x01;       // Timer0 mode 1 
    TH0  = 0XD8;       // 10ms = 10000us => 65536-10000=55536 (D8F0)
    TL0  = 0XF0;
    TF0  = 0;
    TR0  = 0;          // stop Timer 0
}

/** Start Timer 0.
 */
void StartTimer0(void)
{
    TR0=1;
}

/** Stop Timer 0.
 */
void StopTimer0(void)
{
    TR0=0;
}

void EnableInterrupt(void)
{
    ET0=1;  /* Enable Timer0 interrupt */
    EA=1;   /* Enable global interrupt */
}

/** Timer0 interrupt handler */
void Timer0Isr (void) interrupt 1
{
    /** Stop Timer 0. */
    TR0=0;
    /** Reload timer0 register value */
    TH0  = 0XD8;       // 10ms = 10000us => 65536-10000=55536 (D8F0)
    TL0  = 0XF0;
    /** Increment u32Timer10msCnt value*/
    u32Timer10msCnt++;
    /** Start Timer 0. */
    TR0=1;
}







