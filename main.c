#include <stdint.h>
#include <utils.h>
#include <stm32f10x.h>
#include <stdbool.h>

void my_turn_on_point(pin row, pin col)
{
	// if (p.x > 7 || p.y > 7) {
	// 	return;
	// }
	row._gpio_x->ODR |= row.pin_num;
	col._gpio_x->ODR &= ~col.pin_num;
}

int __attribute((noreturn)) main(void) {

	// LED rows and colums
	pin gpio_odr_rows[] = {{GPIOB, GPIO_ODR_ODR7}, {GPIOB, GPIO_ODR_ODR6},
								{GPIOB, GPIO_ODR_ODR8}, {GPIOB, GPIO_ODR_ODR5},
								{GPIOA, GPIO_ODR_ODR5}, {GPIOB, GPIO_ODR_ODR9},
								{GPIOA, GPIO_ODR_ODR6}, {GPIOA, GPIO_ODR_ODR4}};
	pin gpio_odr_cols[] = {{GPIOB, GPIO_ODR_ODR11}, {GPIOB, GPIO_ODR_ODR10},
								{GPIOB, GPIO_ODR_ODR0}, {GPIOB, GPIO_ODR_ODR14},
								{GPIOA, GPIO_ODR_ODR7}, {GPIOB, GPIO_ODR_ODR13},
								{GPIOB, GPIO_ODR_ODR15}, {GPIOB, GPIO_ODR_ODR1}};

	matrix m = {8, 8};

	pin gpio_odr_buttons[] = {{GPIOA, GPIO_ODR_ODR3}, {GPIOA, GPIO_ODR_ODR2},
								{GPIOA, GPIO_ODR_ODR1}, {GPIOA, GPIO_ODR_ODR0},
								{GPIOC, GPIO_ODR_ODR15}}; // UP DWN LFT RHT MID

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	// buttons' pins set up
	GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_MODE15 | GPIO_CRH_CNF15) | GPIO_CRH_MODE15_1;
	GPIOC->ODR |= GPIO_ODR_ODR15;	// MID
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0) | GPIO_CRL_MODE0_1;
	GPIOA->ODR |= GPIO_ODR_ODR0;	// RIGHT
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1) | GPIO_CRL_MODE1_1;
	GPIOA->ODR |= GPIO_ODR_ODR1;	// LEFT
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2) | GPIO_CRL_MODE2_1;
	GPIOA->ODR |= GPIO_ODR_ODR2;	// DOWN
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3) | GPIO_CRL_MODE3_1;
	GPIOA->ODR |= GPIO_ODR_ODR3;	// UP

	// matrix's pins set up
	GPIOB->CRH = GPIOB->CRH & ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14) | GPIO_CRH_MODE14_0;
	GPIOB->CRH = GPIOB->CRH & ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13) | GPIO_CRH_MODE13_0;
	GPIOB->CRH = GPIOB->CRH & ~(GPIO_CRH_MODE15 | GPIO_CRH_CNF15) | GPIO_CRH_MODE15_0;
	GPIOB->CRH = GPIOB->CRH & ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11) | GPIO_CRH_MODE11_0;
	GPIOB->CRH = GPIOB->CRH & ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10) | GPIO_CRH_MODE10_0;
	GPIOB->CRH = GPIOB->CRH & ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9) | GPIO_CRH_MODE9_0;
	GPIOB->CRH = GPIOB->CRH & ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8) | GPIO_CRH_MODE8_0;
	GPIOB->CRL = GPIOB->CRL & ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7) | GPIO_CRL_MODE7_0;
	GPIOB->CRL = GPIOB->CRL & ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6) | GPIO_CRL_MODE6_0;
	GPIOB->CRL = GPIOB->CRL & ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5) | GPIO_CRL_MODE5_0;
	GPIOB->CRL = GPIOB->CRL & ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1) | GPIO_CRL_MODE1_0;
	GPIOB->CRL = GPIOB->CRL & ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0) | GPIO_CRL_MODE0_0;
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7) | GPIO_CRL_MODE7_0;
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6) | GPIO_CRL_MODE6_0;
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5) | GPIO_CRL_MODE5_0;
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4) | GPIO_CRL_MODE4_0;

	bool previos_up_state = false;
	bool previos_left_state = false;
	bool previos_mid_state = false;
	bool previos_down_state = false;
	bool previos_right_state = false;

	point points[64];
	uint8_t i = 0;
	uint8_t j = 0;
	for (uint8_t k = 0; k < m.height * m.width; k++) {
		points[k].y = j;
		points[k].x = i;
		points[k].is_turned = false;
		j++;
		if (j % m.width == 0)
		{
			i++;
			j = 0;
		}
	}

	//point curr_point = {0, 0, true};
	// matrice check turn on all
	// GPIOB->ODR |= GPIO_ODR_ODR7;
	// GPIOB->ODR |= GPIO_ODR_ODR6;
	// GPIOB->ODR |= GPIO_ODR_ODR8;
	// GPIOB->ODR |= GPIO_ODR_ODR5;
	// GPIOA->ODR |= GPIO_ODR_ODR5;
	// GPIOB->ODR |= GPIO_ODR_ODR9;
	// GPIOA->ODR |= GPIO_ODR_ODR6;
	// GPIOA->ODR |= GPIO_ODR_ODR4;

	GPIOB->ODR |= GPIO_ODR_ODR11;
	GPIOB->ODR |= GPIO_ODR_ODR10;
	GPIOB->ODR |= GPIO_ODR_ODR0;
	GPIOB->ODR |= GPIO_ODR_ODR14;
	GPIOA->ODR |= GPIO_ODR_ODR7;
	GPIOB->ODR |= GPIO_ODR_ODR13;
	GPIOB->ODR |= GPIO_ODR_ODR15;
	GPIOB->ODR |= GPIO_ODR_ODR1;

	// rows should have high voltage, colums - low (example for point(R1, C5))
	// GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7) | GPIO_CRL_MODE7_1;
	// GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6) | GPIO_CRL_MODE6_1;
	// GPIOA->ODR |= GPIO_ODR_ODR6;

	// gpio_odr_rows[curr_point.x]._gpio_x->ODR |= gpio_odr_rows[curr_point.x].pin_num;
    // gpio_odr_cols[curr_point.y]._gpio_x->ODR &= ~gpio_odr_cols[curr_point.y].pin_num;

	//turn_on_point(&gpio_odr_rows[curr_point.x], &gpio_odr_cols[curr_point.y]);

	//test_ord();

	while (1)
	{
		// up_button(&previos_up_state, gpio_odr_buttons[0], m, &curr_point);
		// left_button(&previos_left_state, gpio_odr_buttons[2], m, &curr_point);
		// mid_button(&previos_mid_state, &curr_point, gpio_odr_buttons[4]);
		// down_button(&previos_down_state, gpio_odr_buttons[1], m, &curr_point);
		// right_button(&previos_right_state, gpio_odr_buttons[3], m, &curr_point);
		
		if (i == 0) {
			points[63].is_turned = false;
		}
		points[i].is_turned = false;
		i = ++i % 64;
		points[i].is_turned = true;


		//update_points(curr_point, points, m);
		display_picture(points, m, gpio_odr_rows, gpio_odr_cols);
		delay_us(100000);
	}
}