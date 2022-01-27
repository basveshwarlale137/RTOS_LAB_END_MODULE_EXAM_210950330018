#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>


TimerHandle_t xHandle_Timer;
//int i =0;
void Task_T1(void *pvParameters)
{
    while(1)
    {
        printf("task_T1 is here\n");
       
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task_T2(void *pvParameters)
{
    while(1)
    {
        printf("task_T2 is here\n");
       
        vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
}

void Task_T3(void *pvParameters)
{
    while(1)
    {
        printf("task_T3 is here to trigger timer\n");
       
       xTimerStart(xHandle_Timer,0);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void Callback_funct(TimerHandle_t xMyTimer)
{
    printf("this is timer _Callback Function\n");

}

void app_main()
{
    BaseType_t xReturned_1;
    
    TaskHandle_t xHandle_Task_1 = NULL;

    xReturned_1 = xTaskCreate(Task_T1,"TaskLogT1",2048,NULL,5,&xHandle_Task_1);
    
    BaseType_t xReturned_2;
    TaskHandle_t xHandle_Task_2 = NULL;
    xReturned_2 = xTaskCreate(Task_T2,"TaskLogT2",2048,NULL,6,&xHandle_Task_2);

    BaseType_t xReturned_3;
    TaskHandle_t xHandle_Task_3 = NULL;
    xReturned_3 = xTaskCreate(Task_T3,"TaskLogT3",2048,NULL,7,&xHandle_Task_3);
     
     xHandle_Timer =  xTimerCreate("timer_callback",pdMS_TO_TICKS(10000),pdFALSE,NULL,Callback_funct);


    
                 

    

    if(xReturned_1 == pdPASS)
    {
        printf("task T1 created\n");
       // vTaskDelete( xHandle_Task_1);
    }

    if(xReturned_2 == pdPASS)
    {
        printf("task T2 created\n");
      //  vTaskDelete( xHandle_Task_2);
    }
    if(xReturned_3 == pdPASS)
    {
        printf("task T3 created\n");
      //  vTaskDelete( xHandle_Task_3);
    }

}
