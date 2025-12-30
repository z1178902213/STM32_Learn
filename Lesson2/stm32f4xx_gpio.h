#include "stm32f4xx.h"

#define    GPIO_PIN_0      ((unsigned short int)0x0001)
#define    GPIO_PIN_1      ((unsigned short int)0x0002)
#define    GPIO_PIN_2      ((unsigned short int)0x0004)
#define    GPIO_PIN_3      ((unsigned short int)0x0008)
#define    GPIO_PIN_4      ((unsigned short int)0x0010)
#define    GPIO_PIN_5      ((unsigned short int)0x0020)
#define    GPIO_PIN_6      ((unsigned short int)0x0040)
#define    GPIO_PIN_7      ((unsigned short int)0x0080)
#define    GPIO_PIN_8      ((unsigned short int)0x0100)
#define    GPIO_PIN_9      ((unsigned short int)0x0200)
#define    GPIO_PIN_10     ((unsigned short int)0x0400)
#define    GPIO_PIN_11     ((unsigned short int)0x0800)
#define    GPIO_PIN_12     ((unsigned short int)0x1000)
#define    GPIO_PIN_13     ((unsigned short int)0x2000)
#define    GPIO_PIN_14     ((unsigned short int)0x4000)
#define    GPIO_PIN_15     ((unsigned short int)0x8000)
#define    GPIO_PIN_ALL    ((unsigned short int)0xFFFF)


typedef enum {
	GPIO_MODER_INPUT = 0x00,
	GPIO_MODER_OUTPUT = 0x01,
	GPIO_MODER_MUX = 0x02,
	GPIO_MODER_MONI = 0x03
}GPIO_MODER_CONFIG;
	
typedef enum {
	GPIO_OTYUPER_PUSHPULL = 0x00,
	GPIO_OTYUPER_KAILOU = 0x01
}GPIO_OTYUPER_CONFIG;

typedef enum {
	GPIO_OSPEEDR_LOW = 0x00,
	GPIO_OSPEEDR_MIDDLE = 0x01,
	GPIO_OSPEEDR_HIGH = 0x02,
	GPIO_OSPEEDR_FAST = 0x03
}GPIO_OSPEEDR_CONFIG;

typedef enum {
	GPIO_PUPDR_NONE = 0x00,
	GPIO_PUPDR_UP = 0x01,
	GPIO_PUPDR_DOWN = 0x02,
	GPIO_PUPDR_RESERVED = 0x03
}GPIO_PUPDR_CONFIG;

typedef enum {
	GPIO_BSRRH_NONE = 0x00,
	GPIO_BSRRH_RESET = 0x01,
}GPIO_BSRRH_CONFIG;

typedef enum {
	GPIO_BSRRL_NONE = 0x00,
	GPIO_BSRRL_SET = 0x01,
}GPIO_BSRRL_CONFIG;

typedef struct{
	uint16_t GPIO_PIN;
	GPIO_MODER_CONFIG GPIO_MODE;
	GPIO_OTYUPER_CONFIG GPIO_TYPE;
	GPIO_OSPEEDR_CONFIG GPIO_SPEED;
	GPIO_PUPDR_CONFIG GPIO_PUPD;
	GPIO_BSRRL_CONFIG GPIO_BSRRL;
	GPIO_BSRRH_CONFIG GPIO_BSRRH;
}GPIO_INIT_CONFIG;

void gpio_init(GPIO_TYPE* gpiox, GPIO_INIT_CONFIG* gpio_config);
void reset_gpio(GPIO_TYPE* gpiox, uint16_t gpio_pin);
void set_gpio(GPIO_TYPE* gpiox, uint16_t gpio_pin);

