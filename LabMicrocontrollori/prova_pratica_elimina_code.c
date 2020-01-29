#include "stm32_unict_lib.h"
#include "stdio.h"

enum stati {
	S_RUN,
	S_RILASCIO
};

int stato = S_RUN;
int turno = 0;
int ticket_counter = 0;
int flashing_on = 0;
int flashing_times = 0;
int tempo_medio = 0;
int flash = 0;

void main(){
	CONSOLE_init();
	DISPLAY_init();

	GPIO_init(GPIOB);

	GPIO_config_output(GPIOB, 8);
	GPIO_write(GPIOB, 8, 1);

	//x
	GPIO_config_input(GPIOB, 10);
	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	//y
	GPIO_config_input(GPIOB, 4);
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	//timer
	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 42000, 500);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);

	for(;;){
		char dyspl[5];
		printf("flashing_times: %d, Turno: %d, Ticket: %d, Tempo medio: %d\n", flashing_times, turno, ticket_counter, tempo_medio);
		switch(stato){
		case S_RUN:
			sprintf(dyspl, "%.2d%.2d", turno, tempo_medio);
			DISPLAY_puts(0, dyspl);
			break;
		case S_RILASCIO:
			if(flash){
				if(flashing_times < 8){
					if(flashing_on){
						sprintf(dyspl, "%.2d%.2d", ticket_counter, tempo_medio);
						DISPLAY_puts(0, dyspl);
					} else {
						sprintf(dyspl, "  %.2d", tempo_medio);
						DISPLAY_puts(0, dyspl);
					}
					flashing_times++;
					} else {
						stato = S_RUN;
						flashing_times = 0;
						flashing_on = 0;
				}
				flash = 0;
			}
			break;
		default:
			break;
		}
	}
}

void EXTI15_10_IRQHandler(){
	if(EXTI_isset(EXTI10)){
		if(stato == S_RUN){
			stato = S_RILASCIO;
			ticket_counter++;
			ticket_counter%=100;
			tempo_medio+=2;
			tempo_medio%=100;
		}
		EXTI_clear(EXTI10);
	}
}

void EXTI4_IRQHandler(){
	if(EXTI_isset(EXTI4)){
		if(stato == S_RUN && turno + 1 <= ticket_counter){
			tempo_medio -=2;
			turno++;
			turno%=100;
		}
		EXTI_clear(EXTI4);
	}
}

void TIM2_IRQHandler(){
	if(TIM_update_check(TIM2)){
		if(stato == S_RILASCIO){
			flash = 1;
			flashing_on = !flashing_on;
		}
		TIM_update_clear(TIM2);
	}
}
