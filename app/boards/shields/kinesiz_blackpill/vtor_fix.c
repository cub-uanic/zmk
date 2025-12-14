#include <zephyr/init.h>
#include <cmsis_core.h>
#include <zephyr/drivers/gpio.h>

#define APP_OFFSET 0x00010000UL
#define FLASH_BASE 0x08000000UL
#define SRAM_MARKER_ADDR 0x20000000UL

static int vtor_fix_init(void)
{
    /* метка "я дошёл сюда" */
    *(volatile uint32_t *)SRAM_MARKER_ADDR = 0xBEEF1000u;

    SCB->VTOR = FLASH_BASE + APP_OFFSET;
    __DSB();
    __ISB();

    /* метка "VTOR выставлен" */
    *(volatile uint32_t *)SRAM_MARKER_ADDR = 0xBEEF1001u;

    return 0;
}

SYS_INIT(vtor_fix_init, PRE_KERNEL_1, 0);
