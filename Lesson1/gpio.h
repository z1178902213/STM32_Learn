#define GPIO_BASE 0x40021400

#define GPIO_MODER *(unsigned int *)(GPIO_BASE+0x00)
#define GPIO_OTYPER *(unsigned int *)(GPIO_BASE+0x04)