#ifndef SH1107_CONFIG_HPP
#define SH1107_CONFIG_HPP

#include "sh1107_commands.hpp"
#include "spi_device.hpp"
#include <array>
#include <cstdint>
#include <vector>

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

    using SPIDevice = ESP32_Utility::SPIDevice;

    struct Font {
        std::vector<std::vector<std::uint8_t>> buffer{};
        std::uint8_t width{};
        std::uint8_t height{};
    };

    constexpr auto SCREEN_WIDTH = 128U;
    constexpr auto BYTE_HEIGHT = 5U;
    constexpr auto BYTE_WIDTH = 7U;
    constexpr auto SCREEN_HEIGHT = 128U;
    constexpr auto FRAME_BUF_SIZE = SCREEN_WIDTH * (SCREEN_HEIGHT / 8);

    template <std::uint8_t WIDTH, std::uint8_t HEIGHT>
    inline bool get_pixel(std::array<std::uint8_t, (WIDTH * HEIGHT) / 8> const& bitmap,
                          std::uint8_t const x,
                          std::uint8_t const y) noexcept
    {
        auto const byte = (y * WIDTH + x) / 8U;
        auto const bit = 7U - (x % 8U);

        return (bitmap[byte] & (1U << bit)) != 0;
    }

    template <std::uint8_t WIDTH, std::uint8_t HEIGHT>
    inline void set_pixel(std::array<std::uint8_t, (WIDTH * HEIGHT) / 8>& bitmap,
                          std::uint8_t const x,
                          std::uint8_t const y,
                          bool const pixel) noexcept
    {
        auto const byte = (y * WIDTH + x) / 8U;
        auto const bit = 7U - (x % 8U);

        if (pixel) {
            bitmap[byte] |= (1U << bit);
        } else {
            bitmap[byte] &= ~(1U << bit);
        }
    }

    template <std::uint8_t OLD_WIDTH, std::uint8_t OLD_HEIGHT, std::uint8_t NEW_WIDTH, std::uint8_t NEW_HEIGHT>
    inline std::array<std::uint8_t, (NEW_WIDTH * NEW_HEIGHT) / 8>
    resized_bitmap(std::array<std::uint8_t, (OLD_WIDTH * OLD_HEIGHT) / 8> const& bitmap) noexcept
    {
        auto resized_bitmap = std::array<std::uint8_t, (NEW_WIDTH * NEW_HEIGHT) / 8>{};

        for (auto new_y = 0U; new_y < NEW_HEIGHT; ++new_y) {
            for (auto new_x = 0U; new_x < NEW_WIDTH; ++new_x) {
                auto old_x = new_x * OLD_WIDTH / NEW_WIDTH;
                auto old_y = new_y * OLD_HEIGHT / NEW_HEIGHT;

                bool pixel = get_pixel<OLD_WIDTH, OLD_HEIGHT>(bitmap, old_x, old_y);
                set_pixel<NEW_WIDTH, NEW_HEIGHT>(resized_bitmap, new_x, new_y, pixel);
            }
        }

        return resized_bitmap;
    }

}; // namespace SH1107

#endif // SH1107_CONFIG_HPP