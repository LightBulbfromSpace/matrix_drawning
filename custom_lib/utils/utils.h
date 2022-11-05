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

// (y, x)
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
bool set_button(bool* previos_set_state, bool set_flag, pin button_pin);
void rst_button(bool* previos_rst_state, pin button_pin, bool points[], matrix m);

void update_points(point curr_point, bool points[], matrix m, bool set_flag);
void display_picture(bool points[], point p, matrix m, pin rows[], pin cols[]);
point get_coord_from_array_index(int i, matrix m);
int get_array_index_from_coord(point p, matrix m);

void clear(bool points[], matrix m);