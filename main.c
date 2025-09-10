#include <stdint.h>

#define F_CPU 72000000UL
#define CYCLES_PER_LOOP 4 

#define PERIPH_BASE      0x40000000
#define APB2PERIPH_BASE  (PERIPH_BASE + 0x00010000)  // 0x40010000
#define AHBPERIPH_BASE   (PERIPH_BASE + 0x00020000)  // 0x40020000

#define RCC_BASE         (AHBPERIPH_BASE + 0x00001000)  // 0x40021000
#define GPIOC_BASE       (APB2PERIPH_BASE + 0x00001000) // 0x40011000


#define RCC_APB2ENR      (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOC_CRH        (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR        (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

#define RCC_APB2ENR_IOPCEN (1 << 4)

void delay_ms(unsigned int ms) {
    volatile unsigned int count;
    count = ms * (F_CPU / (1000 * CYCLES_PER_LOOP));
    while (count--) __asm__("nop");
}

int main(void) {
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOC_CRH &= ~(0xF << 20);  
    GPIOC_CRH |=  (0x1 << 20); 

    while (1) {
        GPIOC_ODR &= ~(1 << 13);  
        delay_ms(50);            

        GPIOC_ODR |=  (1 << 13);
        delay_ms(500);           
    }
}
