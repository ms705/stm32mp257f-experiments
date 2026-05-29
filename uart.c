#include "uart.h"

/*
 * Memory Barrier Helper for ARM Cortex-A35 (ARMv8-A).
 * * When writing to peripherals on the A35, we must use data synchronization
 * barriers (DSB) to ensure that register writes are completed before subsequent
 * instructions are executed, preventing out-of-order execution issues.
 */
static inline void memory_barrier(void) {
  __asm volatile("dsb st" : : : "memory");
}

void uart_init(USART_TypeDef *uart, uint32_t clock_freq_hz,
               uint32_t baud_rate) {
  /* 1. Disable the UART (UE=0) to allow configuration */
  uart->CR1 &= ~USART_CR1_UE;
  memory_barrier();

  /* 2. Configure Word Length to 8 bits (M0=0, M1=0) */
  uart->CR1 &= ~(USART_CR1_M0 | USART_CR1_M1);

  /* 3. Configure Parity to None (PCE=0 is default 0) */
  /* 4. Configure Stop Bits to 1 (STOP=00 in CR2, default is 0) */
  uart->CR2 &= ~(0x3 << 12);

  /* 5. Set Prescaler to 1 (divide by 1) if PRESC register exists */
  uart->PRESC = 0x0;

  /* 6. Configure Baud Rate
   * Formula for standard mode (oversampling by 16):
   * USARTDIV = Clock_Freq / Baud_Rate
   */
  if (baud_rate > 0) {
    uint32_t usartdiv = (clock_freq_hz + (baud_rate / 2)) / baud_rate;
    uart->BRR = usartdiv;
  }
  memory_barrier();

  /* 7. Enable FIFO (Optional but recommended for A35 performance) */
  //uart->CR1 |= USART_CR1_FIFOEN;

  /* 8. Enable Transmitter (TE) and Receiver (RE) */
  uart->CR1 |= (USART_CR1_TE | USART_CR1_RE);
  memory_barrier();

  /* 9. Enable UART (UE=1) */
  uart->CR1 |= USART_CR1_UE;
  memory_barrier();
}

void uart_putc(USART_TypeDef *uart, char c) {
  /* Wait until Transmit Data Register Empty (TXE) flag is set */
  /* TXE indicates data has moved from TDR to Shift Register */
  while (!(uart->ISR & USART_ISR_TXE)) {
    /* Busy wait */
  }

  /* Write character to Transmit Data Register */
  uart->TDR = (uint8_t)c;

  /* Ensure the write occurs before continuing */
  //memory_barrier();
}

char uart_getc(USART_TypeDef *uart) {
  /* Wait until Read Data Register Not Empty (RXNE) flag is set */
  while (!(uart->ISR & USART_ISR_RXNE)) {
    /* Busy wait */
  }

  /* Read character from Receive Data Register */
  char c = (char)(uart->RDR & 0xFF);
  return c;
}

void uart_puts(USART_TypeDef *uart, const char *str) {
  while (*str) {
    uart_putc(uart, *str++);
    /* If sending '\n', also send '\r' for terminal compatibility */
    if (*(str - 1) == '\n') {
      uart_putc(uart, '\r');
    }
  }

  /* Optional: Wait for Transmission Complete (TC) bit after string */
  while (!(uart->ISR & USART_ISR_TC));
}

int uart_has_data(USART_TypeDef *uart) {
  return (uart->ISR & USART_ISR_RXNE) ? 1 : 0;
}
