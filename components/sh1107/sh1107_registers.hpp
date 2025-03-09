#ifndef SH1107_REGISTERS_HPP
#define SH1107_REGISTERS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace SH1107 {

    struct CONTRAST_CONTROL {
        std::uint8_t contrast : 8;
    } PACKED;

    struct MULTIPLEX_RATIO {
        std::uint8_t : 1;
        std::uint8_t ratio : 7;
    } PACKED;

    struct DISPLAY_OFFSET {
        std::uint8_t : 1;
        std::uint8_t offset : 7;
    } PACKED;

    struct DC_DC_CONTROL_MODE {
        std::uint8_t reserved : 4 = 0b1000;
        std::uint8_t mode : 4;
    } PACKED;

    struct CLOCK_DIVIDE_OSC_FREQ {
        std::uint8_t osc_freq : 4;
        std::uint8_t clock_divide : 4;
    } PACKED;

    struct CHARGE_PERIOD {
        std::uint8_t dis_charge_period : 4;
        std::uint8_t pre_charge_period : 4;
    } PACKED;

    struct VCOM_DESELECT_LEVEL {
        std::uint8_t level : 8;
    } PACKED;

    struct DISPLAY_START_LINE {
        std::uint8_t : 1;
        std::uint8_t line : 7;
    } PACKED;

}; // namespace SH1107

#undef PACKED

#endif // SH1107_REGISTERS_HPP