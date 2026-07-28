/**
 * @file    main.c
 * @brief   FreeRTOS demo for STM32
 *
 * Tasks:
 *  - LedTask       : Toggles LED every 500 ms
 *  - PrintTask     : Receives strings from queue and prints them
 *  - Soft Timer    : Periodically sends a message to the queue
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Simple LED macros - replace with real GPIO for your board */
#define LED_ON()     /* GPIOx->BSRR = PIN */
#define LED_OFF()    /* GPIOx->BRR  = PIN */
#define LED_TOGGLE() /* GPIOx->ODR ^= PIN */

/* Queue handle */
static QueueHandle_t printQueue = NULL;

/* Task prototypes */
void LedTask(void *pvParameters);
void PrintTask(void *pvParameters);

/* Software timer callback */
void vTimerCallback(TimerHandle_t xTimer);

int main(void)
{
    /* Hardware init (clock, GPIO, UART...) would go here */

    /* Create queue (holds pointers to strings) */
    printQueue = xQueueCreate(5, sizeof(char *));

    if (printQueue == NULL) {
        /* Error handling */
        while (1);
    }

    /* Create tasks */
    xTaskCreate(LedTask, "LED", 128, NULL, 1, NULL);
    xTaskCreate(PrintTask, "Print", 256, NULL, 2, NULL);

    /* Create software timer (period 2000 ms, auto-reload) */
    TimerHandle_t xTimer = xTimerCreate(
        "MsgTimer",
        pdMS_TO_TICKS(2000),
        pdTRUE,
        NULL,
        vTimerCallback
    );

    if (xTimer != NULL) {
        xTimerStart(xTimer, 0);
    }

    /* Start the scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    while (1);
}

/*-------------------- Tasks --------------------*/

void LedTask(void *pvParameters)
{
    (void)pvParameters;

    for (;;) {
        LED_TOGGLE();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void PrintTask(void *pvParameters)
{
    (void)pvParameters;
    char *msg;

    for (;;) {
        if (xQueueReceive(printQueue, &msg, portMAX_DELAY) == pdTRUE) {
            /* In real project: send to UART */
            /* printf("%s\r\n", msg); */
            (void)msg;
        }
    }
}

/*-------------------- Timer Callback --------------------*/

void vTimerCallback(TimerHandle_t xTimer)
{
    (void)xTimer;
    static const char *message = "Hello from FreeRTOS Timer";

    /* Send pointer to the string to the queue */
    xQueueSend(printQueue, &message, 0);
}

/*-------------------- FreeRTOS Hooks --------------------*/

void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS();
    for (;;);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    taskDISABLE_INTERRUPTS();
    for (;;);
}
