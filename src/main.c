#include <stdio.h>
#include <psp2/ctrl.h>
#include <psp2/io/fcntl.h>
#include <psp2/power.h>
#include "debugScreen.h"
#define printf  psvDebugScreenPrintf

int main(int argc, const char *argv[]) {
    psvDebugScreenInit();
    printf("Press the left trigger to shut down or the right trigger to reboot.\n\n\n\nPress CROSS and SQUARE to update the database (keep icon layout).\n\n\n\nPress LEFT and UP on the d-pad to delete the database (lose icon layout).");
    while (1) {
		SceCtrlData pad;
    	sceCtrlPeekBufferPositive(0, &pad, 1);
    	
    	if (pad.buttons & SCE_CTRL_RTRIGGER)
			{
				scePowerRequestColdReset();
            }
    	if (pad.buttons & SCE_CTRL_LTRIGGER)
			{
				scePowerRequestStandby();
			}
        if (pad.buttons + SCE_CTRL_CROSS & SCE_CTRL_SQUARE)
			{
				sceIoRemove("ux0:/id.dat");
				scePowerRequestColdReset();
			}
		if (pad.buttons + SCE_CTRL_UP & SCE_CTRL_LEFT)
			{
				sceIoRemove("ur0:/shell/db/app.db");
				scePowerRequestColdReset();
			}
	}
}
