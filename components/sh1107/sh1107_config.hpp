#ifndef SH1107_CONFIG_HPP
#define SH1107_CONFIG_HPP

#include "sh1107_commands.hpp"
#include "sh1107_registers.hpp"
#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace SH1107 {

    enum struct DevAddress : std::uint8_t {};

    enum struct RegAddress : std::uint8_t {
        CONTRAST_CONTROL = 0b10000001,
        MULTIPLEX_RATIO = 0b10101000,
        DISPLAY_OFFSET = 0b11010011,
        DC_DC_CONTROL_MODE = 0b10101101,
        CLOCK_DIVIDE_OSC_FREQ = 0b11010101,
        CHARGE_PERIOD = 0b11011001,
        VCOM_DESELECT_LEVEL = 0b11011011,
        DISPLAY_START_LINE = 0b11011100,
    };

    enum struct Interface : std::uint8_t {
        MPU_8080 = 0b110,
        MPU_I2C = 0b010,
        MPU_6800 = 0b100,
        MPU_4W_SPI = 0b000,
        MPU_3W_SPI = 0b001,
    };

    enum struct ControlPad : std::uint8_t {
        DISPLAY_DATA = 0b01,
        COMMAND_DATA = 0b00,
    };

    struct Config {
        LOWER_COLUMN_ADDRESS lower_column_address{};
        HIGHER_COLUMN_ADDRESS higher_column_address{};
        PAGE_ADDRESS page_address{};
        DISPLAY_START_LINE display_start_line{};
        CONTRAST_CONTROL contrast_control{};
        NORMAL_REVERSE_DISPLAY normal_reverse_display{};
        MULTIPLEX_RATIO multiplex_ratio{};
        DISPLAY_OFFSET display_offset{};
        CLOCK_DIVIDE_OSC_FREQ clock_divide_osc_freq{};
        CHARGE_PERIOD charge_period{};
        VCOM_DESELECT_LEVEL vcom_deselect_level{};
        DC_DC_CONTROL_MODE dc_dc_control_mode{};
    };

}; // namespace SH1107

#undef PACKED

#endif // SH1107_CONFIG_HPP