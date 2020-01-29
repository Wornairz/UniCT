#include "stm32_unict_lib.h"
#include "stdio.h"

enum stati{
	S_RUN,
	S_STARGET
};
int stato = S_STARGET;

int x = 0;
int y = 0;
int xs = 0;
int ys = 0;

void main(){
	CONSOLE_init();
	DISPLAY_init();
	GPIO_init(GPIOB);
	GPIO_init(GPIOC);

	//led giallo
	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOC, 2);
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

	//z
	GPIO_config_input(GPIOB, 5);
	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

	//adc
	ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 1, 11);
	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_on(ADC1);

	//timer
	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 42000, 400);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);

	for(;;){
		char dyspl[5];
		printf("Stato: %d", stato);
		printf("\t\t\t x: %d, y: %d\t\t\t x: %d, y: %d\n", x, y, xs, ys);
		printf("", xs, ys);
		switch(stato){
			case S_RUN:
				GPIO_write(GPIOC, 2, 0);
				GPIO_write(GPIOB, 0, 1);
				sprintf(dyspl, "%.2d%.2d", x, y);
				DISPLAY_puts(0, dyspl);
				break;
			case S_STARGET:
				GPIO_write(GPIOC, 2, 1);
				GPIO_write(GPIOB, 0, 0);
				ADC_sample_channel(ADC1, 11);
				ADC_start(ADC1);
				while(!ADC_completed(ADC1)){}
				xs = (ADC_read(ADC1)*((float) 99/255));

				ADC_sample_channel(ADC1, 10);
				ADC_start(ADC1);
				while(!ADC_completed(ADC1)){}
				ys = (ADC_read(ADC1)* ((float) 99/255));
				sprintf(dyspl, "%.2d%.2d", xs, ys);
				DISPLAY_puts(0, dyspl);

				break;
			default:
				printf("Error");
				break;
		}
	}
}

//x
void EXTI15_10_IRQHandler(){
	if(EXTI_isset(EXTI10)){
		stato = S_STARGET;
		EXTI_clear(EXTI10);
	}
}

//y
void EXTI4_IRQHandler(){
	if(EXTI_isset(EXTI4)){
		if(stato == S_STARGET){
			stato = S_RUN;
			EXTI_clear(EXTI4);
		}
	}
}

//z
void EXTI9_5_IRQHandler(){
	if(EXTI_isset(EXTI5)){
		if(stato == S_RUN){
			xs = 0;
			ys = 0;
			EXTI_clear(EXTI5);
		}
	}
}

void TIM2_IRQHandler(){
	if(TIM_update_check(TIM2)){
		if(stato == S_RUN){
			if(x < xs){
				x++;
			} else if(x > xs){
				x--;
			} else if(x == xs && y < ys){
				y++;
			} else if(x == xs && y > ys){
				y--;
			}
		}

		TIM_update_clear(TIM2);
	}
}
