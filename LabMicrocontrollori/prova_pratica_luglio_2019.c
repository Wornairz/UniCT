#include "stm32_unict_lib.h"
#include "stdio.h"

int contenitori[] = {0,0,0};
int Pcounter = 0;
int P = 10;
int tmpP = 0;
int intervalloNastro = 0;

enum stati {
	S_RUN,
	S_CONFIG,
	S_FINDOBJ,
	S_SVUOTA
};

int stato = S_CONFIG;

int t_on = 0;
int countFlashing = 0;
enum coloreObj {
	ROSSO,
	VERDE,
	GIALLO
};
int objType = VERDE;

int main(){
	GPIO_init(GPIOB);
	GPIO_init(GPIOC);
	DISPLAY_init();
	CONSOLE_init();

	//led
	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOC, 2);
	GPIO_config_output(GPIOC, 3);

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

	//t
	GPIO_config_input(GPIOB, 6);
	GPIO_config_EXTI(GPIOB, EXTI6);
	EXTI_enable(EXTI6, FALLING_EDGE);

	//ADC
	ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 1, 11);
	ADC_on(ADC1);

	//timer
	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 42000, 200);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);

	TIM_init(TIM3);
	TIM_config_timebase(TIM3, 42000, 2000);
	TIM_enable_irq(TIM3, IRQ_UPDATE);
	TIM_on(TIM3);

	for(;;){
		char showDisplay[5];
		switch(stato){
			case S_RUN:
				DISPLAY_dp(1,0);
				if(intervalloNastro)
					DISPLAY_puts(0, " - -");
				else
					DISPLAY_puts(0, "- - ");
				break;
			case S_CONFIG:
				ADC_sample_channel(ADC1, 11);
				ADC_start(ADC1);
				while(!ADC_completed(ADC1)){}
				tmpP = (ADC_read(ADC1)*((float) (20 - 10)/255)) + 10;
				sprintf(showDisplay, "%.4d", tmpP);
				DISPLAY_puts(0, showDisplay);
				break;
			case S_FINDOBJ:
				sprintf(showDisplay, "%.2d", contenitori[objType]);
				DISPLAY_puts(0, showDisplay);
				sprintf(showDisplay, "%.2d", Pcounter);
				DISPLAY_puts(2, showDisplay);
				DISPLAY_dp(1,1);
				break;
			case S_SVUOTA:
				DISPLAY_puts(0, "EE--");
				if(Pcounter == P){
					if(contenitori[ROSSO] > 5){
						contenitori[ROSSO] = 0;
						GPIO_write(GPIOB, 0, 1);
					}
					if(contenitori[VERDE] > 5){
						contenitori[VERDE] = 0;
						GPIO_write(GPIOC, 3, 1);
					}
					if(contenitori[GIALLO] > 5){
						contenitori[GIALLO] = 0;
						GPIO_write(GPIOC, 2, 1);
					}
					delay_ms(2000);
					GPIO_write(GPIOB, 0, 0);
					GPIO_write(GPIOC, 3, 0);
					GPIO_write(GPIOC, 2, 0);
					Pcounter = 0;
					stato = S_RUN;
				}
				break;
			default:
				break;
		}
	}
	return 0;
}

//x
void EXTI15_10_IRQHandler(){
	if(EXTI_isset(EXTI10)){
		if(stato == S_RUN){
			contenitori[ROSSO]++;
			objType = ROSSO;
			t_on = 1;
			stato = S_FINDOBJ;
		}
		EXTI_clear(EXTI10);
	}
}

//y
void EXTI4_IRQHandler(){
	if(EXTI_isset(EXTI4)){
		if(stato == S_RUN){
			contenitori[VERDE]++;
			objType = VERDE;
			t_on = 1;
			stato = S_FINDOBJ;
		}
		EXTI_clear(EXTI4);
	}
}

//z, t
void EXTI9_5_IRQHandler(){
	if(EXTI_isset(EXTI5)){
		if(stato == S_RUN){
			contenitori[GIALLO]++;
			objType = GIALLO;
			t_on = 1;
			stato = S_FINDOBJ;
		}
		EXTI_clear(EXTI5);
	}
	else if(EXTI_isset(EXTI6)){
		if(stato == S_RUN)
			stato = S_CONFIG;
		else if(stato == S_CONFIG){
			P = tmpP;
			stato = S_RUN;
		}
		EXTI_clear(EXTI6);
	}
}

void TIM2_IRQHandler(){
	if(TIM_update_check(TIM2)){
		if(countFlashing > 5){
			t_on = 0;
			countFlashing = 0;
			stato = S_RUN;
		}
		else if(t_on){
			switch(objType){
				case ROSSO:
					GPIO_toggle(GPIOB, 0);
					break;
				case VERDE:
					GPIO_toggle(GPIOC, 3);
					break;
				case GIALLO:
					GPIO_toggle(GPIOC, 2);
					break;
			}
			countFlashing++;
		}
		TIM_update_clear(TIM2);
	}
}

void TIM3_IRQHandler(){
	if(TIM_update_check(TIM3)){
		Pcounter++;
		if(stato == S_RUN)
			intervalloNastro = 1 - intervalloNastro;
		if(Pcounter == P)
			stato = S_SVUOTA;
		if(stato == S_CONFIG)
			Pcounter = 0;

		TIM_update_clear(TIM3);
	}
}
