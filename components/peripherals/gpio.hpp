#ifndef GPIO_HPP
#define GPIO_HPP

#include "driver/gpio.h"

auto constexpr SH1107_CS = gpio_num_t::GPIO_NUM_0;
auto constexpr SH1107_RST = gpio_num_t::GPIO_NUM_1;
auto constexpr SH1107_DC = gpio_num_t::GPIO_NUM_2;

void initialize_gpio() noexcept
{
    auto const sh1107_cs_config = gpio_config_t{.pin_bit_mask = 1U << SH1107_CS,
                                                .mode = GPIO_MODE_OUTPUT,
                                                .pull_up_en = GPIO_PULLUP_DISABLE,
                                                .pull_down_en = GPIO_PULLDOWN_DISABLE,
                                                .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&sh1107_cs_config);
}

void deinitialize_gpio() noexcept
{}

#endif // GPIO_HPP