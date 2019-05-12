#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <psp2/kernel/processmgr.h>
#include <vita2d.h>
#include "touch.h"
#include <psp2/io/fcntl.h>
#include <psp2/power.h>

int fxTouch;
int fyTouch;

#define lerp(value, from_max, to_max) ((((value*10) * (to_max*10))/(from_max*10))/10)
#define PI 3.14159265

int main(int argc, char *argv[]) {
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, 1);
	
    vita2d_init();
    
    vita2d_texture *reset = vita2d_load_PNG_file("app0:/resources/reset.png");
    vita2d_texture *shutdown = vita2d_load_PNG_file("app0:/resources/shutdown.png");
    vita2d_texture *refresh_database = vita2d_load_PNG_file("app0:/resources/refresh_database.png");
    vita2d_texture *reset_database = vita2d_load_PNG_file("app0:/resources/reset_database.png");

    while (1) {
        vita2d_start_drawing();
        vita2d_clear_screen();

        /* Display background */
        vita2d_draw_texture(reset, 0, 0);
        vita2d_draw_texture(shutdown, 480, 0);
        vita2d_draw_texture(refresh_database, 0, 372);
        vita2d_draw_texture(reset_database, 480, 372);
        /*Finish displaying background*/

		vita2d_end_drawing();
        vita2d_swap_buffers();
        
        sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
        for (int i = 0; i < touch.reportNum; i++) {
            fxTouch = (lerp(touch.report[i].x, 1919, 960) - 50);
            fyTouch = (lerp(touch.report[i].y, 1087, 544) - 56.5);
            
            if(fxTouch < 480 && fyTouch < 327){
				scePowerRequestColdReset();
			}
			else if(fxTouch > 480 && fyTouch < 327){
				scePowerRequestStandby();
			}
			else if(fxTouch < 480 && fyTouch > 327){
				sceIoRemove("ux0:/id.dat");
				scePowerRequestColdReset();
			}
			else if(fxTouch > 480 && fyTouch > 327){
				sceIoRemove("ur0:/shell/db/app.db");
				scePowerRequestColdReset();
			}
		}
	}
}

