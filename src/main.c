#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <stdio.h>
#include "debugScreen.h"
#include <psp2/ctrl.h>
#define printf psvDebugScreenPrintf

int main(int argc, char *argv[]) {
    psvDebugScreenInit();
	printf("Press the left trigger to shut down or the right trigger to reboot. ");
    while (1) {
		SceCtrlData pad;
    	sceCtrlPeekBufferPositive(0, &pad, 1);
    	if (pad.buttons & SCE_CTRL_RTRIGGER)
            scePowerRequestColdReset();
    	if (pad.buttons & SCE_CTRL_LTRIGGER)
            scePowerRequestStandby();
    }
}