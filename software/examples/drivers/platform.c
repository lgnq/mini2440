#include <rtthread.h>
#include "board.h"
#include "platform.h"

#ifdef RT_USING_RTC
#include "rtc.h"
#endif /* RT_USING_RTC */

#ifdef RT_USING_SPI
static void rt_hw_spi_init(void)
{

}
#endif /* RT_USING_SPI */

void rt_platform_init(void)
{
#ifdef RT_USING_SPI
    rt_hw_spi_init();

#ifdef RT_USING_DFS
    w25qxx_init("flash0", "spi20");
#endif /* RT_USING_DFS */

#endif /* RT_USING_SPI */

#ifdef RT_USING_USB_HOST
    /* register stm32 usb host controller driver */
    rt_hw_susb_init();
#endif

#ifdef RT_USING_DFS
    /* initilize sd card */
#ifdef RT_USING_SDIO
    rt_mmcsd_core_init();
    rt_mmcsd_blk_init();
    mini2440_sdio_init();
    rt_thread_delay(RT_TICK_PER_SECOND);
#else
    rt_hw_sdcard_init();
#endif
#endif /* RT_USING_DFS */

#ifdef RT_USING_RTGUI
    /* initilize lcd controller */
    rt_hw_lcd_init();

    /* init touch panel */
    rtgui_touch_hw_init();	

    /* initilize key module */
    rt_hw_key_init();
#endif /* RT_USING_RTGUI */

#ifdef RT_USING_RTC
    rt_hw_rtc_init();
#endif /* RT_USING_RTC */

    rt_thread_delay(50);
    rt_device_init_all();
}

