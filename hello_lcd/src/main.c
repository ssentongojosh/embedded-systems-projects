
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

int data_pins [8] = {D0, D1, D2, D3, D4, D5, D6, D7};

void write_command(uint8_t command){
    gpio_set_level(RS,0);
    gpio_set_level(RW,0);

    for (int i = 0; i <= 7; i++){
        gpio_set_level(data_pins[i],(command >> i) & 0x1);
    }
    gpio_set_level(EN,1);
    vTaskDelay(pdMS_TO_TICKS(5));
    gpio_set_level(EN,0);
    vTaskDelay(pdMS_TO_TICKS(5));
}

void write_data(char * data, int size){
    gpio_set_level(RS,1);
    gpio_set_level(RW,0);

    
   
    for (int i = 0; i < size; i++)
    {        
        for (int j = 0; j <= 7; j++){
        gpio_set_level(data_pins[j],(data[i] >> j) & 0x1);
    }

    gpio_set_level(EN,1);
    vTaskDelay(pdMS_TO_TICKS(5));
    gpio_set_level(EN,0);
    vTaskDelay(pdMS_TO_TICKS(450));
    }
    
}


void app_main() {
    gpio_config_t pin_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = PIN_MASK,
    };

    gpio_config(&pin_config);

    // initialize lcd to display ON, cursor ON and cursor BLINKING
    // this can be doen in entry mode (D3 = 1) and D2 = 1 (for display ON)
    // D1 = 1 (for cursor ON) and D0 = 1 (for cursor blinking)
    // this gives the value 00001111 which in hex values is 0x0F

    uint8_t command = 0x0F;
    write_command(command);

    char data[16] = "hello Ssentongo"; 
    int size = sizeof(data);
    write_data(data, size);

}
