#include<stdio.h>
#include"stm32_unict_lib.h"

int adc_val = 0;
int flash_on = 0;
int intensita = 0;
char str[5];
int main() {
  GPIO_init(GPIOB);
  GPIO_init(GPIOC);
  DISPLAY_init();

  GPIO_config_output(GPIOB, 0);

  GPIO_config_input(GPIOB, 10);
  GPIO_config_EXTI(GPIOB, EXTI10);
  EXTI_enable(EXTI10, FALLING_EDGE);

  TIM_init(TIM2);
  TIM_config_timebase(TIM2, 420, 1000);
  TIM_enable_irq(TIM2, IRQ_UPDATE);
  TIM_on(TIM2);
  
  ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
  ADC_channel_config(ADC1, GPIOC, 1, 11);
  ADC_on(ADC1);
  for (;;) {
    if (flash_on) {
      ADC_sample_channel(ADC1, 11);
      ADC_start(ADC1);
      while (!ADC_completed(ADC1)) {}
      adc_val = ADC_read(ADC1);
      intensita = adc_val * (800 - 50) / 255 + 50;
      sprintf(str, "%04d", intensita);
      DISPLAY_puts(0, str);
    } else
      DISPLAY_puts(0, " Off");
  }
}
void TIM2_IRQHandler(void) {
  if (TIM_update_check(TIM2)) {
    if (flash_on) {
      if (GPIO_read(GPIOB, 0)) {
        GPIO_write(GPIOB, 0, 0);
        TIM2 - > ARR = 800;
      } else {
        GPIO_write(GPIOB, 0, 1);
        TIM2 - > ARR = intensita;
      }
    } else
      GPIO_write(GPIOB, 0, 1);
    TIM_update_clear(TIM2);
  }
}
void EXTI15_10_IRQHandler(void) {
  if (EXTI_isset(EXTI10)) {
    flash_on = !flash_on;
    EXTI_clear(EXTI10);
  }
}