#include "sh1107.hpp"
#include "font5x7.hpp"
#include "utility.hpp"

namespace SH1107 {

    SH1107::SH1107(SPIDevice&& spi_device, gpio_num_t const control_pin, gpio_num_t const reset_pin) noexcept :
        control_pin_{control_pin}, reset_pin_{reset_pin}, spi_device_{std::forward<SPIDevice>(spi_device)}
    {
        this->initialize();
    }

    SH1107::SH1107(SPIDevice&& spi_device,
                   Config const& config,
                   gpio_num_t const control_pin,
                   gpio_num_t const reset_pin) noexcept :
        control_pin_{control_pin}, reset_pin_{reset_pin}, spi_device_{std::forward<SPIDevice>(spi_device)}
    {
        this->initialize(config);
    }

    SH1107::~SH1107() noexcept
    {
        this->deinitialize();
    }

    void SH1107::transmit_data_byte(std::uint8_t const byte) const noexcept
    {
        this->select_control_pad(ControlPad::DISPLAY_DATA);
        this->spi_device_.transmit_byte(byte);
    }

    void SH1107::transmit_command_byte(std::uint8_t const byte) const noexcept
    {
        this->select_control_pad(ControlPad::COMMAND_DATA);
        this->spi_device_.transmit_byte(byte);
    }

    void SH1107::initialize() noexcept
    {
        this->device_reset();

        this->transmit_command_byte(0xAE); // Display OFF
        this->transmit_command_byte(0xD5); // Set Display Clock Divide Ratio
        this->transmit_command_byte(0x80);
        this->transmit_command_byte(0xA8); // Set Multiplex Ratio
        this->transmit_command_byte(0x3F);
        this->transmit_command_byte(0xD3); // Display Offset
        this->transmit_command_byte(0x00);
        this->transmit_command_byte(0x40); // Display Start Line
        this->transmit_command_byte(0x8D); // Charge Pump
        this->transmit_command_byte(0x14);
        this->transmit_command_byte(0xAF); // Display ON

        this->initialized_ = true;
        vTaskDelay(pdMS_TO_TICKS(100UL));
    }

    void SH1107::initialize(Config const& config) noexcept
    {
        this->device_reset();

        this->initialized_ = true;
        vTaskDelay(pdMS_TO_TICKS(100UL));
    }

    void SH1107::deinitialize() noexcept
    {
        this->device_reset();
        this->display_off();
        this->initialized_ = false;
    }

    void SH1107::device_reset() const noexcept
    {
        gpio_set_level(this->reset_pin_, 0U);
        vTaskDelay(pdMS_TO_TICKS(100U));
        gpio_set_level(this->reset_pin_, 1U);
        vTaskDelay(pdMS_TO_TICKS(100U));
    }

    void SH1107::entire_display_on() const noexcept
    {
        this->send_set_entire_display_on_off_command(true);
    }

    void SH1107::entire_display_off() const noexcept
    {
        this->send_set_entire_display_on_off_command(false);
    }

    void SH1107::display_on() const noexcept
    {
        this->send_set_display_on_off_command(true);
    }

    void SH1107::display_off() const noexcept
    {
        this->send_set_display_on_off_command(false);
    }

    void SH1107::select_control_pad(ControlPad const control_pad) const noexcept
    {
        gpio_set_level(this->control_pin_, std::to_underlying(control_pad));
    }

    void SH1107::send_set_lower_column_address_command(std::uint8_t const address) const noexcept
    {
        this->send_set_lower_column_address_command(SET_LOWER_COLUMN_ADDRESS{.address = address});
    }

