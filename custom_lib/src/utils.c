#include <utils.h>
#include <stm32f10x.h>
#include <stdio.h>

void delay(uint32_t ticks) {
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


void delay_us(uint32_t us) {
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
        if (p->x == 0) {
            p->x = m.height - 1;
        } else {
            p->x = --p->x % m.height;
        }
    }
    delay_us(1000);
    *previos_up_state = up_state;
}

void left_button(bool* previos_left_state, pin button_pin, matrix m, point* p)
{
    bool left_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (left_state && !(*previos_left_state)) {
        if (p->y == 0) {
            p->y = m.width - 1;
        } else {
            p->y = --p->y % m.width;
        }
    }
    delay_us(1000);
    *previos_left_state = left_state;
}

void right_button(bool* previos_right_state, pin button_pin, matrix m, point* p)
{
    bool right_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (right_state && !(*previos_right_state)) {
        p->y = ++p->y % m.width;
    }
    delay_us(1000);
    *previos_right_state = right_state;
}

void down_button(bool* previos_down_state, pin button_pin, matrix m, point* p)
{
    bool down_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (down_state && !(*previos_down_state)) {
        p->x = ++p->x % m.height;
    }
    delay_us(1000);
    *previos_down_state = down_state;
}

void mid_button(bool* previos_mid_state, point* p, pin button_pin)
{
    bool mid_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (mid_state && !(*previos_mid_state)) {
        p->is_turned = !p->is_turned;
    }
    delay_us(1000);
    *previos_mid_state = mid_state;
}

void update_points(point curr_point, point points[], matrix m)
{
    uint8_t k = curr_point.y * m.width + curr_point.x;
    points[k] = curr_point;
}

void display_picture(point points[], matrix m, pin rows[], pin cols[])
{
    for (uint8_t i = 0; i < m.height * m.width; i++)
    {
        if (points[i].is_turned)
            turn_on_point(&rows[points[i].x], &cols[points[i].y]);
        else
            turn_off_point(&rows[points[i].x], &cols[points[i].y]);
        delay(10000);
    }
}

void test_ord()
{
    GPIOB->ODR |= GPIO_ODR_ODR5;
    GPIOB->ODR &= ~GPIO_ODR_ODR15;
}