#include <rtthread.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include "appmgr.h"
#include "statusbar.h"

void realtouch_ui_init(void)
{
    rt_device_t device;    
    struct rt_device_rect_info info;    

    device = rt_device_find("lcd");    
    if (device != RT_NULL)    
    {        
        info.width = 240; //800;        
        info.height = 320; //480;        
        /* set graphic resolution */        
        rt_device_control(device, RTGRAPHIC_CTRL_SET_MODE, &info);    
    }    

    /* re-set graphic device */    
    rtgui_graphic_set_device(device);       

    app_mgr_init();
    rt_thread_delay(10);

    calibration_init();
}
