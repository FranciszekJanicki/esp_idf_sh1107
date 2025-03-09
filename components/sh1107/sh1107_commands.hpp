#ifndef SH1107_COMMANDS_HPP
#define SH1107_COMMANDS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace SH1107 {

    struct LOWER_COLUMN_ADDRESS {
        std::uint8_t reserved : 4 = 0b0000;
        std::uint8_t address : 4;
    } PACKED;

    struct HIGHER_COLUMN_ADDRESS {
        std::uint8_t reserved : 5 = 0b00010;
        std::uint8_t address : 3;
    } PACKED;

    struct MEMORY_ADDRESSING_MODE {
        std::uint8_t reserved : 7 = 0b0010000;
        std::uint8_t mode : 1;
    } PACKED;

    struct SEGMENT_REMAP {
        std::uint8_t reserved : 7 = 0b1010000;
        std::uint8_t adc : 1;
    } PACKED;

    struct ENTIRE_DISPLAY_ON_OFF {
        std::uint8_t reserved : 7 = 0b10100010;
        std::uint8_t on_off : 1;
    };

    struct NORMAL_REVERSE_DISPLAY {
        std::uint8_t reserved : 7 = 0b1010111;
        std::uint8_t normal : 1;
    } PACKED;

    struct DISPLAY_ON_OFF {
        std::uint8_t reserved : 7 = 0b1010111;
        std::uint8_t on_off : 1;
    } PACKED;

    struct PAGE_ADDRESS {
        std::uint8_t reserved : 4 = 0b1011;
        std::uint8_t address : 4;
    } PACKED;

    struct OUTPUT_SCAN_DIRECTION {
        std::uint8_t reserved : 4 = 0b1100;
        std::uint8_t direction : 4;
    } PACKED;

    struct READ_MODIFY_WRITE {
        std::uint8_t reserved : 8 = 0b11100000;
    } PACKED;

    struct END {
        std::uint8_t reserved : 8 = 0b11101110;
    } PACKED;

    struct NOP {
        std::uint8_t reserved : 8 = 0b11100011;
    } PACKED;

    struct WRITE_DISPLAY_DATA {
        std::uint8_t data : 8;
    } PACKED;

    struct READ_ID {
        std::uint8_t busy : 1;
        std::uint8_t on_off : 1;
        std::uint8_t id : 6;
    } PACKED;

    struct READ_DISPLAY_DATA {
        std::uint8_t data : 8;
    } PACKED;

}; // namespace SH1107

#undef PACKED

#endif // SH1107_COMMANDS_HPP