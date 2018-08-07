#include <psp2/ctrl.h>
int main(){
    SceCtrlData pad;
    while (1) {
    sceCtrlPeekBufferPositive(0, &pad, 1);
    if (pad.buttons & SCE_CTRL_RTRIGGER)
            scePowerRequestColdReset();
    if (pad.buttons & SCE_CTRL_LTRIGGER)
            scePowerRequestStandby();
    }
}
