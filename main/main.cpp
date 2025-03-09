#include "gpio.hpp"
#include "sh1107.hpp"
#include "spi.hpp"
#include "spi_device.hpp"
#include "usart.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void app_main(void)
{
    initialize_spi();
    initialize_gpio();
    initialize_usart();

    using namespace SH1107;
    using namespace Utility;

    auto spi_device = SPIDevice{sh1107_spi_device, SH1107_CS};

    auto config = Config{};

    auto sh1107 = SH1107::SH1107{std::move(spi_device), config, SH1107_DC, SH1107_RST};

    while (true) {
    }

    deinitialize_gpio();
    deinitialize_spi();
    deinitialize_usart();
}

#ifdef __cplusplus
}
#endif