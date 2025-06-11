#ifndef SH1107_SH1107_COMMANDS_H
#define SH1107_SH1107_COMMANDS_H

#include <stdint.h>

// struct SET_LOWER_COLUMN_ADDRESS {
//     uint8_t reserved : 4 = 0b0000;
//     uint8_t address : 4;
// };

// struct SH1107_CMD_SET_HIGHER_COLUMN_ADDRESS {
//     uint8_t reserved : 5 = 0b00010;
//     uint8_t address : 3;
// };

// struct SH1107_CMD_SET_MEMORY_ADDRESSING_MODE {
//     uint8_t reserved : 7 = 0b0010000;
//     uint8_t mode : 1;
// };

// struct SH1107_CMD_SET_SEGMENT_REMAP {
//     uint8_t reserved : 7 = 0b1010000;
//     uint8_t remap : 1;
// };

// struct SH1107_CMD_SET_ENTIRE_DISPLAY_ON_OFF {
//     uint8_t reserved : 7 = 0b1010010;
//     uint8_t on_off : 1;
// };

// struct SH1107_CMD_SET_NORMAL_REVERSE_DISPLAY {
//     uint8_t reserved : 7 = 0b1010011;
//     uint8_t display : 1;
// };

// struct SH1107_CMD_SET_DISPLAY_ON_OFF {
//     uint8_t reserved : 7 = 0b1010111;
//     uint8_t on_off : 1;
// };

// struct SH1107_CMD_SET_PAGE_ADDRESS {
//     uint8_t reserved : 4 = 0b1011;
//     uint8_t address : 4;
// };

// struct SH1107_CMD_SET_OUTPUT_SCAN_DIRECTION {
//     uint8_t reserved : 4 = 0b1100;
//     uint8_t direction : 1;
//     uint8_t : 3;
// };

// struct SH1107_CMD_READ_MODIFY_WRITE {
//     uint8_t reserved : 8 = 0b11100000;
// };

// struct SH1107_CMD_END {
//     uint8_t reserved : 8 = 0b11101110;
// };

// struct SH1107_CMD_NOP {
//     uint8_t reserved : 8 = 0b11100011;
// };

// struct SH1107_CMD_READ_ID {
//     uint8_t busy : 1;
//     uint8_t on_off : 1;
//     uint8_t id : 6;
// };

// struct SH1107_CMD_SET_CONTRAST_CONTROL {
//     uint8_t reserved : 8 = 0b10000001;
//     uint8_t contrast : 8;
// };

// struct SH1107_CMD_SET_MULTIPLEX_RATIO {
//     uint8_t reserved : 8 = 0b10101000;
//     uint8_t : 1;
//     uint8_t ratio : 7;
// };

// struct SH1107_CMD_SET_DISPLAY_OFFSET {
//     uint8_t reserved : 8 = 0b11010011;
//     uint8_t : 1;
//     uint8_t offset : 7;
// };

// struct SH1107_CMD_SET_DC_DC_SETTING {
//     uint16_t reserved : 12 = 0b101011011000;
//     uint8_t setting : 4;
// };

// struct SH1107_CMD_SET_DISPLAY_CLOCK {
//     uint8_t reserved : 8 = 0b11010101;
//     uint8_t osc_freq : 4;
//     uint8_t clock_divide : 4;
// };

// struct SH1107_CMD_SET_CHARGE_PERIOD {
//     uint8_t reserved : 8 = 0b11011001;
//     uint8_t discharge_period : 4;
//     uint8_t precharge_period : 4;
// };

// struct SH1107_CMD_SET_VCOM_DESELECT_LEVEL {
//     uint8_t reserved : 8 = 0b11011011;
//     uint8_t level : 8;
// };

// struct SH1107_CMD_SET_DISPLAY_START_LINE {
//     uint8_t reserved : 8 = 0b11011100;
//     uint8_t : 1;
//     uint8_t line : 7;
// };

typedef enum {
    SH1107_CMD_SET_LOWER_COLUMN_ADDRESS = 0b00000000,
    SH1107_CMD_SET_HIGHER_COLUMN_ADDRESS = 0b00010000,
    SH1107_CMD_SET_MEMORY_ADDRESSING_MODE = 0b00100000,
    SH1107_CMD_SET_SEGMENT_REMAP = 0b10100000,
    SH1107_CMD_SET_ENTIRE_DISPLAY_ON_OFF = 0b10100100,
    SH1107_CMD_SET_NORMAL_REVERSE_DISPLAY = 0b10100110,
    SH1107_CMD_SET_DISPLAY_ON_OFF = 0b10101110,
    SH1107_CMD_SET_PAGE_ADDRESS = 0b10110000,
    SH1107_CMD_SET_OUTPUT_SCAN_DIRECTION = 0b11000000,
    SH1107_CMD_READ_MODIFY_WRITE = 0b11100000,
    SH1107_CMD_END = 0b11101110,
    SH1107_CMD_NOP = 0b11100011,
    SH1107_CMD_READ_ID = 0b00000000,
    SH1107_CMD_SET_CONTRAST_CONTROL = 0b10000001,
    SH1107_CMD_SET_MULTIPLEX_RATIO = 0b10101000,
    SH1107_CMD_SET_DISPLAY_OFFSET = 0b11010011,
    SH1107_CMD_SET_DC_DC_SETTING_MSB = 0b00001010,
    SH1107_CMD_SET_DC_DC_SETTING_LSB = 011011000,
    SH1107_CMD_SET_DISPLAY_CLOCK = 0b11010101,
    SH1107_CMD_SET_CHARGE_PERIOD = 0b11011001,
    SH1107_CMD_SET_VCOM_DESELECT_LEVEL = 0b11011011,
    SH1107_CMD_SET_DISPLAY_START_LINE = 0b11011100,
} sh1107_cmd_t;

#endif // SH1107_SH1107_COMMANDS_H