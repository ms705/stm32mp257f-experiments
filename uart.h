#ifndef STM32MP2_UART_H
#define STM32MP2_UART_H

#include <stdint.h>

/* * STM32MP257 UART Register Map Structure
 * Based on standard STM32 USART IP (V2/V3)
 */
typedef struct {
  volatile uint32_t CR1;   /* Control Register 1 */
  volatile uint32_t CR2;   /* Control Register 2 */
  volatile uint32_t CR3;   /* Control Register 3 */
  volatile uint32_t BRR;   /* Baud Rate Register */
  volatile uint32_t GTPR;  /* Guard Time and Prescaler Register */
  volatile uint32_t RTOR;  /* Receiver Timeout Register */
  volatile uint32_t RQR;   /* Request Register */
  volatile uint32_t ISR;   /* Interrupt and Status Register */
  volatile uint32_t ICR;   /* Interrupt Flag Clear Register */
  volatile uint32_t RDR;   /* Receive Data Register */
  volatile uint32_t TDR;   /* Transmit Data Register */
  volatile uint32_t PRESC; /* Prescaler Register */
} USART_TypeDef;

/* Memory Base Address for UART4 (Common Console on DK boards)
 * Note: Verify specific bus address in STM32MP2 reference manual.
 */
#define UART4_BASE 0x40100000UL
#define UART4 ((USART_TypeDef *)UART4_BASE)

/* Bit Definitions */
#define USART_CR1_UE (1 << 0)      /* USART Enable */
#define USART_CR1_RE (1 << 2)      /* Receiver Enable */
#define USART_CR1_TE (1 << 3)      /* Transmitter Enable */
#define USART_CR1_M0 (1 << 12)     /* Word length - Bit 0 */
#define USART_CR1_M1 (1 << 28)     /* Word length - Bit 1 */
#define USART_CR1_FIFOEN (1 << 29) /* FIFO Enable */

#define USART_ISR_TXE (1 << 7)  /* Transmit Data Register Empty */
#define USART_ISR_RXNE (1 << 5) /* Read Data Register Not Empty */
#define USART_ISR_TC (1 << 6)   /* Transmission Complete */

/* API Prototypes */

/**
 * @brief Initialize the UART peripheral.
 * @param uart Pointer to the USART instance (e.g., UART4).
 * @param clock_freq_hz The frequency of the clock feeding the UART peripheral.
 * @param baud_rate Desired baud rate (e.g., 115200).
 */
void uart_init(USART_TypeDef *uart, uint32_t clock_freq_hz, uint32_t baud_rate);

/**
 * @brief Send a single character.
 * @param uart Pointer to the USART instance.
 * @param c Character to send.
 */
void uart_putc(USART_TypeDef *uart, char c);

/**
 * @brief Receive a single character (blocking).
 * @param uart Pointer to the USART instance.
 * @return The received character.
 */
char uart_getc(USART_TypeDef *uart);

/**
 * @brief Send a null-terminated string.
 * @param uart Pointer to the USART instance.
 * @param str Pointer to the string.
 */
void uart_puts(USART_TypeDef *uart, const char *str);

/**
 * @brief Check if a character is available to read.
 * @param uart Pointer to the USART instance.
 * @return 1 if data available, 0 otherwise.
 */
int uart_has_data(USART_TypeDef *uart);

#endif  // STM32MP2_UART_H
