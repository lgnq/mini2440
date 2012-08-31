/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 * 2011-06-05     Bernard      modify for STM32F107 version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

/**
 * @addtogroup mini2440
 */

/*@{*/

extern int  rt_application_init(void);

#if defined(__CC_ARM)
extern int Image$$ER_ZI$$ZI$$Limit;
#define MINI2440_SRAM_BEGIN   (&Image$$ER_ZI$$ZI$$Limit)
#elif (defined (__GNUC__))
rt_uint8_t _irq_stack_start[1024];
rt_uint8_t _fiq_stack_start[1024];
rt_uint8_t _undefined_stack_start[512];
rt_uint8_t _abort_stack_start[512];
rt_uint8_t _svc_stack_start[4096] SECTION(".nobss");
extern unsigned char __bss_end;
#define MINI2440_SRAM_BEGIN   (&__bss_end)
#endif

#define MINI2440_SRAM_END     (0x33F00000)

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init tick */
    rt_system_tick_init();

    /* init kernel object */
    rt_system_object_init();

    /* init timer system */
    rt_system_timer_init();

    rt_system_heap_init((void *)MINI2440_SRAM_BEGIN, (void *)MINI2440_SRAM_END);

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init all device */
    rt_device_init_all();

    /* init application */
    rt_application_init();

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}

/*@}*/
