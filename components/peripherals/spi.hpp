#ifndef SPI_HPP
#define SPI_HPP

#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "sh1107_config.hpp"

auto sh1107_spi_device = spi_device_handle_t{};

auto constexpr SH1107_MOSI = gpio_num_t::GPIO_NUM_37;
auto constexpr SH1107_SCLK = gpio_num_t::GPIO_NUM_36;

void initialize_spi() noexcept
{
    auto spi_bus3_config = spi_bus_config_t{};
    spi_bus3_config.miso_io_num = -1;
    spi_bus3_config.mosi_io_num = SH1107_MOSI;
    spi_bus3_config.sclk_io_num = SH1107_SCLK;
    spi_bus3_config.quadhd_io_num = -1;
    spi_bus3_config.quadwp_io_num = -1;

    ESP_ERROR_CHECK(spi_bus_initialize(SPI3_HOST, &spi_bus3_config, SPI_DMA_DISABLED));

    auto sh1107_spi_device_config = spi_device_interface_config_t{};
    sh1107_spi_device_config.spics_io_num = -1;
    sh1107_spi_device_config.clock_speed_hz = 4 * 1000 * 1000;
    sh1107_spi_device_config.mode = 3;
    sh1107_spi_device_config.address_bits = CHAR_BIT;
    sh1107_spi_device_config.command_bits = 0;
    sh1107_spi_device_config.flags = SPI_DEVICE_HALFDUPLEX;
    sh1107_spi_device_config.queue_size = 1;

    ESP_ERROR_CHECK(spi_bus_add_device(SPI3_HOST, &sh1107_spi_device_config, &sh1107_spi_device));
}

void deinitialize_spi() noexcept
{
    spi_bus_remove_device(sh1107_spi_device);
}

#endif // SPI_HPP