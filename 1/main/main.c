/**
 * Author: Vibhor Srivastava
 * 
 * Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. 
 * Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t integer_queue;

void task1(void *params)
{
    printf("Created task 1, Periodicity = 1000ms\n");
    while (1)
    {
        printf("task1\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task2(void *params)
{
    printf("Created task 2, Periodicity = 2000ms\n");
    while (1)
    {
        printf("task2\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task3(void *params)
{
    printf("Created task 3, Periodicity = 5000ms\n");
    while (1)
    {
        printf("task3\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task4(void *params)
{
    int message = 0;
    printf("Created task 4, Periodicity = 1000ms\n");
    while (1)
    {
        xQueueSend(integer_queue, &message, 0);
        printf("Sent value \'%d\' from task4\n", message);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        message++;
    }
    vTaskDelete(NULL);
}

void task5(void *params)
{
    int buff;
    printf("Created task 5, Periodicity = 1000\n");
    while (1)
    {
        xQueueReceive(integer_queue, &buff, 0);
        printf("Received \'%d\' in task5\n", buff);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{

    //we create a messge queue for integer type messages before creating the tasks
    integer_queue = xQueueCreate(5, sizeof(int));

    //All tasks have same priority
    xTaskCreate(task1, "task1", 2048, NULL, 2, NULL);
    xTaskCreate(task2, "task2", 2048, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 2048, NULL, 2, NULL);
    xTaskCreate(task4, "task4", 2048, NULL, 2, NULL);
    xTaskCreate(task5, "task5", 2048, NULL, 2, NULL);
    while (1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
