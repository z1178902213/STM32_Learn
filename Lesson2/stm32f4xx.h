#include<stdint.h>

/*RCCÕ‚…Ëª˘µÿ÷∑*/
#define RCC_BASE   ((unsigned int)(0x40020000 + 0x3800))
#define GPIOF_BASE ((unsigned int)(0x40021400))
#define GPIOF ((GPIO_TYPE*)GPIOF_BASE)

typedef struct{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint16_t BSRRL;
	uint16_t BSRRH;
	uint32_t LCKR;
	uint32_t AFRH;
	uint32_t AFRL;
}GPIO_TYPE;

typedef struct
{
	uint32_t CR;            /*!< RCC  ±÷”øÿ÷∆ºƒ¥Ê∆˜,				µÿ÷∑∆´“∆: 0x00 */
	uint32_t PLLCFGR;       /*!< RCC PLL≈‰÷√ºƒ¥Ê∆˜, 				µÿ÷∑∆´“∆: 0x04 */
	uint32_t CFGR;          /*!< RCC  ±÷”≈‰÷√ºƒ¥Ê∆˜,   		µÿ÷∑∆´“∆: 0x08 */
	uint32_t CIR;           /*!< RCC  ±÷”÷–∂œºƒ¥Ê∆˜,     		µÿ÷∑∆´“∆: 0x0C */
	uint32_t AHB1RSTR;      /*!< RCC AHB1 Õ‚…Ë∏¥Œªºƒ¥Ê∆˜,	µÿ÷∑∆´“∆: 0x10 */
	uint32_t AHB2RSTR;      /*!< RCC AHB2 Õ‚…Ë∏¥Œªºƒ¥Ê∆˜, 	µÿ÷∑∆´“∆: 0x14 */
	uint32_t AHB3RSTR;      /*!< RCC AHB3 Õ‚…Ë∏¥Œªºƒ¥Ê∆˜, 	µÿ÷∑∆´“∆: 0x18 */
	uint32_t RESERVED0;     /*!< ±£¡Ù, 										µÿ÷∑∆´“∆£∫0x1C */
	uint32_t APB1RSTR;      /*!< RCC APB1 Õ‚…Ë∏¥Œªºƒ¥Ê∆˜,	µÿ÷∑∆´“∆: 0x20 */
	uint32_t APB2RSTR;      /*!< RCC APB2 Õ‚…Ë∏¥Œªºƒ¥Ê∆˜,	µÿ÷∑∆´“∆: 0x24 */
	uint32_t RESERVED1[2];  /*!< ±£¡Ù, 										µÿ÷∑∆´“∆£∫0x28-0x2C*/
	uint32_t AHB1ENR;       /*!< RCC AHB1 Õ‚…Ë ±÷”ºƒ¥Ê∆˜,	µÿ÷∑∆´“∆: 0x30 */
	uint32_t AHB2ENR;       /*!< RCC AHB2 Õ‚…Ë ±÷”ºƒ¥Ê∆˜,	µÿ÷∑∆´“∆: 0x34 */
	uint32_t AHB3ENR;       /*!< RCC AHB3 Õ‚…Ë ±÷”ºƒ¥Ê∆˜,	µÿ÷∑∆´“∆: 0x38 */
} RCC_TypeDef;


#define RCC                 ((RCC_TypeDef *) RCC_BASE)
