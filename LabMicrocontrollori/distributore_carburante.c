/* 
 * Main.c 
 * 
 *  Created on: 03 ott 2019 
 *      Author: danilo 
 */
#include "stm32_unict_lib.h"
#include <stdio.h>

enum{
    ST_SET,
    ST_START,
    ST_STOP
};
int state = ST_SET;

float current_value = 0;
float importo = 0;
int showImport = 0;
float incremento = 0.75;

int main(){
    DISPLAY_init();
    GPIO_init(GPIOB);
    GPIO_init(GPIOC);
    GPIO_config_output(GPIOB, 0);
    GPIO_config_output(GPIOC, 2);

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

    for (;;){
        char str[5];
        int stampa = 0;
        DISPLAY_dp(1, 1);
        switch (state){
            case ST_SET:
                GPIO_write(GPIOB, 0, 0);
                GPIO_write(GPIOC, 2, 0);    
                stampa = importo * 100;
                sprintf(str, "%04d", stampa);
                DISPLAY_puts(0, str);
                break;
            case ST_START:
                GPIO_write(GPIOB, 0, 0);
                showImport++;
                if (showImport > 1){
                    showImport = 0;
                    int stampa = current_value * 100;
                    sprintf(str, "%04d", stampa);
                    DISPLAY_puts(0, str);
                }
                if (current_value > importo){
                    state = ST_STOP;
                    showImport = 0;
                } else {
                    GPIO_toggle(GPIOC, 2);
                    current_value + = incremento;
                    delay_ms(500);
                }
                break;
            case ST_STOP:
                stampa = importo * 100;
                sprintf(str, "%04d", stampa);
                DISPLAY_puts(0, str);
                GPIO_write(GPIOB, 0, 1);
                GPIO_write(GPIOC, 2, 0);
                break;
            }
    }
}

void EXTI15_10_IRQHandler(void){
    if (EXTI_isset(EXTI10)){ //pushed X
        if (state == ST_SET){
            importo += 20;
        }
        EXTI_clear(EXTI10);
    }
}

void EXTI4_IRQHandler(void){
    if (EXTI_isset(EXTI4)){ //pushed Y
        if (state == ST_SET){
            importo += 5;
        }
        EXTI_clear(EXTI4);
    }
}

void EXTI9_5_IRQHandler(void){
    if (EXTI_isset(EXTI5)){ //pushed Z
        if (state == ST_SET){
            importo = 0;
        }
        EXTI_clear(EXTI5);
    }

    if (EXTI_isset(EXTI6)){ //pushed T
        if (state == ST_SET && importo != 0){
            current_value = 0;
            state = ST_START;
        }
        else if (state == ST_STOP){
            importo = 0;
            state = ST_SET;
        }
        EXTI_clear(EXTI6);
    }
}