#include "gpio.hpp"
#include "sh1107.hpp"
#include "spi.hpp"
#include "spi_device.hpp"
#include "usart.hpp"

namespace {

    void task(void*)
    {
        initialize_spi();
        initialize_gpio();
        initialize_usart();

        using namespace SH1107;
        using namespace Utility;

        auto spi_device = SPIDevice{sh1107_spi_device, SH1107_CS};

        auto sh1107 = SH1107::SH1107{std::move(spi_device), SH1107_DC, SH1107_RST};

        sh1107.clear_frame_buf();

        while (true) {
            sh1107.draw_string(0, 0, "DUPA");
            sh1107.display_frame_buf();
            sh1107.transmit_command_byte(0xAF);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        deinitialize_gpio();
        deinitialize_spi();
        deinitialize_usart();
    }

    auto static_task = StaticTask_t{};
    auto task_stack = std::array<std::uint8_t, 4096 * 3UL>{};

    void start_task() noexcept
    {
        xTaskCreateStaticPinnedToCore(&task,
                                      "oled task",
                                      task_stack.size(),
                                      nullptr,
                                      1UL,
                                      task_stack.data(),
                                      &static_task,
                                      1UL);
    }

}; // namespace

#ifdef __cplusplus
extern "C" {
#endif

void app_main(void)
{
    start_task();
}

#ifdef __cplusplus
}
#endif