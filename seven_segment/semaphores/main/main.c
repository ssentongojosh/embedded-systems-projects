#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"

SemaphoreHandle_t mySemaphore;

int num1 = 1;
int num2 = 2;
int num3 = 3;




void taskOne(void * param){
    if (mySemaphore != NULL){
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY)){
            //todo
            ESP_LOGI("taskOne","i have a semaphore, running on core %d",esp_cpu_get_core_id());
            xSemaphoreGive(mySemaphore);
        }
    }
}

void taskTwo(void * param){
    if (mySemaphore != NULL){
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY)){
            //todo
            
            ESP_LOGI("taskTwo","i have a semaphore, running on core %d",esp_cpu_get_core_id());
            xSemaphoreGive(mySemaphore);
        }
    }
}


void taskThree(void * param){
    if (mySemaphore != NULL){
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY)){
            //todo
            
            ESP_LOGI("taskThree","i have a semaphore, running on core %d",esp_cpu_get_core_id());
            xSemaphoreGive(mySemaphore);
        }
    }
}


void taskFour(void * param){
    if (mySemaphore != NULL){
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY)){
            //todo
            
            ESP_LOGI("taskFour","i have a semaphore, running on core %d",esp_cpu_get_core_id());
            xSemaphoreGive(mySemaphore);
        }
    }
}

void taskFive(void * param){
    if (mySemaphore != NULL){
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY)){
            
            ESP_LOGI("taskFive","i have a semaphore, running on core %d",esp_cpu_get_core_id());
            xSemaphoreGive(mySemaphore);
        }
    }
}





void app_main(void)
{
    mySemaphore = xSemaphoreCreateCounting(3,0);

    

}
