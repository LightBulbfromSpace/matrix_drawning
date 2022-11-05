#include <utils.h>
#include <stm32f10x.h>

void delay(uint32_t ticks)
{
    //for (int i=0; i<ticks; i++) {
    //    __NOP();
    //}
    __asm__ volatile(
        "mov r0, #0x0\n\t"
        "mov r1, %0\n\t"
        "loop:\n\t"
            "add r0, r0, #1\n\t"
            "cmp r0, r1\n\t"
        "bne loop\n\t"
        :: "r"(ticks)
    );
}

void delay_us(uint32_t us)
{
    __asm volatile (
        "push {r0}\r\n"
        "mov R0, %0\r\n"
        "_loop:\r\n"                //approx. 8 ticks/iteration
            "cmp R0, #0\r\n"        //
            "beq _exit\r\n"         //1 or 1+P (if true: time for clear pipeline)
            "sub R0, R0, #1\r\n"    //1
            "nop\r\n"               //1 alignment
            "b _loop\r\n"           //1+P (pipleline)
        "_exit:\r\n"
        "pop {r0}\r\n"
        :: "r" (9 * us)             //for 72 Vhz
    );
}

void turn_on_point(pin* row, pin* col)
{
	row->_gpio_x->ODR |= row->pin_num;
	col->_gpio_x->ODR &= ~col->pin_num;
}

void turn_off_point(pin* row, pin* col)
{
    row->_gpio_x->ODR &= ~row->pin_num;
    col->_gpio_x->ODR |= col->pin_num;
}

void up_button(bool* previos_up_state, pin button_pin, matrix m, point* p)
{
    bool up_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (up_state && !(*previos_up_state)) {
        if (p->y == 0) {
            p->y = m.height - 1;
        } else {
            p->y = --p->y % m.height;
        }
    }
    delay_us(500);
    *previos_up_state = up_state;
}

void left_button(bool* previos_left_state, pin button_pin, matrix m, point* p)
{
    bool left_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (left_state && !(*previos_left_state)) {
        if (p->x == 0) {
            p->x = m.width - 1;
        } else {
            p->x = --p->x % m.width;
        }
    }
    delay_us(500);
    *previos_left_state = left_state;
}

void right_button(bool* previos_right_state, pin button_pin, matrix m, point* p)
{
    bool right_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (right_state && !(*previos_right_state)) {
        p->x = ++p->x % m.width;
    }
    delay_us(500);
    *previos_right_state = right_state;
}

void down_button(bool* previos_down_state, pin button_pin, matrix m, point* p)
{
    bool down_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (down_state && !(*previos_down_state)) {
        p->y = ++p->y % m.height;
    }
    delay_us(500);
    *previos_down_state = down_state;
}

void mid_button(bool* previos_mid_state, point* p, pin button_pin)
{
    bool mid_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (mid_state && !(*previos_mid_state)) {
        p->is_turned = !p->is_turned;
    }
    delay_us(500);
    *previos_mid_state = mid_state;
}

bool set_button(bool* previos_set_state, bool set_flag, pin button_pin)
{
    bool set_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (set_state && !(*previos_set_state)) {
        set_flag = !set_flag;
    }
    delay_us(500);
    *previos_set_state = set_state;
    return set_flag;
}

void rst_button(bool* previos_rst_state, pin button_pin, bool points[], matrix m)
{
    bool rst_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (rst_state && !(*previos_rst_state)) {
        clear(points, m);
    }
    delay_us(500);
    *previos_rst_state = rst_state;
}

void update_points(point curr_point, bool points[], matrix m, bool set_flag)
{
    if (set_flag)
    {
        int k = get_array_index_from_coord(curr_point, m);
        points[k] = curr_point.is_turned;
    }
}

void display_picture(bool points[], point p, matrix m, pin rows[], pin cols[])
{
    if (p.is_turned)
    {
        turn_on_point(&rows[p.y], &cols[p.x]);
        delay_us(100);
        turn_off_point(&rows[p.y], &cols[p.x]);
    }
    for (uint8_t i = 0; i < m.height * m.width; i++)
    {
        point p = get_coord_from_array_index(i, m);
        if (points[i]) {
            turn_on_point(&rows[p.x], &cols[p.y]);
            delay_us(100);
        }
        turn_off_point(&rows[p.x], &cols[p.y]);
    }
}

point get_coord_from_array_index(int i,  matrix m)
{
    point p = {i % m.width, i / m.width}; 
    return p;
}

int get_array_index_from_coord(point p, matrix m)
{
    return p.y * m.width + p.x;
}

void clear(bool points[], matrix m)
{
    for (uint8_t i = 0; i < m.width * m.height; i++)
        points[i] = false;
}