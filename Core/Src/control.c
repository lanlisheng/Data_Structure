/*
 * @Description: All modules about control
 * @Company: Optimus Prime, Inc.
 * @Author: Qijian Lu
 * @Date: 2020-10-14 16:58:43
 * @LastEditors: Qijian Lu
 * @LastEditTime: 2021-10-13 15:07:26
 */
#include "control.h"

/* Delay for 1 us */
void HAL_Delay_Us(__IO uint32_t Delay) {
  uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * Delay);
  while (delay--)
    ;
}
