#include <utils.h>
#include <stm32f10x.h>
#include <stdbool.h>

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

void turn_on_point(uint32_t i, uint32_t j, pin rows[], pin cols[])
{
	if (i > 7 || j > 7) {
		return;
	}
	for (uint32_t k = 0; k < 8; k++)
	{
		if (k == j) {
			rows[k]._gpio_x->ODR |= rows[k].pin_num;
		} else {
			rows[k]._gpio_x->ODR &= ~rows[k].pin_num;
		}
	}
	for (uint32_t k = 0; k < 8; k++)
	{
		if (k == i) {
			cols[k]._gpio_x->ODR &= ~cols[k].pin_num;
		} else {
			cols[k]._gpio_x->ODR |= cols[k].pin_num;
		}
	}
}

void up_button(bool previos_up_state, pin button_pin, matrix m, uint32_t i)
{
    bool up_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (up_state && !previos_up_state) {
        if (i == 0) {
            i = m.height - 1;
        } else {
            i = --i % m.height;
        }
    }
    delay_us(1000);
    previos_up_state = up_state;
}

void left_button(bool previos_left_state, pin button_pin, matrix m, uint32_t i)
{
    bool left_state = !(button_pin._gpio_x->IDR & button_pin.pin_num);
    if (left_state && !previos_left_state) {
        if (i == 0) {
            i = m.width - 1;
        } else {
            i = --i % m.width;
        }
    }
    delay_us(1000);
    previos_left_state = left_state;
}