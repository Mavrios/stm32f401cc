#ifndef RCC_PRV_H_
#define RCC_PRV_H_

#define HSION_MSK		0x00000001
#define HSIRDY_MSK		0x00000002

#define NOTREADY		((u8) 0)

#define SW0				0
#define SW1				1
#define RSTSW_MSK		0xFFFFFFFC
#define SW_MSK			0x00000003
#define SWS_MSK			0x0000000C

#define SWS0			2
#define SWS1			3

#define HSEON_MSK		0x00010000

#define HSEBYP			18
#define HSERDY_MSK		0x00020000

#define PLLON_MSK		0x01000000
#define PLLRDY_MSK		0x02000000

#define CSSON			19

#define PLLN			6
#define PLLP			16
#define PLLSRC			22
#define PLLSRC_MSK		0x00400000
#define PLLQ			24


#define PLLM_MIN		2
#define PLLM_MAX		63

#define PLLN_MIN		192
#define PLLN_MAX		432

#define RCC_u16TIME_OUT		((u16) 500)
#endif
