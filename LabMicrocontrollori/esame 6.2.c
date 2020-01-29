#include "stm32_unict_lib.h"
#include "stdio.h"

enum {
	S_RUN,
	S_CONF,
	S_SHOWTIME,
	S_CONFTIME
};

int stato = S_CONF;
int opt = 0;
int led_on = 0;
int add_sec = 0;
int stato_led = 0;
int time[2] = {0, 0};
int last_time_set[2] = {0, 0};
int start_time[2] = {0, 0};
int end_time[2] = {0, 0};
int tmp_time[2] = {0, 0};

void main(){
	DISPLAY_init();
	CONSOLE_init();

	GPIO_init(GPIOB);
	GPIO_init(GPIOC);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOB, 8);
	GPIO_config_output(GPIOC, 2);

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

	//ADC
	ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 1, 11);
	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_on(ADC1);

	//TIM
	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 42000, 1000);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);

	for(;;){
		char dysp[5];
		if(led_on)
			GPIO_write(GPIOB, 8, 1);
		else
			GPIO_write(GPIOB, 8, 0);
		if(add_sec > 1){
			time[1]++;
			time[1]%=60;
			if(time[1] == 0){
				time[0]++;
				time[0]%=60;
			}
			add_sec = 0;
		}
		switch (stato) {
			case S_RUN:
				GPIO_write(GPIOB, 8, 1);
				GPIO_write(GPIOB, 0, 0);
				printf("%.2d%.2d\n", time[0], time[1]);
				sprintf(dysp, "%.2d%.2d", time[0], time[1]);
				DISPLAY_puts(0, dysp);
				break;
			case S_CONF:
				GPIO_write(GPIOB, 0, 1);
				switch (opt) {
					case 0:
						DISPLAY_puts(0, "  ti");
						break;
					case 1:
						DISPLAY_puts(0, "  st");
						break;
					case 2:
						DISPLAY_puts(0, "  en");
						break;
					default:
						DISPLAY_puts(0, "erro");
						break;
				}
				break;
			case S_SHOWTIME:
				GPIO_write(GPIOB, 8, 1);
				switch (opt) {
					case 0:
						sprintf(dysp, "%.2d%.2d", last_time_set[0], last_time_set[1]);
						DISPLAY_puts(0, dysp);
						break;
					case 1:
						sprintf(dysp, "%.2d%.2d", start_time[0], start_time[1]);
						DISPLAY_puts(0, dysp);
						break;
					case 2:
						sprintf(dysp, "%.2d%.2d", end_time[0], end_time[1]);
						DISPLAY_puts(0, dysp);
						break;
					default:
						DISPLAY_puts(0, "erro");
						break;
				}
				break;
			case S_CONFTIME:
				ADC_sample_channel(ADC1, 11);
				ADC_start(ADC1);
				while(!ADC_completed(ADC1)) { }
				tmp_time[0] = ADC_read(ADC1)*59/255;

				ADC_sample_channel(ADC1, 10);
				ADC_start(ADC1);
				while(!ADC_completed(ADC1)) { }
				tmp_time[1] = ADC_read(ADC1)*59/255;
				printf("ore: %.2d, minuti: %.2d\n", tmp_time[0], tmp_time[1]);
				sprintf(dysp, "%.2d%.2d", tmp_time[0], tmp_time[1]);
				DISPLAY_puts(0, dysp);
				break;
			default:
				break;
		}
	}
}

//x
void EXTI15_10_IRQHandler(){
	if(EXTI_isset(EXTI10)){
		if(stato == S_RUN){
			stato = S_CONF;
		} else if(stato == S_CONF){
			opt++;
			opt %= 3;
		} else if(stato == S_CONFTIME){
			if(opt == 0){
				time[0] = tmp_time[0];
				time[1] = tmp_time[1];
				last_time_set[0] = tmp_time[0];
				last_time_set[1] = tmp_time[1];
			} else if(opt == 1){
				start_time[0] = tmp_time[0];
				start_time[1] = tmp_time[1];
			} else if(opt == 2){
				end_time[0] = tmp_time[0];
				end_time[1] = tmp_time[1];
			}
			stato = S_CONF;
			led_on = 0;
		}

		EXTI_clear(EXTI10);
	}
}

//y
void EXTI4_IRQHandler(){
	if(EXTI_isset(EXTI4)){
		if(stato == S_CONF){
			add_sec = 0;
			stato = S_RUN;
		}
		else if(stato == S_CONFTIME || stato == S_SHOWTIME){
			led_on = 0;
			stato = S_CONF;
		}

		EXTI_clear(EXTI4);
	}
}

//z
void EXTI9_5_IRQHandler(){
	if(EXTI_isset(EXTI5)){
		if(stato == S_CONF)
			stato = S_SHOWTIME;
		else if(stato == S_SHOWTIME)
			stato = S_CONFTIME;
		EXTI_clear(EXTI5);
	}
}

void TIM2_IRQHandler(){
	if(TIM_update_check(TIM2)){
		add_sec++;
		if(stato == S_CONFTIME)
			led_on = !led_on;
		if(stato == S_RUN && add_sec > 1){
			if((time[0] == start_time[0] && time[1] == start_time[1]) || (time[0] == end_time[0] && time[1] == end_time[1]))
				GPIO_toggle(GPIOC, 2);
		}

		TIM_update_clear(TIM2);
	}
}
