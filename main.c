#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define LED_PIN 25
#define IRQ_PIN 22

void setup_led(void);
void irq_rx_complete(uint gpio, uint32_t events);

int main() {
    stdio_init_all();

    setup_led();

    gpio_set_irq_enabled_with_callback(IRQ_PIN, GPIO_IRQ_EDGE_RISE, true,
                                       &irq_rx_complete);

    gpio_put(LED_PIN, 1);

    while (1) {}

    return -1;
}

void setup_led(void) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // pull low initially
    gpio_put(LED_PIN, 0);
}

void irq_rx_complete(uint gpio, uint32_t events) {
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
    gpio_put(LED_PIN, 1);
    sleep_ms(500);

    gpio_put(LED_PIN, 0);
    sleep_ms(500);
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
}
