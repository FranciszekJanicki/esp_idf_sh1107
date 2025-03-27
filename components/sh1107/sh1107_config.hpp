#ifndef SH1107_CONFIG_HPP
#define SH1107_CONFIG_HPP

#include "sh1107_commands.hpp"
#include "spi_device.hpp"
#include <cstdint>
#include <vector>

#define PACKED __attribute__((__packed__))

namespace SH1107 {

    enum struct DevAddress : std::uint8_t {};

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

    struct Config {};

    using SPIDevice = Utility::SPIDevice;

    struct Font {
        std::vector<std::vector<std::uint8_t>> buffer{};
        std::uint8_t width{};
        std::uint8_t height{};
    };

    auto constexpr SCREEN_WIDTH = 128U;
    auto constexpr BYTE_HEIGHT = 5U;
    auto constexpr BYTE_WIDTH = 7U;
    auto constexpr SCREEN_HEIGHT = 128U;
    auto constexpr FRAME_BUF_SIZE = SCREEN_WIDTH * (SCREEN_HEIGHT / 8);

}; // namespace SH1107

#undef PACKED

#endif // SH1107_CONFIG_HPP