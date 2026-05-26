#include "uart.h"

/* * HYPOTHETICAL ADDRESSES for STM32MP2
 * (You MUST verify these in the Reference Manual RM0468)
 */
#define GPIOA_BASE 0x44240000UL
#define RCC_BASE 0x44200000UL
#define RCC_GPIOACFGR (RCC_BASE + 0x52C)
#define RCC_UART4CFGR (RCC_BASE + 0x788)

/* Register Offsets */
#define GPIO_MODER_OFFSET (0x00)
#define GPIO_ODR_OFFSET (0x14)

/* Simple mmio write helper */
static inline void mmio_write32(uint64_t addr, unsigned int val) {
  *(volatile unsigned int*)addr = val;
}

/* Simple mmio read helper */
static inline unsigned int mmio_read32(uint64_t addr) {
  return *(volatile unsigned int*)addr;
}

void delay_cycles(volatile unsigned long cycles) {
  while (cycles--) {
    __asm__ volatile("nop");
  }
}

int main(void) {
  /* 1. Enable GPIOA Clock (Bit 0 of AHB4ENSETR) */
  // unsigned int rcc_val = mmio_read32(RCC_BASE + RCC_MP_AHB4ENSETR);
  // mmio_write32(RCC_BASE + RCC_MP_AHB4ENSETR, rcc_val | (1 << 0));
  mmio_write32(RCC_GPIOACFGR, 0b10);
  mmio_write32(RCC_UART4CFGR, 0b10);

  /* 2. Configure GPIOA Pin 13 as Output (assuming LED is on PA13) */
  /* Clear bits 26-27, set bit 26 (01 = General Purpose Output) */
  // unsigned int mode = mmio_read32(GPIOA_BASE + GPIO_MODER_OFFSET);
  // mode &= ~(0x3 << (13 * 2));
  // mode |= (0x1 << (13 * 2));
  // mmio_write32(GPIOA_BASE + GPIO_MODER_OFFSET, mode);

  USART_TypeDef* uart = UART4;
  uart_init(uart, 64000000, 115200);  // Assuming 64 MHz clock

  /* 3. Blink Loop */
  while (1) {
    /* Toggle Bit 13 */
    unsigned int odr = mmio_read32(GPIOA_BASE + GPIO_ODR_OFFSET);
    mmio_write32(GPIOA_BASE + GPIO_ODR_OFFSET, odr ^ (1 << 13));
    uart_puts(uart, "Hello\r\n");
    delay_cycles(500000);
  }
  return 0;
}
