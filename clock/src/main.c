#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#define CLOCK GPIO_NUM_15
#define LATCH GPIO_NUM_16
#define DATA_ GPIO_NUM_19

#define DIGIT1 GPIO_NUM_17
#define DIGIT2 GPIO_NUM_18
#define DIGIT3 GPIO_NUM_11
#define DIGIT4 GPIO_NUM_12

#define PIN_MASK                                                               \
  ((1UL << CLOCK) | (1UL << LATCH) | (1UL << DATA_) | (1UL << DIGIT1) |        \
   (1UL << DIGIT2) | (1UL << DIGIT3) | (1UL << DIGIT4))

   const uint8_t digitTable[] = {
      0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
      0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111,
  };

int total_seconds = 0;
int current_digit[4] = {};

TimerHandle_t clock_timer;





void select_write(uint8_t data,int digit) {

   gpio_set_level(LATCH, 0);

  for (int i = 7; i >= 0; i--) {
    /** This gave me hard time to figure out
     * initially had the loop from 0 to 7 and
     * the seven segment display would display
     * garbage numbers. After some research, i realized
     * that the issue is with how the shift register
     * handles the serial data  sent in. The register always shifts the bit
     * order of the data. sending the bit pattern into the shift register in LSB
     * would make the register push it out in MSB. looping from 0 to 7 is
     * sending the data in LSB and hence register pushes it out in MSB order
     * which breaks the order because we still need it in LSB when it comes out.
     * So we send it in MSB order such that even when the register shifts the
     * bit order , the order in which we want it to move out is maintained.
     * Thank God i put this comment here for my future me not to wonder why
     */
    gpio_set_level(CLOCK, 0);
    gpio_set_level(DATA_, (data >> i) & 1);
    gpio_set_level(CLOCK, 1);
  }

  gpio_set_level(LATCH, 1);

  switch (digit) {
  case 0:
    gpio_set_level(DIGIT1, 0);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    gpio_set_level(DIGIT1, 1);
    break;

  case 1:
    gpio_set_level(DIGIT2, 0);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    gpio_set_level(DIGIT2, 1);
    break;
  case 2:
    gpio_set_level(DIGIT3, 0);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    gpio_set_level(DIGIT3, 1);
    break;

  case 3:
    gpio_set_level(DIGIT4, 0);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    gpio_set_level(DIGIT4, 1);
    break;
  default:
    break;
  }
}

void vUpdateDigit(TimerHandle_t clock_timer) {
  total_seconds++;
  current_digit[0] = (total_seconds/600)%6;
  current_digit[1] = (total_seconds/60)%10;
  current_digit[2] = (total_seconds/10)%6;
  current_digit[3] = (total_seconds/1)%10;
}

void vTaskRefresh(void * param){
  while(1){
  for (int i = 0; i < 4 ; i++){
   select_write(digitTable[current_digit[i]],i);
  }
}
}

void app_main() {

  

  gpio_config_t pin_config = {.mode = GPIO_MODE_DEF_OUTPUT,
                              .pin_bit_mask = PIN_MASK,
                              .pull_down_en = GPIO_PULLDOWN_DISABLE,
                              .pull_up_en = GPIO_PULLUP_DISABLE,
                              .intr_type = GPIO_INTR_DISABLE};

  gpio_config(&pin_config);
  gpio_set_level(DATA_, 0);

  gpio_set_level(DIGIT1, 1);
  gpio_set_level(DIGIT2, 1);
  gpio_set_level(DIGIT3, 1);
  gpio_set_level(DIGIT4, 1);

  clock_timer = xTimerCreate("clock timer", pdMS_TO_TICKS(1000), pdTRUE,
                             (void *)0, vUpdateDigit);
  

  
      xTimerStart(clock_timer,pdMS_TO_TICKS(1000));
      xTaskCreate(vTaskRefresh,"Refresh",5012,NULL,1,NULL);


  
}
