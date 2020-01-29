#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"stm32_unict_lib.h"

enum {
  ST_RUN,
  ST_SETUP
};
int stato = ST_RUN;

float RottaEffettiva = 0;
float RottaDesiderata = 0;
float tempDesiderata;
int adc_val;
int turbolenza;
float Alettoni;

int main() {
  DISPLAY_init();
  GPIO_init(GPIOB);
  GPIO_init(GPIOC);
  TIM_init(TIM2);

  GPIO_config_output(GPIOC, 3);
  GPIO_config_output(GPIOB, 0);

  GPIO_config_input(GPIOB, 10);
  GPIO_config_EXTI(GPIOB, EXTI10);
  EXTI_enable(EXTI10, FALLING_EDGE);

  GPIO_config_input(GPIOB, 4);
  GPIO_config_EXTI(GPIOB, EXTI4);
  EXTI_enable(EXTI4, FALLING_EDGE);

  ADC_init(ADC1, ADC_RES_12, ADC_ALIGN_RIGHT);
  ADC_channel_config(ADC1, GPIOC, 1, 11);
  ADC_channel_config(ADC1, GPIOC, 1, 10);
  ADC_on(ADC1);

  TIM_config_timebase(TIM2, 42000, 20);
  TIM_enable_irq(TIM2, IRQ_UPDATE);
  TIM_on(TIM2);

  srand(time(NULL));

  for (;;) {
    switch (stato) {
      char str[5];
    case ST_RUN:
      sprintf(str, "%04d", (int) RottaEffettiva);
      DISPLAY_puts(0, str);
      ADC_sample_channel(ADC1, 10);
      ADC_start(ADC1);
      while (!ADC_completed(ADC1)) {}
      adc_val = ADC_read(ADC1);
      turbolenza = adc_val * (2) / 4095;
      RottaEffettiva += rand() % (turbolenza * 2 + 1) - turbolenza;
      break;
    case ST_SETUP:
      ADC_sample_channel(ADC1, 11);
      ADC_start(ADC1);
      while (!ADC_completed(ADC1)) {}
      adc_val = ADC_read(ADC1);
      tempDesiderata = adc_val * (180 + 180) / 4095 - 180;
      sprintf(str, "%04d", (int) tempDesiderata);
      DISPLAY_puts(0, str);
      delay_ms(500);
      break;
    }
  }
}

void EXTI15_10_IRQHandler() {
  if (EXTI_isset(EXTI10)) {
    if (stato == ST_RUN) {
      GPIO_write(GPIOB, 0, 1);
      stato = ST_SETUP;
    } else if (stato == ST_SETUP) {
      GPIO_write(GPIOB, 0, 0);
      stato = ST_RUN;
    }
  }
  EXTI_clear(EXTI10);
}

void EXTI4_IRQHandler() {
  if (EXTI_isset(EXTI4)) {
    if (stato == ST_SETUP) {
      RottaDesiderata = tempDesiderata;
      GPIO_write(GPIOB, 0, 0);
      stato = ST_RUN;
    }
  }
  EXTI_clear(EXTI4);
}

void TIM2_IRQHandler() {
  Alettoni = (RottaDesiderata - RottaEffettiva) * 0.08;
  if (Alettoni < -10)
    Alettoni = -10;
  else if (Alettoni > 10)
    Alettoni = 10;
  RottaEffettiva += Alettoni * 0.04;
  if (abs(RottaDesiderata - RottaEffettiva) < 2)
    GPIO_write(GPIOC, 3, 1);
  else
    GPIO_write(GPIOC, 3, 0);
  TIM_update_clear(TIM2);
}