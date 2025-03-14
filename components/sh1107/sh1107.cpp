#include "sh1107.hpp"
#include "font5x7.hpp"
#include "utility.hpp"

namespace SH1107 {

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

    void SH1107::transmit_data(std::uint8_t const byte) const noexcept
    {
        this->select_control_pad(ControlPad::DISPLAY_DATA);
        this->spi_device_.transmit_byte(byte);
    }

    void SH1107::transmit_data(std::uint8_t const* const bytes, std::size_t const size) const noexcept
    {
        this->select_control_pad(ControlPad::DISPLAY_DATA);
        this->spi_device_.transmit_bytes(bytes, size);
    }

    void SH1107::transmit_command(std::uint8_t const byte) const noexcept
    {
        this->select_control_pad(ControlPad::COMMAND_DATA);
        this->spi_device_.transmit_byte(byte);
    }

    void SH1107::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->select_control_pad(ControlPad::COMMAND_DATA);
        this->spi_device_.transmit_byte(reg_address);
        this->spi_device_.transmit_byte(byte);
    }

    void SH1107::initialize(Config const& config) noexcept
    {
        this->device_reset();

        this->transmit_command(0xAE); // Display OFF
        this->transmit_command(0xD5); // Set Display Clock Divide Ratio
        this->transmit_command(0x80);
        this->transmit_command(0xA8); // Set Multiplex Ratio
        this->transmit_command(0x3F);
        this->transmit_command(0xD3); // Display Offset
        this->transmit_command(0x00);
        this->transmit_command(0x40); // Display Start Line
        this->transmit_command(0x8D); // Charge Pump
        this->transmit_command(0x14);
        this->transmit_command(0xAF); // Display ON

        // this->send_lower_column_address_command(config.lower_column_address);
        // this->send_higher_column_address_command(config.higher_column_address);
        // this->send_page_address_command(config.page_address);
        // this->set_display_start_line_register(config.display_start_line);
        // this->set_contrast_control_register(config.contrast_control);
        // this->send_normal_reverse_display_command(config.normal_reverse_display);
        // this->set_multiplex_ratio_register(config.multiplex_ratio);
        // this->set_display_offset_register(config.display_offset);
        // this->set_clock_divide_osc_freq_register(config.clock_divide_osc_freq);
        // this->set_charge_period_register(config.charge_period);
        // this->set_vcom_deselect_level_register(config.vcom_deselect_level);
        // this->set_dc_dc_control_mode_register(config.dc_dc_control_mode);

        this->initialized_ = true;
    }

    void SH1107::deinitialize() noexcept
    {
        this->device_reset();
        this->display_off();
        this->initialized_ = false;
    }

    void SH1107::device_reset() const noexcept
    {
        vTaskDelay(pdMS_TO_TICKS(100U));
        gpio_set_level(this->reset_pin_, 1U);
        vTaskDelay(pdMS_TO_TICKS(100U));
        gpio_set_level(this->reset_pin_, 0U);
        vTaskDelay(pdMS_TO_TICKS(100U));
        gpio_set_level(this->reset_pin_, 1U);
        vTaskDelay(pdMS_TO_TICKS(100U));
    }

    void SH1107::entire_display_on() const noexcept
    {
        this->send_entire_display_on_off_command(ENTIRE_DISPLAY_ON_OFF{.on_off = true});
    }

    void SH1107::entire_display_off() const noexcept
    {
        this->send_entire_display_on_off_command(ENTIRE_DISPLAY_ON_OFF{.on_off = false});
    }

    void SH1107::display_on() const noexcept
    {
        this->send_display_on_off_command(DISPLAY_ON_OFF{.on_off = true});
    }

    void SH1107::display_off() const noexcept
    {
        this->send_display_on_off_command(DISPLAY_ON_OFF{.on_off = false});
    }

    void SH1107::select_control_pad(ControlPad const control_pad) const noexcept
    {
        gpio_set_level(this->control_pin_, std::to_underlying(control_pad));
    }

    void SH1107::send_lower_column_address_command(LOWER_COLUMN_ADDRESS const lower_column_address) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(lower_column_address));
    }

    void SH1107::send_higher_column_address_command(HIGHER_COLUMN_ADDRESS const higher_column_address) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(higher_column_address));
    }

    void SH1107::send_memory_addressing_mode_command(MEMORY_ADDRESSING_MODE const memory_addressing_mode) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(memory_addressing_mode));
    }

    void SH1107::send_segment_remap_command(SEGMENT_REMAP const segment_remap) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(segment_remap));
    }

    void SH1107::send_entire_display_on_off_command(ENTIRE_DISPLAY_ON_OFF const entire_display_on_off) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(entire_display_on_off));
    }

    void SH1107::send_normal_reverse_display_command(NORMAL_REVERSE_DISPLAY const normal_reverse_display) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(normal_reverse_display));
    }

    void SH1107::send_display_on_off_command(DISPLAY_ON_OFF const display_on_off) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(display_on_off));
    }

    void SH1107::send_page_address_command(PAGE_ADDRESS const page_address) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(page_address));
    }

    void SH1107::send_output_scan_direction_command(OUTPUT_SCAN_DIRECTION const output_scan_direction) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(output_scan_direction));
    }

    void SH1107::send_read_modify_write_command(READ_MODIFY_WRITE const read_modify_write) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(read_modify_write));
    }

    void SH1107::send_end_command(END const end) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(end));
    }

    void SH1107::send_nop_command(NOP const nop) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(nop));
    }

    void SH1107::send_write_display_data_command(WRITE_DISPLAY_DATA const write_display_data) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(write_display_data));
    }

    void SH1107::send_read_id_command(READ_ID const read_id) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(read_id));
    }

    void SH1107::send_read_display_data_command(READ_DISPLAY_DATA const read_display_data) const noexcept
    {
        this->transmit_command(std::bit_cast<std::uint8_t>(read_display_data));
    }

    void SH1107::set_contrast_control_register(CONTRAST_CONTROL const contrast_control) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::CONTRAST_CONTROL),
                         std::bit_cast<std::uint8_t>(contrast_control));
    }

    void SH1107::set_multiplex_ratio_register(MULTIPLEX_RATIO const multiplex_ratio) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::MULTIPLEX_RATIO), std::bit_cast<std::uint8_t>(multiplex_ratio));
    }

    void SH1107::set_display_offset_register(DISPLAY_OFFSET const display_offset) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::DISPLAY_OFFSET), std::bit_cast<std::uint8_t>(display_offset));
    }

    void SH1107::set_dc_dc_control_mode_register(DC_DC_CONTROL_MODE const dc_dc_control_mode) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::DC_DC_CONTROL_MODE),
                         std::bit_cast<std::uint8_t>(dc_dc_control_mode));
    }

    void SH1107::set_clock_divide_osc_freq_register(CLOCK_DIVIDE_OSC_FREQ const display_divide_osc_freq) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::CLOCK_DIVIDE_OSC_FREQ),
                         std::bit_cast<std::uint8_t>(display_divide_osc_freq));
    }

    void SH1107::set_charge_period_register(CHARGE_PERIOD const charge_period) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::CHARGE_PERIOD), std::bit_cast<std::uint8_t>(charge_period));
    }

    void SH1107::set_vcom_deselect_level_register(VCOM_DESELECT_LEVEL const vcom_deselect_level) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::VCOM_DESELECT_LEVEL),
                         std::bit_cast<std::uint8_t>(vcom_deselect_level));
    }

    void SH1107::set_display_start_line_register(DISPLAY_START_LINE const display_start_line) const noexcept
    {
        this->write_byte(std::to_underlying(RegAddress::DISPLAY_START_LINE),
                         std::bit_cast<std::uint8_t>(display_start_line));
    }

    void SH1107::display_frame_buf()
    {
        if (!this->initialized_) {
            return;
        }

        // auto cmds = std::uint8_t;
        // cmds[0] = CMD_SET_X_ADDR;
        // cmds[1] = CMD_SET_Y_ADDR;

        this->send_lower_column_address_command(LOWER_COLUMN_ADDRESS{.address = 0});
        this->send_higher_column_address_command(HIGHER_COLUMN_ADDRESS{.address = 0});

        this->transmit_data(this->frame_buf, OLED_FRAME_BUF_SIZE);
    }

    void SH1107::clear_frame_buf() noexcept
    {
        if (!this->initialized_) {
            return;
        }

        std::memset(this->frame_buf, 0U, OLED_FRAME_BUF_SIZE);
    }

    void SH1107::set_pixel(std::uint8_t x, std::uint8_t y, bool color) noexcept
    {
        if (!this->initialized_) {
            return;
        }

        if (x >= OLED_WIDTH || y >= OLED_HEIGHT) {
            return;
        }

        if (color)
            this->frame_buf[x + (y / 8) * OLED_WIDTH] |= 1 << (y % 8);
        else
            this->frame_buf[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
    }

    void SH1107::draw_line(std::uint8_t x0, std::uint8_t y0, std::uint8_t x1, std::uint8_t y1, bool color) noexcept
    {
        if (!this->initialized_) {
            return;
        }

        auto dx = std::abs(x1 - x0);
        auto dy = -std::abs(y1 - y0);
        auto sx = x0 < x1 ? 1 : -1;
        auto sy = y0 < y1 ? 1 : -1;
        auto err = dx + dy;
        auto err2 = 0;

        while (1) {
            this->set_pixel(x0, y0, color);

            if (x0 == x1 && y0 == y1) {
                break;
            }

            err2 = 2 * err;

            if (err2 >= dy) {
                err += dy;
                x0 += sx;

                if (x0 > OLED_WIDTH) {
                    break;
                }
            }

            if (err2 <= dx) {
                err += dx;
                y0 += sy;

                if (y0 > OLED_HEIGHT) {
                    break;
                }
            }
        }
    }

    void SH1107::draw_circle(std::uint8_t x0, std::uint8_t y0, std::uint8_t r, bool color) noexcept
    {
        if (!this->initialized_) {
            return;
        }

        auto x = -r;
        auto y = 0;
        auto err = 2 - 2 * r;

        do {
            this->set_pixel(x0 - x, y0 + y, color);
            this->set_pixel(x0 - y, y0 - x, color);
            this->set_pixel(x0 + x, y0 - y, color);
            this->set_pixel(x0 + y, y0 + x, color);

            r = err;

            if (r > x) {
                ++x;
                err = err + x * 2 + 1;
            }

            if (r <= y) {
                ++y;
                err = err + y * 2 + 1;
            }
        } while (x < 0);
    }

    void SH1107::draw_bitmap(std::uint8_t x,
                             std::uint8_t y,
                             std::uint8_t w,
                             std::uint8_t h,
                             std::uint8_t* const bitmap,
                             bool color) noexcept
    {
        if (!this->initialized_) {
            return;
        }

        auto byte_width = (w + 7) / 8;
        auto b = 0;

        this->transmit_data(0xb0);
        for (auto j = 0; j < h; j++, ++y) {
            this->transmit_command(0x00 + (j & 0x0f));
            this->transmit_command(0x10 + (j >> 4));
            for (auto i = 0; i < w; i++) {
                if (i & 7) {
                    b <<= 1;
                } else {
                    b = bitmap[j * byte_width + i / 8];
                }

                if (b & (1U << 7U)) {
                    this->set_pixel(x + i, y, color);
                }
            }
        }
    }

    void SH1107::draw_char(std::uint8_t x, std::uint8_t y, char c) noexcept
    {
        if (!this->initialized_) {
            return;
        }

        if (c < 32 || c > 127) {
            return;
        }

        for (auto i = 0; i < FONT5X7_WIDTH; i++) {
            auto line = font5x7[c - FONT5X7_CHAR_CODE_OFFSET][i];

            for (auto j = 0; j < FONT5X7_HEIGHT; j++) {
                this->set_pixel(x + i, y + j, line & (1U << j));
            }
        }
    }

    void SH1107::draw_string(std::uint8_t x, std::uint8_t y, std::string const& s) noexcept
    {
        if (!this->initialized_) {
            return;
        }

        for (auto const c : s) {
            this->draw_char(x, y, c);
            x += FONT5X7_WIDTH + 1;

            if (x >= OLED_WIDTH) {
                break;
            }
        }
    }

    void SH1107::draw_string_formatted(std::uint8_t x, std::uint8_t y, std::string const& s, ...) noexcept
    {
        if (!this->initialized_) {
            return;
        }

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

}; // namespace SH1107