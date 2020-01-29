#include "stm32_unict_lib.h"
#include <stdio.h>

enum
{
    ST_CHIUSO,
    ST_APERTURA,
    ST_APERTO,
    ST_CHIUSURA
};
int current_state = ST_CHIUSO;

int opening_progress = 0;
int waiting_progress = 0;
int incremento_tc;
int incremento_ta;

int main()
{
    DISPLAY_init();
    GPIO_init(GPIOB);
    GPIO_init(GPIOC);
    TIM_init(TIM2);
    ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);

    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_channel_config(ADC1, GPIOC, 0, 10);
    ADC_on(ADC1);

    GPIO_config_output(GPIOB, 0);

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

    TIM_config_timebase(TIM2, 42000, 1000);
    //Abilito interrupt timer
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_set(TIM2, 0);

    float adc_val = 0;

    for (;;)
    {
        ADC_sample_channel(ADC1, 11);
        ADC_start(ADC1);
        while (!ADC_completed(ADC1))
        {
        }
        adc_val = ADC_read(ADC1);
        incremento_tc = 8 - (adc_val * (8 - 5) / 255); //incremento intervallo [6,10] tc in percentuale
        ADC_sample_channel(ADC1, 10);
        ADC_start(ADC1);
        while (!ADC_completed(ADC1))
        {
        }
        adc_val = ADC_read(ADC1);
        incremento_ta = 16 - (adc_val * (16 - 3) / 255); //incremento intervallo [3,15] ta in percentuale
        /*char str[5]; 
      sprintf(str,"%04d",incremento_tc); 
      DISPLAY_puts(0,str); 
    */
        switch (current_state)
        {
        case ST_CHIUSO:
            GPIO_write(GPIOB, 0, 0);
            DISPLAY_puts(0, "----");
            break;
        default:
            if (opening_progress >= 0 && opening_progress <= 110)
            {
                if (opening_progress < 25)
                    DISPLAY_puts(0, "----");
                else if (opening_progress < 50)
                    DISPLAY_puts(0, "--- ");
                else if (opening_progress < 75)
                    DISPLAY_puts(0, "--  ");
                else if (opening_progress < 100)
                    DISPLAY_puts(0, "-   ");
                else if (opening_progress >= 100)
                    DISPLAY_puts(0, "    ");
                break;
            }
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10))
    {
        if (current_state == ST_CHIUSO)
        {
            TIM_on(TIM2);
            current_state = ST_APERTURA;
        }
        else if (current_state == ST_CHIUSURA)
        {
            current_state = ST_APERTURA;
        }
        EXTI_clear(EXTI10);
    }
}

void EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4))
    {
        if (current_state == ST_APERTO)
        {
            waiting_progress = 100;
        }
        EXTI_clear(EXTI4);
    }
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI5))
    {
        if (current_state == ST_APERTO)
            waiting_progress = 0;
        else if (current_state == ST_CHIUSURA)
            current_state = ST_APERTURA;
        EXTI_clear(EXTI5);
    }
}

void TIM2_IRQHandler()
{
    GPIO_toggle(GPIOB, 0);
    switch (current_state)
    {
    case ST_APERTURA:
        if (opening_progress >= 100)
            current_state = ST_APERTO;
        else
            opening_progress += incremento_tc;
        //incrementa in base al valore adc in quanto portato in %, alla fine si ottiene 10sec
        break;
    case ST_APERTO:
        if (waiting_progress >= 100)
        {
            //incrementa in base al valore adc ogni 0,5 sec
            waiting_progress = 0;
            current_state = ST_CHIUSURA;
        }
        else
            waiting_progress += incremento_ta;
        break;
    case ST_CHIUSURA:
        if (opening_progress <= 0)
        {
            current_state = ST_CHIUSO;
            TIM_off(TIM2);
            TIM_set(TIM2, 0);
        }
        else
            opening_progress -= incremento_tc;
        break;
    }
    TIM_update_clear(TIM2);
}
