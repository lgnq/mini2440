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

/**
 * @addtogroup mini2440
 */

/*@{*/

#include <stdio.h>

#include <board.h>
#include <rtthread.h>

void rt_init_thread_entry(void *parameter)
{
    /* initialization RT-Thread Components
     *  finsh
     *  filesystems, such as fatfs, yaffs, uffs 
     *  GUI
     *  Lwip
     */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif
}

int rt_application_init(void)
{
    rt_thread_t init_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    return 0;
}

#include <finsh.h>
void fun(void)
{
    rt_kprintf("fun is performed by finsh.\r\n");
}
FINSH_FUNCTION_EXPORT(fun, fun desccription);

void fun_with_arg(int a)
{
    rt_kprintf("fun's arg is: %d\n", a);
}
FINSH_FUNCTION_EXPORT(fun_with_arg, funciton with a argument);
/*@}*/
