#ifndef SH1107_HPP
#define SH1107_HPP

#include "driver/gpio.h"
#include "sh1107_commands.hpp"
#include "sh1107_config.hpp"
#include "spi_device.hpp"

namespace SH1107 {

    struct SH1107 {
    public:
        using SPIDevice = Utility::SPIDevice;

        SH1107() noexcept = default;

        SH1107(SPIDevice&& spi_device, gpio_num_t const control_pin, gpio_num_t const reset_pin) noexcept;
        SH1107(SPIDevice&& spi_device,
               Config const& config,
               gpio_num_t const control_pin,
               gpio_num_t const reset_pin) noexcept;

        SH1107(SH1107 const& other) = delete;
        SH1107(SH1107&& other) noexcept = default;

        SH1107& operator=(SH1107 const& other) = delete;
        SH1107& operator=(SH1107&& other) noexcept = default;

        ~SH1107() noexcept;

        void display_frame_buf() noexcept;

        void clear_frame_buf() noexcept;

        void set_pixel(std::uint8_t x, std::uint8_t y, bool color = true) noexcept;

        void draw_line(std::uint8_t x0, std::uint8_t y0, std::uint8_t x1, std::uint8_t y1, bool color = true) noexcept;

        void draw_circle(std::uint8_t x0, std::uint8_t y0, std::uint8_t r, bool color = true) noexcept;

        void draw_bitmap(std::uint8_t x,
                         std::uint8_t y,
                         std::uint8_t w,
                         std::uint8_t h,
                         std::uint8_t* const bitmap,
                         bool color = true) noexcept;

        void draw_char(std::uint8_t x, std::uint8_t y, char c) noexcept;

        void draw_string(std::uint8_t x, std::uint8_t y, std::string const& s) noexcept;

        void draw_string_formatted(std::uint8_t x, std::uint8_t y, std::string const& s, ...) noexcept;

        void transmit_data_byte(std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        void transmit_data_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept;

        void transmit_command_byte(std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        void transmit_command_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept;

        void initialize() noexcept;
        void initialize(Config const& config) noexcept;

        void deinitialize() noexcept;

        void device_reset() const noexcept;

        void entire_display_on() const noexcept;
        void entire_display_off() const noexcept;

        void display_on() const noexcept;
        void display_off() const noexcept;

        void select_control_pad(ControlPad const control_pad) const noexcept;

        void send_set_lower_column_address_command(std::uint8_t const address) const noexcept;
        void send_set_lower_column_address_command(SET_LOWER_COLUMN_ADDRESS const address) const noexcept;

        void send_set_higher_column_address_command(std::uint8_t const address) const noexcept;
        void send_set_higher_column_address_command(SET_HIGHER_COLUMN_ADDRESS const address) const noexcept;

        void send_set_memory_addressing_mode_command(bool const mode) const noexcept;
        void send_set_memory_addressing_mode_command(SET_MEMORY_ADDRESSING_MODE const mode) const noexcept;

        void send_set_segment_remap_command(bool const remap) const noexcept;
        void send_set_segment_remap_command(SET_SEGMENT_REMAP const remap) const noexcept;

        void send_set_entire_display_on_off_command(bool const on_off) const noexcept;
        void send_set_entire_display_on_off_command(SET_ENTIRE_DISPLAY_ON_OFF const on_off) const noexcept;

        void send_set_normal_reverse_display_command(bool const display) const noexcept;
        void send_set_normal_reverse_display_command(SET_NORMAL_REVERSE_DISPLAY const display) const noexcept;

        void send_set_display_on_off_command(bool const on_off) const noexcept;
        void send_set_display_on_off_command(SET_DISPLAY_ON_OFF const on_off) const noexcept;

        void send_set_page_address_command(std::uint8_t const address) const noexcept;
        void send_set_page_address_command(SET_PAGE_ADDRESS const address) const noexcept;

        void send_set_output_scan_direction_command(bool const direction) const noexcept;
        void send_set_output_scan_direction_command(SET_OUTPUT_SCAN_DIRECTION const direction) const noexcept;

        void send_read_modify_write_command() const noexcept;

        void send_end_command() const noexcept;

        void send_nop_command() const noexcept;

        void send_read_id_command() const noexcept;

        void send_set_contrast_control_command(std::uint8_t const contrast) const noexcept;
        void send_set_contrast_control_command(SET_CONTRAST_CONTROL const contrast) const noexcept;

        void send_set_multiplex_ratio_command(std::uint8_t const ratio) const noexcept;
        void send_set_multiplex_ratio_command(SET_MULTIPLEX_RATIO const ratio) const noexcept;

        void send_set_display_offset_command(std::uint8_t const offset) const noexcept;
        void send_set_display_offset_command(SET_DISPLAY_OFFSET const offset) const noexcept;

        void send_set_dc_dc_setting_command(std::uint8_t const setting) const noexcept;
        void send_set_dc_dc_setting_command(SET_DC_DC_SETTING const setting) const noexcept;

        void send_set_display_clock_command(std::uint8_t const osc_freq,
                                            std::uint8_t const clock_divide) const noexcept;
        void send_set_display_clock_command(SET_DISPLAY_CLOCK const clock) const noexcept;

        void send_set_charge_period_command(std::uint8_t const discharge, std::uint8_t const precharge) const noexcept;
        void send_set_charge_period_command(SET_CHARGE_PERIOD const charge_period) const noexcept;

        void send_set_vcom_deselect_level_command(std::uint8_t const level) const noexcept;
        void send_set_vcom_deselect_level_command(SET_VCOM_DESELECT_LEVEL const level) const noexcept;

        void send_set_display_start_line_command(std::uint8_t const line) const noexcept;
        void send_set_display_start_line_command(SET_DISPLAY_START_LINE const line) const noexcept;

        bool initialized_{false};

        gpio_num_t control_pin_{};
        gpio_num_t reset_pin_{};

        SPIDevice spi_device_{};

        std::array<std::uint8_t, FRAME_BUF_SIZE> frame_buf_{};
    };

    template <std::size_t SIZE>
    void SH1107::transmit_data_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        this->select_control_pad(ControlPad::DISPLAY_DATA);
        this->spi_device_.transmit_bytes(bytes);
    }

    template <std::size_t SIZE>
    void SH1107::transmit_command_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        this->select_control_pad(ControlPad::COMMAND_DATA);
        this->spi_device_.transmit_bytes(bytes);
    }

}; // namespace SH1107

#endif // SH1107_HPP