    void SH1107::send_set_lower_column_address_command(SET_LOWER_COLUMN_ADDRESS const address) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(address));
    }

    void SH1107::send_set_higher_column_address_command(std::uint8_t const address) const noexcept
    {
        this->send_set_higher_column_address_command(SET_HIGHER_COLUMN_ADDRESS{.address = address});
    }

    void SH1107::send_set_higher_column_address_command(SET_HIGHER_COLUMN_ADDRESS const address) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(address));
    }

    void SH1107::send_set_memory_addressing_mode_command(bool const mode) const noexcept
    {
        this->send_set_memory_addressing_mode_command(SET_MEMORY_ADDRESSING_MODE{.mode = mode});
    }

    void SH1107::send_set_memory_addressing_mode_command(SET_MEMORY_ADDRESSING_MODE const mode) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(mode));
    }

    void SH1107::send_set_segment_remap_command(bool const remap) const noexcept
    {
        this->send_set_segment_remap_command(SET_SEGMENT_REMAP{.remap = remap});
    }

    void SH1107::send_set_segment_remap_command(SET_SEGMENT_REMAP const remap) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_SEGMENT_REMAP)>>(remap));
    }

    void SH1107::send_set_entire_display_on_off_command(bool const on_off) const noexcept
    {
        this->send_set_entire_display_on_off_command(SET_ENTIRE_DISPLAY_ON_OFF{.on_off = on_off});
    }

    void SH1107::send_set_entire_display_on_off_command(SET_ENTIRE_DISPLAY_ON_OFF const on_off) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(on_off));
    }

    void SH1107::send_set_normal_reverse_display_command(bool const display) const noexcept
    {
        this->send_set_normal_reverse_display_command(SET_NORMAL_REVERSE_DISPLAY{.display = display});
    }

    void SH1107::send_set_normal_reverse_display_command(SET_NORMAL_REVERSE_DISPLAY const display) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(display));
    }

    void SH1107::send_set_display_on_off_command(bool const on_off) const noexcept
    {
        this->send_set_display_on_off_command(SET_DISPLAY_ON_OFF{.on_off = on_off});
    }

    void SH1107::send_set_display_on_off_command(SET_DISPLAY_ON_OFF const on_off) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(on_off));
    }

    void SH1107::send_set_page_address_command(std::uint8_t const address) const noexcept
    {
        this->send_set_page_address_command(SET_PAGE_ADDRESS{.address = address});
    }

    void SH1107::send_set_page_address_command(SET_PAGE_ADDRESS const address) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(address));
    }

    void SH1107::send_set_output_scan_direction_command(bool const direction) const noexcept
    {
        this->send_set_output_scan_direction_command(SET_OUTPUT_SCAN_DIRECTION{.direction = direction});
    }

    void SH1107::send_set_output_scan_direction_command(SET_OUTPUT_SCAN_DIRECTION const direction) const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(direction));
    }

    void SH1107::send_read_modify_write_command() const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(READ_MODIFY_WRITE{}));
    }

    void SH1107::send_end_command() const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(END{}));
    }

    void SH1107::send_nop_command() const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(NOP{}));
    }

    void SH1107::send_read_id_command() const noexcept
    {
        this->transmit_command_byte(std::bit_cast<std::uint8_t>(READ_ID{}));
    }

    void SH1107::send_set_contrast_control_command(std::uint8_t const contrast) const noexcept
    {
        this->send_set_contrast_control_command(SET_CONTRAST_CONTROL{.contrast = contrast});
    }

    void SH1107::send_set_contrast_control_command(SET_CONTRAST_CONTROL const contrast) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_CONTRAST_CONTROL)>>(contrast));
    }

    void SH1107::send_set_multiplex_ratio_command(std::uint8_t const ratio) const noexcept
    {
        this->send_set_multiplex_ratio_command(SET_MULTIPLEX_RATIO{.ratio = ratio});
    }

    void SH1107::send_set_multiplex_ratio_command(SET_MULTIPLEX_RATIO const ratio) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_MULTIPLEX_RATIO)>>(ratio));
    }

    void SH1107::send_set_display_offset_command(std::uint8_t const offset) const noexcept
    {
        this->send_set_display_offset_command(SET_DISPLAY_OFFSET{.offset = offset});
    }

    void SH1107::send_set_display_offset_command(SET_DISPLAY_OFFSET const offset) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_DISPLAY_OFFSET)>>(offset));
    }

    void SH1107::send_set_dc_dc_setting_command(std::uint8_t const setting) const noexcept
    {
        this->send_set_dc_dc_setting_command(SET_DC_DC_SETTING{.setting = setting});
    }

    void SH1107::send_set_dc_dc_setting_command(SET_DC_DC_SETTING const setting) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_DC_DC_SETTING)>>(setting));
    }

    void SH1107::send_set_display_clock_command(std::uint8_t const osc_freq,
                                                std::uint8_t const clock_divide) const noexcept
    {
        this->send_set_display_clock_command(SET_DISPLAY_CLOCK{.osc_freq = osc_freq, .clock_divide = clock_divide});
    }

    void SH1107::send_set_display_clock_command(SET_DISPLAY_CLOCK const clock) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_DISPLAY_CLOCK)>>(clock));
    }

    void SH1107::send_set_charge_period_command(std::uint8_t const discharge,
                                                std::uint8_t const precharge) const noexcept
    {
        this->send_set_charge_period_command(
            SET_CHARGE_PERIOD{.discharge_period = discharge, .precharge_period = precharge});
    }

    void SH1107::send_set_charge_period_command(SET_CHARGE_PERIOD const charge_period) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_CHARGE_PERIOD)>>(charge_period));
    }

    void SH1107::send_set_vcom_deselect_level_command(std::uint8_t const level) const noexcept
    {
        this->send_set_vcom_deselect_level_command(SET_VCOM_DESELECT_LEVEL{.level = level});
    }

    void SH1107::send_set_vcom_deselect_level_command(SET_VCOM_DESELECT_LEVEL const level) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_VCOM_DESELECT_LEVEL)>>(level));
    }

    void SH1107::send_set_display_start_line_command(std::uint8_t const line) const noexcept
    {
        this->send_set_display_start_line_command(SET_DISPLAY_START_LINE{.line = line});
    }

    void SH1107::send_set_display_start_line_command(SET_DISPLAY_START_LINE const line) const noexcept
    {
        this->transmit_command_bytes(std::bit_cast<std::array<std::uint8_t, sizeof(SET_DISPLAY_START_LINE)>>(line));
    }

    void SH1107::set_pixel(std::uint8_t x, std::uint8_t y, bool color) noexcept
    {
        if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
            return;
        }

        std::size_t byte_index = (y / 8) * SCREEN_WIDTH + x;
        std::uint8_t bit_mask = 1 << (y % 8);

        if (color) {
            frame_buf_[byte_index] |= bit_mask;
        } else {
            frame_buf_[byte_index] &= ~bit_mask;
        }
    }

    void SH1107::draw_line(std::uint8_t x0, std::uint8_t y0, std::uint8_t x1, std::uint8_t y1, bool color) noexcept
    {
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = dx + dy, e2;

        while (true) {
            set_pixel(x0, y0, color);
            if (x0 == x1 && y0 == y1)
                break;
            e2 = 2 * err;
            if (e2 >= dy) {
                err += dy;
                x0 += sx;
            }
            if (e2 <= dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

    void SH1107::draw_circle(std::uint8_t x0, std::uint8_t y0, std::uint8_t r, bool color) noexcept
    {
        int x = r, y = 0, err = 1 - x;
        while (x >= y) {
            set_pixel(x0 + x, y0 + y, color);
            set_pixel(x0 + y, y0 + x, color);
            set_pixel(x0 - y, y0 + x, color);
            set_pixel(x0 - x, y0 + y, color);
            set_pixel(x0 - x, y0 - y, color);
            set_pixel(x0 - y, y0 - x, color);
            set_pixel(x0 + y, y0 - x, color);
            set_pixel(x0 + x, y0 - y, color);
            y++;
            if (err < 0) {
                err += 2 * y + 1;
            } else {
                x--;
                err += 2 * (y - x) + 1;
            }
        }
    }

    void SH1107::draw_bitmap(std::uint8_t x,
                             std::uint8_t y,
                             std::uint8_t w,
                             std::uint8_t h,
                             std::uint8_t* bitmap,
                             bool color) noexcept
    {
        for (std::uint8_t j = 0; j < h; j++) {
            for (std::uint8_t i = 0; i < w; i++) {
                std::uint8_t byte = bitmap[j * ((w + 7) / 8) + (i / 8)];
                if (byte & (1 << (7 - (i % 8)))) {
                    set_pixel(x + i, y + j, color);
                }
            }
        }
    }

    void SH1107::draw_char(std::uint8_t x, std::uint8_t y, char c) noexcept
    {
        if (c < 32 || c > 127)
            return;

        for (std::uint8_t i = 0; i < FONT5X7_WIDTH; i++) {
            std::uint8_t line = font5x7[c - 32][i];
            for (std::uint8_t j = 0; j < FONT5X7_HEIGHT; j++) {
                set_pixel(x + i, y + j, line & (1 << j));
            }
        }
    }

    void SH1107::draw_string(std::uint8_t x, std::uint8_t y, std::string const& s) noexcept
    {
        for (char c : s) {
            draw_char(x, y, c);
            x += FONT5X7_WIDTH + 1;
            if (x >= SCREEN_WIDTH)
                break;
        }
    }

    void SH1107::draw_string_formatted(std::uint8_t x, std::uint8_t y, std::string const& s, ...) noexcept
    {
        va_list args;
        va_start(args, s);

        size_t size = vsnprintf(nullptr, 0, s.c_str(), args) + 1;
        if (size <= 0) {
            return;
        }

        std::string buf;
        buf.reserve(size);
        vsnprintf(buf.data(), size, s.c_str(), args);

        va_end(args);

        std::string formatted_string = buf.substr(0U, size - 1);
        this->draw_string(x, y, formatted_string);
    }

    void SH1107::display_frame_buf()
    {
        for (std::uint8_t page = 0; page < (SCREEN_HEIGHT / 8); page++) {
            this->transmit_command_byte(0xB0 | page);
            this->transmit_command_byte(0x00);
            this->transmit_command_byte(0x10);

            auto bytes = std::array<std::uint8_t, SCREEN_WIDTH>{};
            std::memcpy(bytes.data(), frame_buf_.data() + page * SCREEN_WIDTH, SCREEN_WIDTH);
            this->transmit_data_bytes(bytes);
        }
    }

    void SH1107::clear_frame_buf() noexcept
    {
        std::fill(frame_buf_.begin(), frame_buf_.end(), 0);
    }

}; // namespace SH1107