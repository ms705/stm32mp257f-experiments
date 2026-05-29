#include <stdint.h>
#include "base.h"

#ifndef __GPIO_H__
#define __GPIO_H__

typedef struct
{
  volatile uint32_t MODER;           /*!< GPIO mode register                                  Address offset: 0x000 */
  volatile uint32_t OTYPER;          /*!< GPIO output type register                           Address offset: 0x004 */
  volatile uint32_t OSPEEDR;         /*!< GPIO output speed register                          Address offset: 0x008 */
  volatile uint32_t PUPDR;           /*!< GPIO port pull-up/pull-down register                Address offset: 0x00C */
  volatile uint32_t IDR;             /*!< GPIO input data register                            Address offset: 0x010 */
  volatile uint32_t ODR;             /*!< GPIO output data register                           Address offset: 0x014 */
  volatile uint32_t BSRR;            /*!< GPIO bit set/reset register                         Address offset: 0x018 */
  volatile uint32_t LCKR;            /*!< GPIO configuration lock register                    Address offset: 0x01C */
  volatile uint32_t AFR[2];          /*!< GPIO alternate function  registers                  Address offset: 0x020 */
  volatile uint32_t BRR;             /*!< GPIO bit reset register                             Address offset: 0x028 */
  volatile uint32_t OR;              /*!< GPIO bit option register                            Address offset: 0x02C */
  volatile uint32_t SECCFGR;         /*!< GPIO secure configuration register                  Address offset: 0x030 */
  volatile uint32_t PRIVCFGR;        /*!< GPIO privileged configuration register              Address offset: 0x034 */
  volatile uint32_t RCFGLOCKR;       /*!< GPIO resource configuration lock register           Address offset: 0x038 */
       uint32_t RESERVED0;       /*!< Reserved                                            Address offset: 0x03C */
  volatile uint32_t DELAYRL;         /*!< GPIO delay low register                             Address offset: 0x040 */
  volatile uint32_t DELAYRH;         /*!< GPIO delay high register                            Address offset: 0x044 */
  volatile uint32_t ADVCFGRL;        /*!< GPIO PIO control low register                       Address offset: 0x048 */
  volatile uint32_t ADVCFGRH;        /*!< GPIO delay high register                            Address offset: 0x04C */

  volatile uint32_t CIDCFGR0;        /*!< GPIO CID configuration register for I/O pin 0       Address offset: 0x050 */
  volatile uint32_t SEMCR0;          /*!< GPIO semaphore control register for I/O pin 0       Address offset: 0x054 */
  volatile uint32_t CIDCFGR1;        /*!< GPIO CID configuration register for I/O pin 1       Address offset: 0x058 */
  volatile uint32_t SEMCR1;          /*!< GPIO semaphore control register for I/O pin 1       Address offset: 0x05C */
  volatile uint32_t CIDCFGR2;        /*!< GPIO CID configuration register for I/O pin 2       Address offset: 0x060 */
  volatile uint32_t SEMCR2;          /*!< GPIO semaphore control register for I/O pin 2       Address offset: 0x064 */
  volatile uint32_t CIDCFGR3;        /*!< GPIO CID configuration register for I/O pin 3       Address offset: 0x068 */
  volatile uint32_t SEMCR3;          /*!< GPIO semaphore control register for I/O pin 3       Address offset: 0x06C */
  volatile uint32_t CIDCFGR4;        /*!< GPIO CID configuration register for I/O pin 4       Address offset: 0x070 */
  volatile uint32_t SEMCR4;          /*!< GPIO semaphore control register for I/O pin 4       Address offset: 0x074 */
  volatile uint32_t CIDCFGR5;        /*!< GPIO CID configuration register for I/O pin 5       Address offset: 0x078 */
  volatile uint32_t SEMCR5;          /*!< GPIO semaphore control register for I/O pin 5       Address offset: 0x07C */
  volatile uint32_t CIDCFGR6;        /*!< GPIO CID configuration register for I/O pin 6       Address offset: 0x080 */
  volatile uint32_t SEMCR6;          /*!< GPIO semaphore control register for I/O pin 6       Address offset: 0x084 */
  volatile uint32_t CIDCFGR7;        /*!< GPIO CID configuration register for I/O pin 7       Address offset: 0x088 */
  volatile uint32_t SEMCR7;          /*!< GPIO semaphore control register for I/O pin 7       Address offset: 0x08C */
  volatile uint32_t CIDCFGR8;        /*!< GPIO CID configuration register for I/O pin 8       Address offset: 0x090 */
  volatile uint32_t SEMCR8;          /*!< GPIO semaphore control register for I/O pin 8       Address offset: 0x094 */
  volatile uint32_t CIDCFGR9;        /*!< GPIO CID configuration register for I/O pin 9       Address offset: 0x098 */
  volatile uint32_t SEMCR9;          /*!< GPIO semaphore control register for I/O pin 9       Address offset: 0x09C */
  volatile uint32_t CIDCFGR10;       /*!< GPIO CID configuration register for I/O pin 10      Address offset: 0x0A0 */
  volatile uint32_t SEMCR10;         /*!< GPIO semaphore control register for I/O pin 10      Address offset: 0x0A4 */
  volatile uint32_t CIDCFGR11;       /*!< GPIO CID configuration register for I/O pin 11      Address offset: 0x0A8 */
  volatile uint32_t SEMCR11;         /*!< GPIO semaphore control register for I/O pin 11      Address offset: 0x0AC */
  volatile uint32_t CIDCFGR12;       /*!< GPIO CID configuration register for I/O pin 12      Address offset: 0x0B0 */
  volatile uint32_t SEMCR12;         /*!< GPIO semaphore control register for I/O pin 12      Address offset: 0x0B4 */
  volatile uint32_t CIDCFGR13;       /*!< GPIO CID configuration register for I/O pin 13      Address offset: 0x0B8 */
  volatile uint32_t SEMCR13;         /*!< GPIO semaphore control register for I/O pin 13      Address offset: 0x0BC */
  volatile uint32_t CIDCFGR14;       /*!< GPIO CID configuration register for I/O pin 14      Address offset: 0x0C0 */
  volatile uint32_t SEMCR14;         /*!< GPIO semaphore control register for I/O pin 14      Address offset: 0x0C4 */
  volatile uint32_t CIDCFGR15;       /*!< GPIO CID configuration register for I/O pin 15      Address offset: 0x0C8 */
  volatile uint32_t SEMCR15;         /*!< GPIO semaphore control register for I/O pin 15      Address offset: 0x0CC */
       uint32_t RESERVED1[190];  /*!< Reserved                                            Address offset: 0x0D0-0x3C4 */
  volatile uint32_t HWCFGR10;        /*!< GPIO hardware configuration register 10             Address offset: 0x3C8 */
  volatile uint32_t HWCFGR9;         /*!< GPIO hardware configuration register 9              Address offset: 0x3CC */
  volatile uint32_t HWCFGR8;         /*!< GPIO hardware configuration register 8              Address offset: 0x3D0 */
  volatile uint32_t HWCFGR7;         /*!< GPIO hardware configuration register 7              Address offset: 0x3D4 */
  volatile uint32_t HWCFGR6;         /*!< GPIO hardware configuration register 6              Address offset: 0x3D8 */
  volatile uint32_t HWCFGR5;         /*!< GPIO hardware configuration register 5              Address offset: 0x3DC */
  volatile uint32_t HWCFGR4;         /*!< GPIO hardware configuration register 4              Address offset: 0x3E0 */
  volatile uint32_t HWCFGR3;         /*!< GPIO hardware configuration register 3              Address offset: 0x3E4 */
  volatile uint32_t HWCFGR2;         /*!< GPIO hardware configuration register 2              Address offset: 0x3E8 */
  volatile uint32_t HWCFGR1;         /*!< GPIO hardware configuration register 1              Address offset: 0x3EC */
  volatile uint32_t HWCFGR0;         /*!< GPIO hardware configuration register 0              Address offset: 0x3F0 */
  volatile uint32_t VERR;            /*!< GPIO version register                               Address offset: 0x3F4 */
  volatile uint32_t IPIDR;           /*!< GPIO identification register                        Address offset: 0x3F8 */
  volatile uint32_t SIDR;            /*!< GPIO size identification register                   Address offset: 0x3FC */
} GPIO_TypeDef;


#define GPIO_MODE_INPUT 0b00UL
#define GPIO_MODE_OUTPUT 0b0UL
#define GPIO_MODE_ALTERNATE 0b10UL
#define GPIO_MODE_ANALOG 0b11UL
#define GPIO_MODER_MASK 0b11UL

#define GPIO_AFR_MASK 0b1111UL

void gpio_select_func(uint64_t port_base_addr, uint32_t pin, uint32_t func);
void gpio_set_mode(uint64_t port_base_addr, uint32_t pin, uint32_t mode);


#endif
