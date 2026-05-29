#include "uart.h"
#include "gpio.h"
#include "base.h"

/* #define GPIOA_BASE 0x44240000UL */
//#define RCC_BASE 0x44200000UL
#define RCC_GPIOACFGR (RCC_BASE + 0x52C)
#define RCC_GPIOGCFGR (RCC_BASE + 0x544)
#define RCC_UART5CFGR (RCC_BASE + 0x78C)
#define RCC_USART2CFGR (RCC_BASE + 0x784)

/* Register Offsets */
#define GPIO_MODER_OFFSET (0x00)
#define GPIO_ODR_OFFSET (0x14)

#define UART_USE_UART5

#ifdef UART_USE_UART5
// UART5_TX: PG9 (AF5)
// UART5_RX: PG10 (AF5)
#define UART_TX_PORT GPIOG_BASE
#define UART_RX_PORT GPIOG_BASE
#define UART_TX_PIN 9
#define UART_RX_PIN 10
#define UART_BASE UART5
#endif

#ifdef UART_USE_UART2
// USART2_TX: PA4
// USART2_RX: PA8
#define UART_TX_PORT GPIOA_BASE
#define UART_RX_PORT GPIOA_BASE
#define UART_TX_PIN 4
#define UART_RX_PIN 9 // TODO:  documentation is consistent if this is pin 8, 9, or 10
#define UART_BASE USART2
#endif


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

#define assert(cond)                                                           \
  do {                                                                         \
    if (!(cond)) {                                                             \
      while (1) {                                                              \
      }                                                                        \
    } \
} while(0)


int main(void) {
  /* 1. Enable GPIOA Clock (Bit 0 of AHB4ENSETR) */
  // unsigned int rcc_val = mmio_read32(RCC_BASE + RCC_MP_AHB4ENSETR);
  // mmio_write32(RCC_BASE + RCC_MP_AHB4ENSETR, rcc_val | (1 << 0));
  mmio_write32(RCC_GPIOACFGR, 0b10);
  mmio_write32(RCC_GPIOGCFGR, 0b10);
  mmio_write32(RCC_USART2CFGR, 0b110);
  mmio_write32(RCC_UART5CFGR, 0b110);

  /* 2. Configure GPIOA Pin 13 as Output (assuming LED is on PA13) */
  /* Clear bits 26-27, set bit 26 (01 = General Purpose Output) */
  // unsigned int mode = mmio_read32(GPIOA_BASE + GPIO_MODER_OFFSET);
  // mode &= ~(0x3 << (13 * 2));
  // mode |= (0x1 << (13 * 2));
  // mmio_write32(GPIOA_BASE + GPIO_MODER_OFFSET, mode);

  //GPIO_TypeDef *port_g = (GPIO_TypeDef *)GPIOG_BASE;
  gpio_set_mode(UART_TX_PORT, UART_TX_PIN, GPIO_MODE_ALTERNATE);
  gpio_set_mode(UART_RX_PORT, UART_RX_PIN, GPIO_MODE_ALTERNATE);
  gpio_select_func(UART_TX_PORT,  UART_TX_PIN, 5);
  gpio_select_func(UART_RX_PORT, UART_RX_PIN, 5);

  USART_TypeDef* uart = UART_BASE;
  uart_init(uart, 64000000, 115200);  // Peripheral clock is 64 MHz

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
