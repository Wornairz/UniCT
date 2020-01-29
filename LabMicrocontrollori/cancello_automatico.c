/* 
 * Main.c 
 * 
 *  Created on: 03 ott 2019 
 *      Author: danilo 
 */ 
#include "stm32_unict_lib.h" 
#include <stdio.h> 
enum { 
ST_CHIUSO, 
ST_APERTURA, 
ST_APERTO, 
ST_CHIUSURA 
}; 
int current_state = ST_CHIUSO; //stato 

int opening_progress = 0;	//variabile contatore apertura [0,100] 10sec 
int waiting_progress = 0;	//variabile contatore attesa [0,8]	4sec 

int main(){ 
    DISPLAY_init(); 
    GPIO_init(GPIOB); 
    TIM_init(TIM2); 

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
    
    TIM_config_timebase(TIM2, 42000, 1000); //timer 0,5s 
 
    //Abilito interrupt timer 
    TIM_enable_irq(TIM2, IRQ_UPDATE); 
    TIM_set(TIM2, 0); 
    
    for(;;){ 
        switch(current_state){ 
            case ST_CHIUSO: 
            GPIO_write(GPIOB, 0, 0); 
            DISPLAY_puts(0, "----"); 
            break; 
        default: 
            if(opening_progress >= 0 && opening_progress <= 100 ){ 
                if(opening_progress < 25)	 
                    DISPLAY_puts(0, "----"); 
                else if(opening_progress < 50) 
                    DISPLAY_puts(0, "--- "); 
                else if(opening_progress < 75) 
                    DISPLAY_puts(0, "--  "); 
                else if(opening_progress < 100) 
                    DISPLAY_puts(0, "-   "); 
                else if(opening_progress == 100) 
                    DISPLAY_puts(0, "    "); 
                break; 
            } 
        } 
    } 
} 

void EXTI15_10_IRQHandler(void){ 
    if(EXTI_isset(EXTI10)){                         //pushed X, simula bottone apertura telecomando cancello 
        if(current_state == ST_CHIUSO){	//premendo X avvio il timer di 0,5sec e passo nello stato di apertura 
            TIM_on(TIM2); 
            current_state = ST_APERTURA; 
        } 
    else if(current_state == ST_CHIUSURA){ 
        current_state = ST_APERTURA; 
        } 
       EXTI_clear(EXTI10); 
    } 
} 

void EXTI4_IRQHandler(void){ 
    if(EXTI_isset(EXTI4)){                          //pushed Y, simula bottone chiusura telecomando cancello 
        if(current_state == ST_APERTO){	//se nello stato di aperto, imposta il contatore direttamente al 
            waiting_progress = 8;	//valore finale, la gestione avviene poi nell'interrupt di TIM2 
        } 
        EXTI_clear(EXTI4); 
    } 
} 

void EXTI9_5_IRQHandler(void){ 
    if(EXTI_isset(EXTI5)){                          //pushed Z, simula la fotocellula del cancello 
        if(current_state == ST_APERTO)	      //resetta il tempo di attesa se rileva movimento 
            waiting_progress = 0; 
        else if(current_state == ST_CHIUSURA)	//altrimenti riapre il cancello se in stato di chiusura 
            current_state = ST_APERTURA; 
        EXTI_clear(EXTI5); 
    } 
} 

void TIM2_IRQHandler(){	//gestisce passaggio stati 
    GPIO_toggle(GPIOB, 0); 
    switch(current_state){ 
        case ST_APERTURA:	//controlla variabile contatore per ---> stato di aperto 
            if(opening_progress == 100) 
                current_state = ST_APERTO; 
            else 
                opening_progress += 5;	//incrementa di 5 in quanto portato in %, alla fine si ottiene 10sec 
        break; 
        case ST_APERTO: 
            if(waiting_progress == 8){	//incrementa 1 ogni 0,5 sec, con 8 si ottiene 4sec come da testo 
                waiting_progress = 0; 
                current_state = ST_CHIUSURA; 
            } 
            else 
                waiting_progress += 1; 
        break; 
        case ST_CHIUSURA: 
            if(opening_progress == 0){	//arresta e resetta il timer 
                current_state = ST_CHIUSO; 
                TIM_off(TIM2); 
                TIM_set(TIM2, 0); 
            } 
            else 
                opening_progress -= 5; 
        break; 
    } 
    TIM_update_clear(TIM2); 
} 