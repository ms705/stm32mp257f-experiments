#include "gpio.h"


void gpio_select_func(uint64_t port_base_addr, uint32_t pin,
                                    uint32_t func) {
    GPIO_TypeDef* port = (GPIO_TypeDef*)port_base_addr;
    int idx = (pin < 8) ? 0 : 1;
    volatile uint32_t* reg = &port->AFR[idx];
    uint32_t shift = (pin < 8) ? (pin * 4) : ((pin - 8) * 4);

    *reg &= ~(GPIO_AFR_MASK << shift);
    *reg |= (func << shift);
}


void gpio_set_mode(uint64_t port_base_addr, uint32_t pin, uint32_t mode) {
  GPIO_TypeDef *port = (GPIO_TypeDef *)port_base_addr;
  uint32_t shift = pin * 2;
  port->MODER &= ~(GPIO_MODER_MASK << shift);
  port->MODER |= (mode << shift);
}
