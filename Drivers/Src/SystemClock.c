/**
 ******************************************************************************
 * @file           : SystemClock.c
 * @author         : Daniel Peixoto
 * @brief          : Source file for System Clock configuration for the STM32F401CCU6 @84Mhz
 * 					 with 25Mhz HSE Crystal Oscillator
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#define	HSEON		(1U<<16)
#define HSERDY		(1U<<17)
#define PWREN		(1U<<28)
#define PRFTEN		(1U<<8)
#define DCEN		(1U<<10)
#define ICEN		(1<<9)




#include "stm32f401xc.h"


void SystemClocck(void){
	/***********************************************************/
	//1 - Enable the High Speed External Oscillator and wait for it to become ready
	RCC->CR	|= HSEON;
	while(!(RCC->CR & HSERDY)){}
	//2 - Set the Power Enable Clock and the Regulator Voltage Scaling Output Selection
	RCC->APB1ENR |= PWREN;
	PWR->CR |=  (1U<<14);		//Scale 2 for 60 MHz < fHCLK ≤ 84 MHz
	PWR->CR |=~ (1U<<15);
	//3 - Configure the Flash Prefetch and Latency settings
	FLASH->ACR |=  (1U<<0);		//5 WS (6 CPU cycles)
	FLASH->ACR &=~ (1U<<1);
	FLASH->ACR |=  (1U<<2);
	FLASH->ACR &=~ (1U<<3);
	FLASH->ACR |= PRFTEN;		//Prefetch enable
	FLASH->ACR |= ICEN;			//Instruction cache enable
	FLASH->ACR |= DCEN;			//Data cache enable
	//4 - Configure Prescalers  HCLK, PCLK1, PCLK2
	RCC->CFGR	&=~ (1U<<4);	//AHB Prescaler - Not divided
	RCC->CFGR	&=~ (1U<<5);	//AHB Prescaler - Not divided
	RCC->CFGR	&=~ (1U<<6);	//AHB Prescaler - Not divided
	RCC->CFGR	&=~ (1U<<7);	//AHB Prescaler - Not divided

	RCC->CFGR	&=~ (1U<<10);	//APB1 Prescaler - Divided by 2 - APB1 Max Frequency @42Mhz
	RCC->CFGR	&=~ (1U<<11);	//APB1 Prescaler - Divided by 2 - APB1 Max Frequency @42Mhz
	RCC->CFGR	|=  (1U<<12);	//APB1 Prescaler - Divided by 2 - APB1 Max Frequency @42Mhz

	RCC->CFGR	&=~ (1U<<13);	//APB2 Prescaler - Not divided
	RCC->CFGR	&=~ (1U<<14);	//APB2 Prescaler - Not divided
	RCC->CFGR	&=~ (1U<<15);	//APB2 Prescaler - Not divided




}






