/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>

/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;

/* 线程1入口 */
static void thread1_entry(void *parameter)
{
    rt_uint32_t count = 0;

    for (; count < 5; count ++)
    {
        /* 打印线程1的输出 */
        rt_kprintf("thread1: count = %d\n", count);
        /* 执行yield后应该切换到thread2执行 */
        rt_thread_yield();
    }
}

/* 线程2入口 */
static void thread2_entry(void *parameter)
{
    rt_uint32_t count = 0;

    for (; count < 5; count ++)
    {
        /* 打印线程2的输出 */
        rt_thread_yield();
        rt_kprintf("thread2: count = %d\n", count);
    }
}

int rt_application_init(void)
{
    tid1 = rt_thread_create("thread",
        thread1_entry, RT_NULL, /* 线程入口是thread1_entry, 入口参数是RT_NULL */
        512, 6, 100);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* 创建线程2 */
    tid2 = rt_thread_create("thread",
        thread2_entry, RT_NULL, /* 线程入口是thread2_entry, 入口参数是RT_NULL */
        512, 6, 100);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    return 0;
}
