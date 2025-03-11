#ifndef GPIO_HPP
#define GPIO_HPP

#include "driver/gpio.h"

auto constexpr SH1107_CS = gpio_num_t::GPIO_NUM_4;
auto constexpr SH1107_RST = gpio_num_t::GPIO_NUM_5;
auto constexpr SH1107_DC = gpio_num_t::GPIO_NUM_6;

void initialize_gpio() noexcept
{
    auto const sh1107_gpio_config =
        gpio_config_t{.pin_bit_mask = (1U << SH1107_CS) | (1U << SH1107_DC) | (1U << SH1107_RST),
                      .mode = GPIO_MODE_OUTPUT,
                      .pull_up_en = GPIO_PULLUP_DISABLE,
                      .pull_down_en = GPIO_PULLDOWN_DISABLE,
                      .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&sh1107_gpio_config);
}

void deinitialize_gpio() noexcept
{}

#endif // GPIO_HPP