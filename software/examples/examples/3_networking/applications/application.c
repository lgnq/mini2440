/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include <rtthread.h>

#include "platform.h"

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>

#include "dm9000.h"
#endif

#ifdef RT_USING_COMPONENTS_INIT
#include <components_init.h>
#endif

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_LWIP
    /* initialize eth interface */
    rt_hw_dm9000_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

    rt_platform_init();

    /* do some thing here. */
}

int rt_application_init(void)
{
    rt_thread_t init_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 2048, 8, 20);
#else
    init_thread = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 2048, 80, 20);
#endif

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    return 0;
}
