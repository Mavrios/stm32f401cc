#ifndef STM32F401CC_H_
#define STM32F401CC_H_

#define RCC_u32_BASE_ADDRESS         0x40023800

typedef struct
{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 Reserved1[2];
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 Reserved2[2];
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 Reserved3[2];
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 Reserved4[2];
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 Reserved5[2];
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 Reserved6[2];
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 Reserved7[2];
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 Reserved8;
	volatile u32 RCC_DCKCFGR;
}RCC_RegDef_t;

#define RCC		((RCC_RegDef_t *) RCC_u32_BASE_ADDRESS)

/***************************************************GPIO******************************************************/

#define GPIOA_u32_BASE_ADDRESS		0x40020000
#define GPIOB_u32_BASE_ADDRESS		0x40020400
#define GPIOC_u32_BASE_ADDRESS		0x40020800
#define GPIOD_u32_BASE_ADDRESS		0x40020C00
#define GPIOE_u32_BASE_ADDRESS		0x40021000
#define GPIOH_u32_BASE_ADDRESS		0x40021C00


typedef struct
{
	volatile u32 GPIOx_MODER;
	volatile u32 GPIOx_OTYPER;
	volatile u32 GPIOx_OSPEEDR;
	volatile u32 GPIOx_PUPDR;
	volatile u32 GPIOx_IDR;
	volatile u32 GPIOx_ODR;
	volatile u32 GPIOx_BSRR;
	volatile u32 GPIOx_LCKR;
	volatile u32 GPIOx_AFRL;
	volatile u32 GPIOx_AFRH;
}GPIO_RegDef_t;

#define GPIOA		((void *) GPIOA_u32_BASE_ADDRESS)
#define GPIOB		((void *) GPIOB_u32_BASE_ADDRESS)
#define GPIOC		((void *) GPIOC_u32_BASE_ADDRESS)
#define GPIOD		((void *) GPIOD_u32_BASE_ADDRESS)
#define GPIOE		((void *) GPIOE_u32_BASE_ADDRESS)
#define GPIOH		((void *) GPIOH_u32_BASE_ADDRESS)


#define NVIC_u32BASE_ADDRESS		0xE000E100


typedef struct{
	volatile u32 NVIC_ISER[8];
	volatile u32 Reserved0[24];
	volatile u32 NVIC_ICER[8];
	volatile u32 Reserved1[24];
	volatile u32 NVIC_ISPR[8];
	volatile u32 Reserved2[24];
	volatile u32 NVIC_ICPR[8];
	volatile u32 Reserved3[24];
	volatile u32 NVIC_IABR[8];
	volatile u32 Reserved4[56];
	volatile u8 NVIC_IPR[240];
	volatile u32 Reserved5[644];
	volatile u32 NVIC_STIR;
}NVIC_Registers_t;


#define NVIC		((NVIC_Registers_t *) NVIC_u32BASE_ADDRESS)


#define AISCR		*((volatile u32 *) 0xE000ED0C)



#define SYSTICK_u32_BASE_ADDRESS		0xE000E010

typedef struct{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;
}SYSTICK_Registers_t;

#define SYSTICK		((SYSTICK_Registers_t *) SYSTICK_u32_BASE_ADDRESS)
#endif
