
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define RS GPIO_NUM_18
#define RW GPIO_NUM_17
#define EN GPIO_NUM_15
#define D0 GPIO_NUM_19
#define D1 GPIO_NUM_21
#define D2 GPIO_NUM_13
#define D3 GPIO_NUM_12
#define D4 GPIO_NUM_14
#define D5 GPIO_NUM_27
#define D6 GPIO_NUM_26
#define D7 GPIO_NUM_25

#define PIN_MASK ((1UL << RS) | (1UL << RW) | (1UL << EN) | (1UL << D0) | (1UL << D1) | (1UL << D2) | (1UL << D3) | (1UL << D4) | (1UL << D5) | (1UL << D6) | (1UL << D7))

#define OUTPUT GPIO_MODE_OUTPUT

void digit_write(int pin, int level){
    gpio_set_level(pin,level);
    gpio_set_level(EN,1);
    vTaskDelay(pdMS_TO_TICKS(5));
    gpio_set_level(EN,0);

}

void app_main() {
    gpio_config_t pin_config = {
        .mode = OUTPUT,
        .pin_bit_mask = PIN_MASK,
    };

    gpio_config(&pin_config);
    

    // initialize
    gpio_set_level(RS,0); //command set
    gpio_set_level(RW,0); // write mode

    digit_write(D0,1); // 1 = Blink char at cursor
    digit_write(D1,1); // 1 = Cursor ON
    digit_write(D2,1); // 1 = Display ON
    digit_write(D3,1); // display ON/OFF control
    digit_write(D4,0);
    digit_write(D5,0);
    digit_write(D6,0);
    digit_write(D7,0);

}
