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
    rt_components_init();
}

ALIGN(RT_ALIGN_SIZE)
static char thread1_stack[1024];
struct rt_thread thread1;
static void rt_thread_entry1(void *parameter)
{
    while (1)
    {
	//	rt_kprintf("thread1 run...\n");
        /* Insert delay */
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

ALIGN(RT_ALIGN_SIZE)
static char thread2_stack[1024];
struct rt_thread thread2;
static void rt_thread_entry2(void *parameter)
{
    while (1)
    {
	//	rt_kprintf("thread2 run...\n");
        /* Insert delay */
        rt_thread_delay(RT_TICK_PER_SECOND/2);
    }
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

    //------- init led1 thread
    rt_thread_init(&thread1,
                   "led1",
                   rt_thread_entry1,
                   RT_NULL,
                   &thread1_stack[0],
                   sizeof(thread1_stack),11,5);
    rt_thread_startup(&thread1);

    //------- init led2 thread
    rt_thread_init(&thread2,
                   "led2",
                   rt_thread_entry2,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),11,5);
    rt_thread_startup(&thread2);

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
