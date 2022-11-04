#include <stm32f10x.h>
#include <stdint.h>

// stores port and number of pin
typedef struct 
{
	GPIO_TypeDef* _gpio_x;
	uint32_t pin_num
} pin;

typedef struct
{
    uint32_t width;
    uint32_t height;
} matrix;


uint32_t matrix_width = 8;
uint32_t matrix_height = 8;

void delay(uint32_t ticks);
void delay_us(uint32_t us);
void turn_on_point(uint32_t i, uint32_t j, pin rows[], pin cols[]);
void up_button(bool previos_up_state, pin button_pin, matrix m, uint32_t i);
void left_button(bool previos_left_state, pin button_pin, matrix m, uint32_t i);