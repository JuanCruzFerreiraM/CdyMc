#include "../../include/mef.h"


void mef ();

void SEOS_Dispatch_Tasks() {
    if (mef_flag) {
        mef();
        mef_flag = 0;
    }
}


void mef () {
    switch (state)
    {
    case 0 :
        main_screen();
        break;
    case 1 :
        password();
        break;
    case 2 :
        wait_input();
        break;
    case 3:
        check();
        break;
    case 4:
        win();
        break;
    case 5:
        lose();
        break;
    default: 
        main_screen(); //this state should never be reach
        break;
    }
}