#include "freertos/FreeRTOS.h"
#include "driver/gpio.h" 

#define RS GPIO_NUM_18
#define RW GPIO_NUM_17
#define EN GPIO_NUM_15

#define DATA GPIO_NUM_21
#define LATCH GPIO_NUM_22
#define CLOCK GPIO_NUM_23

#define R1 GPIO_NUM_13
#define R2 GPIO_NUM_12
#define R3 GPIO_NUM_14
#define R4 GPIO_NUM_27

// input pins
#define C1 GPIO_NUM_26
#define C2 GPIO_NUM_25
#define C3 GPIO_NUM_33
#define C4 GPIO_NUM_32

int output_pins[] = {RS, RW, EN, DATA, LATCH, CLOCK, R1, R2, R3, R4};

int input_pins[] = {C1, C2, C3, C4};

int row_pins[] = {R1, R2, R3, R4};

char keys[] = {'1','4','7','.','2','5','8','0','3','6','9','=','/','*','-','+'};
void write_data(int);

void set_rows(int lvl1, int lvl2, int lvl3, int lvl4){
    gpio_set_level(R1,lvl1);
    gpio_set_level(R2,lvl2);
    gpio_set_level(R3,lvl3);
    gpio_set_level(R4,lvl4);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void scan_keypad(void * param){
    while(1){
        set_rows(0,1,1,1);
        for (size_t i = 0; i < 4; i++){
            if (gpio_get_level(input_pins[i]) == 0){
                write_data(keys[4*i+0]);
            }
        }
        
        set_rows(1,0,1,1);
        for (size_t i = 0; i < 4; i++){
            if (gpio_get_level(input_pins[i]) == 0){
                write_data(keys[4*i+1]);
            }
        }
        
        set_rows(1,1,0,1);
        for (size_t i = 0; i < 4; i++){
            if (gpio_get_level(input_pins[i]) == 0){
                write_data(keys[4*i+2]);
            }
        }
        
        set_rows(1,1,1,0);
        for (size_t i = 0; i < 4; i++){
            if (gpio_get_level(input_pins[i]) == 0){
                write_data(keys[4*i+3]);
            }
        }
    }
}


void write_command(uint8_t command){
    gpio_set_level(RS,0);
    gpio_set_level(RW,0);

    gpio_set_level(LATCH,0);
    for (int i = 7; i >= 0; i--){
        gpio_set_level(CLOCK,0);
        gpio_set_level(DATA,(command >> i) & 0x1);
        gpio_set_level(CLOCK,1);
    }
    gpio_set_level(LATCH,1);

    gpio_set_level(EN,1);
    vTaskDelay(pdMS_TO_TICKS(5));
    gpio_set_level(EN,0);
    vTaskDelay(pdMS_TO_TICKS(5));
}

void write_data(int data){
    gpio_set_level(RS,1);
    gpio_set_level(RW,0);
     
    gpio_set_level(LATCH,0);
        for (int j = 7; j >= 0; j--){
            gpio_set_level(CLOCK,0);
            gpio_set_level(DATA,(data >> j) & 0x1);
            gpio_set_level(CLOCK,1);
    }
     gpio_set_level(LATCH,1);
    
    gpio_set_level(EN,1);
    vTaskDelay(pdMS_TO_TICKS(5));
    gpio_set_level(EN,0);
    vTaskDelay(pdMS_TO_TICKS(100));
    
}

void app_main() {
    for (int i = 0; i < sizeof(output_pins)/sizeof(output_pins[0]); i++){
    gpio_config_t output_pin_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << output_pins[i],
    };
    gpio_config(&output_pin_config);
}
    for (int i = 0; i < sizeof(input_pins)/sizeof(input_pins[0]); i++){
    gpio_config_t input_pin_config = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << input_pins[i],
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };
    gpio_config(&input_pin_config);
}

    uint8_t command = 0x0F;
    write_command(command);

    xTaskCreate(scan_keypad,"cycle rows",2048,NULL,1,NULL);

}
