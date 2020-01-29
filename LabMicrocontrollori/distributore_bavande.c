#include<stdio.h>
#include<string.h>
#include "stm32_unict_lib.h"

enum {
    ST_CONFIG,
    ST_EROGAZIONE,
    ST_RESTO
};
int stato = ST_CONFIG;
float importo = 0;
enum {
	CAFFE,
	TE,
	CIOCCOLATA
};
int costo_bevande[] = { 0.35, 0.40, 0.45};
int bevanda_selezionata = -1;
enum {
	valore20,
	valore10,
	valore5
};
int serbatoio_monete[] = { 10, 10, 10};

int red_led_on = 0;
int yellow_led_on = 0;
int green_led_on = 0;

int count_erogazione = 0;
int main(int argc, char* argv[]){

	DISPLAY_init();
	GPIO_init(GPIOB);
	GPIO_init(GPIOC);
    ADC_init(ADC1,ADC_RES_8,ADC_ALIGN_RIGHT);

    GPIO_config_output(GPIOB,0);
    GPIO_config_output(GPIOC,3);
    GPIO_config_output(GPIOC,2);

	//push button X
	GPIO_config_input(GPIOB, 10);
	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	//push button Y
	GPIO_config_input(GPIOB, 4);
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	//push button Z
	GPIO_config_input(GPIOB, 5);
	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

	//push button T
	GPIO_config_input(GPIOB, 6);
	GPIO_config_EXTI(GPIOB, EXTI6);
	EXTI_enable(EXTI6, FALLING_EDGE);

    ADC_channel_config(ADC1,GPIOC,1,11);
	ADC_on(ADC1);

    TIM_config_timebase(TIM2, 42000, 1000);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_set(TIM2, 0);
    TIM_on(TIM2)

	for(;;){
        switch (stato)
        {
        case ST_CONFIG:
            ADC_sample_channel(ADC1,11);
        	ADC_start(ADC1);
        	while(!ADC_completed(ADC1)){}
        	adc_val=ADC_read(ADC1);
        	bevanda_selezionata = adc_val*(2-0)/255; //range[0,2]
            break;
        case ST_EROGAZIONE:
            break;
        case ST_RESTO:
            break;
        default:
            break;
        }

	}
	return 0;
}

//Y
void EXTI4_IRQHandler(void){
	if(EXTI_isset(EXTI4)){
        if(stato == ST_CONFIG){
            red_led_on = 1;
            importo += 0.20;
        }
            
        EXTI_clear(EXTI4);
	}
}

//X
void EXTI15_10_IRQHandler(void){
	if(EXTI_isset(EXTI10)){
        if(stato == ST_CONFIG){
            red_led_on = 1;
            importo += 0.50;
        }
        EXTI_clear(EXTI10);
	}
}

void EXTI9_5_IRQHandler(void){
	if(EXTI_isset(EXTI5)){		//Z
		if(stato == ST_CONFIG){
            red_led_on = 1;
            importo += 0.10;
        }
        EXTI_clear(EXTI5);
	}
	else if(EXTI_isset(EXTI6)){ //T
            if(stato == ST_CONFIG)
                if(importo >= costo_bevande[bevanda_selezionata]){
                    count_erogazione = 0;
                    stato = ST_EROGAZIONE;
                }
	        EXTI_clear(EXTI6);
		}
}

void TIM2_IRQHandler(){
     switch (stato)
        {
        case ST_CONFIG:
            int stato_led = GPIO_read(GPIOB, 0);
            if(red_led_on && stato_led == 0)
                GPIO_write(GPIOB, 0, 1);
            else{
                red_led_on = 0;
                GPIO_write(GPIOB, 0, 0);
            }
        case ST_EROGAZIONE:
            GPIO_write(GPIOC, 3, 1);
            if(++count_erogazione == 2){
                GPIO_write(GPIOC, 3, 0);
                stato = ST_RESTO;
            }
            break;
        case ST_RESTO:
            break;
        default:
            break;
        }
    TIM_update_clear(TIM2);
}

