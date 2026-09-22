#include <stdio.h>
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"


#define RED GPIO_NUM_6
#define GREEN GPIO_NUM_7
#define BLUE GPIO_NUM_8

#define SPEED LEDC_LOW_SPEED_MODE
#define TIMER LEDC_TIMER_0
#define CHANNEL0 LEDC_CHANNEL_0
#define CHANNEL1 LEDC_CHANNEL_1
#define CHANNEL2 LEDC_CHANNEL_2


ledc_timer_config_t my_timer = {
    .speed_mode = SPEED,
    .timer_num = LEDC_TIMER_0,
    .clk_cfg = LEDC_AUTO_CLK,
    .freq_hz = 2000,
    .duty_resolution = LEDC_TIMER_8_BIT
};

ledc_channel_config_t RED_CONF = {
    .gpio_num = RED,
    .duty = 128,
    .speed_mode = SPEED,
    .timer_sel = LEDC_TIMER_0,
    .channel = LEDC_CHANNEL_0,
    .intr_type = LEDC_INTR_DISABLE,
    .hpoint = 0

};
ledc_channel_config_t BLUE_CONF = {
    .gpio_num = BLUE,
    .duty = 128,
    .speed_mode = SPEED,
    .timer_sel = LEDC_TIMER_0,
    .channel = LEDC_CHANNEL_1,
    .intr_type = LEDC_INTR_DISABLE,
    .hpoint = 0

};
ledc_channel_config_t GREEN_CONF = {
    .gpio_num = GREEN,
    .duty = 128,
    .speed_mode = SPEED,
    .timer_sel = LEDC_TIMER_0,
    .channel = LEDC_CHANNEL_2,
    .intr_type = LEDC_INTR_DISABLE,
    .hpoint = 0

};

void rgb_light(uint32_t red, uint32_t blue, uint32_t green){
    ledc_set_duty(
        SPEED, CHANNEL0, red
    );
    ledc_update_duty(
        SPEED, CHANNEL0
    );

    ledc_set_duty(
        SPEED, CHANNEL1, blue
    );
    ledc_update_duty(
        SPEED, CHANNEL1
    );

    ledc_set_duty(
        SPEED, CHANNEL2, green
    );
    ledc_update_duty(
        SPEED, CHANNEL2
    );
}

void app_main(void)
{
    ledc_timer_config(&my_timer);
    ledc_channel_config(&RED_CONF);
    ledc_channel_config(&BLUE_CONF);
    ledc_channel_config(&GREEN_CONF);


    while(1){
         //RED
    rgb_light(255,0,0);
    vTaskDelay(pdMS_TO_TICKS(1000));

    //BLUE
    rgb_light(0,0,255);
     vTaskDelay(pdMS_TO_TICKS(1000));

    //GREEN
    rgb_light(255,255,0);
     vTaskDelay(pdMS_TO_TICKS(1000));

     rgb_light(100,255,34);
     vTaskDelay(pdMS_TO_TICKS(1000));

     rgb_light(50,255,255);
     vTaskDelay(pdMS_TO_TICKS(1000));

     rgb_light(21,120,10);
     vTaskDelay(pdMS_TO_TICKS(1000));

     rgb_light(0,255,0);
     vTaskDelay(pdMS_TO_TICKS(1000));
    }
   

}