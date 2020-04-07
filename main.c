
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);
}

static void LED1_Task(void *pvParameters)
{
    bool LedState = true; //intially red ledstate set to 'ON' at the begining of cycle
    while (1)
    {

        LedState = (bool)!LedState;  //
        Board_LED_Set(0, LedState);   // the led is on for 1 second
        vTaskDelay(configTICK_RATE_HZ);

        LedState = (bool)!LedState;     // sfter complete of set delay time the bool state changes to false
        Board_LED_Set(0, LedState);     // the led state is 'OFF' here for other 3.5 seconds.
        vTaskDelay(3.5*configTICK_RATE_HZ);
        LedState = true; // after completing the one cycle the led is set to turn on for loop
    }
}

///*This is the thread for LED 2*/
static void LED2_Task(void *pvParameters)
{
    bool LedState = false; // the state is set to false intially
    while(1)
    {
         LedState = (bool)!LedState;
        Board_LED_Set(1, LedState); // led is 'OFF' for 1.5 seconds
        vTaskDelay(1.5*configTICK_RATE_HZ);

        LedState = (bool)!LedState;   // led is set to 'On' for 1 seconds
        Board_LED_Set(1,  LedState);  // true
        vTaskDelay(configTICK_RATE_HZ);

       LedState = (bool)!LedState;
        Board_LED_Set(1, LedState);   // led state is false here for next 2 seconds
        vTaskDelay(2*configTICK_RATE_HZ);
        LedState = false;
    }
}
//
///*This is the thread for LED 2*/
static void LED3_Task(void *pvParameters)
{
   bool LedState = false;
    while(1)
    {
         LedState = (bool)!LedState;
        Board_LED_Set(2,LedState);    // false for 2 seconds.
        vTaskDelay(2*configTICK_RATE_HZ);

        LedState = (bool)!LedState;
        Board_LED_Set(2, LedState);  // true for 1 second.
        vTaskDelay(configTICK_RATE_HZ);

        LedState = (bool)!LedState;
        Board_LED_Set(2,LedState);  //false foe other 2 seconds
        vTaskDelay(2*configTICK_RATE_HZ);
        LedState = false;
    }
}
int main(void)
{
	prvSetupHardware();

    xTaskCreate(LED1_Task, (signed char *) "LED1_Task",
                    configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
                    (xTaskHandle *) NULL);

    xTaskCreate(LED2_Task,(signed char *) "LED2_Task",
                    configMINIMAL_STACK_SIZE,NULL,(tskIDLE_PRIORITY + 2UL),
                    (xTaskHandle *)NULL);

    xTaskCreate(LED3_Task,(signed char *) "LED3_Task",
                    configMINIMAL_STACK_SIZE,NULL,(tskIDLE_PRIORITY + 1UL),
                    (xTaskHandle * )NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
