#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdbool.h>
#include <math.h>
#include "esp_log.h"

#define CLOCK GPIO_NUM_15
#define LATCH GPIO_NUM_16
#define DATA_ GPIO_NUM_19

#define PIN_MASK ((1UL << CLOCK) | (1UL << LATCH) | (1UL << DATA_))


bool isPrime(int n) {
    if (n < 2)
        return false;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}


void app_main() {
  const uint8_t digitTable[] = {
    0b00111111,//0
    0b00000110,//1
    0b01011011,//2
    0b01001111,//3
    0b01100110,//4
    0b01101101,//5
    0b01111101,//6
    0b00000111,//7
    0b01111111,//8
    0b01101111,//9
  };

  gpio_config_t pin_config = {
    .mode=GPIO_MODE_DEF_OUTPUT,
    .pin_bit_mask=PIN_MASK,
    .pull_down_en=GPIO_PULLDOWN_DISABLE,
    .pull_up_en=GPIO_PULLUP_DISABLE,
    .intr_type=GPIO_INTR_DISABLE
  };

  gpio_config(&pin_config);
  gpio_set_level(DATA_,0);
  int rounds = 1;

  while(1){
    ESP_LOGI("main","round: %d",rounds);

  for (int j=9; j >= 0; j--){
    gpio_set_level(LATCH,0);
if (isPrime(j)){
    for (int i=7; i >=0; i--){
    
      
        gpio_set_level(CLOCK,0);
        gpio_set_level(DATA_,(digitTable[j] >> i) & 1 );
        
    gpio_set_level(CLOCK,1);
    }
    gpio_set_level(LATCH,1);
    vTaskDelay(1000*rounds / portTICK_PERIOD_MS);
  }

    
    
  }
  rounds++;
}

}
