#ifndef SPI_HPP
#define SPI_HPP

#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "sh1107_config.hpp"

auto sh1107_spi_device = spi_device_handle_t{};

auto constexpr SH1107_MOSI = gpio_num_t::GPIO_NUM_37; // Ensure this is valid for your ESP
auto constexpr SH1107_SCLK = gpio_num_t::GPIO_NUM_36; // Ensure this is valid for your ESP

void initialize_spi() noexcept
{
    auto spi_bus3_config = spi_bus_config_t{};
    spi_bus3_config.miso_io_num = -1;
    spi_bus3_config.mosi_io_num = SH1107_MOSI;
    spi_bus3_config.sclk_io_num = SH1107_SCLK;
    spi_bus3_config.quadhd_io_num = -1;
    spi_bus3_config.quadwp_io_num = -1;
    spi_bus3_config.max_transfer_sz = 4096;
    spi_bus3_config.flags = SPICOMMON_BUSFLAG_MASTER;

    ESP_ERROR_CHECK(spi_bus_initialize(SPI3_HOST, &spi_bus3_config, SPI_DMA_CH_AUTO));

    auto sh1107_spi_device_config = spi_device_interface_config_t{};
    sh1107_spi_device_config.spics_io_num = -1;
    sh1107_spi_device_config.clock_speed_hz = 1 * 1000 * 1000;
    sh1107_spi_device_config.mode = 3;         // SH1107 uses SPI Mode 3
    sh1107_spi_device_config.address_bits = 0; // No address phase
    sh1107_spi_device_config.command_bits = 0;
    sh1107_spi_device_config.dummy_bits = 0;
    sh1107_spi_device_config.flags = 0; // Remove HALFDUPLEX
    sh1107_spi_device_config.queue_size = 3;
    sh1107_spi_device_config.duty_cycle_pos = 128;

    ESP_ERROR_CHECK(spi_bus_add_device(SPI3_HOST, &sh1107_spi_device_config, &sh1107_spi_device));
}

void deinitialize_spi() noexcept
{
    spi_bus_remove_device(sh1107_spi_device);
}

#endif // SPI_HPP
