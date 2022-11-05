#include <stm32f10x.h>
#include <stdint.h>
#include <stdbool.h>

//stores port and number of pin
typedef struct
{
	GPIO_TypeDef* _gpio_x;
	uint32_t pin_num
} pin;

//stores height and width of LED matrix
typedef struct
{
    uint8_t width;
    uint8_t height;
} matrix;

typedef struct
{
    uint8_t y;
    uint8_t x;
    bool is_turned;
} point;


void delay(uint32_t ticks);
void delay_us(uint32_t us);

void turn_on_point(pin* row, pin* col);
void turn_off_point(pin* row, pin* col);

void up_button(bool* previos_up_state, pin button_pin, matrix m, point* p);
void left_button(bool* previos_left_state, pin button_pin, matrix m, point* p);
void right_button(bool* previos_right_state, pin button_pin, matrix m, point* p);
void down_button(bool* previos_down_state, pin button_pin, matrix m, point* p);
void mid_button(bool* previos_mid_state, point* p, pin button_pin);

void update_points(point curr_point, point points[], matrix m);
void display_picture(point points[], matrix m, pin rows[], pin cols[]);
void test_ord();