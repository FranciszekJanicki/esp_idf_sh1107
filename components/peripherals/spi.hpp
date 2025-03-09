#ifndef SPI_HPP
#define SPI_HPP

#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "sh1107_config.hpp"

auto sh1107_spi_device = spi_device_handle_t{};

namespace {

    auto constexpr SH1107_MOSI = 0;
    auto constexpr SH1107_MISO = 1;
    auto constexpr SH1107_SCLK = 2;

}; // namespace

void initialize_spi() noexcept
{
    auto const spi_bus1_config = spi_bus_config_t{.mosi_io_num = SH1107_MOSI,
                                                  .miso_io_num = SH1107_MISO,
                                                  .sclk_io_num = SH1107_SCLK,
                                                  .quadwp_io_num = -1,
                                                  .quadhd_io_num = -1,
                                                  .data4_io_num = -1,
                                                  .data5_io_num = -1,
                                                  .data6_io_num = -1,
                                                  .data7_io_num = -1,
                                                  .data_io_default_level = 1,
                                                  .max_transfer_sz = 0,
                                                  .flags = 0U,
                                                  .isr_cpu_id = ESP_INTR_CPU_AFFINITY_1,
                                                  .intr_flags = 0U};

    spi_bus_initialize(SPI1_HOST, &spi_bus1_config, SPI_DMA_DISABLED);

    auto const sh1107_spi_device_config = spi_device_interface_config_t{.command_bits = 8U,
                                                                        .address_bits = 8U,
                                                                        .dummy_bits = 0U,
                                                                        .mode = 0U,
                                                                        .clock_source = SPI_CLK_SRC_DEFAULT,
                                                                        .duty_cycle_pos = 0U,
                                                                        .cs_ena_pretrans = 0U,
                                                                        .cs_ena_posttrans = 0U,
                                                                        .clock_speed_hz = 0U,
                                                                        .input_delay_ns = 0U,
                                                                        .spics_io_num = -1,
                                                                        .flags = 0U,
                                                                        .queue_size = 0,
                                                                        .pre_cb = nullptr,
                                                                        .post_cb = nullptr};

    spi_bus_add_device(SPI1_HOST, &sh1107_spi_device_config, &sh1107_spi_device);
}

void deinitialize_spi() noexcept
{
    spi_bus_remove_device(sh1107_spi_device);
}

#endif // SPI_HPP