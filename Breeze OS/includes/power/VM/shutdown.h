#ifndef _VM_POWER_SHUTDOWN
#define _VM_POWER_SHUTDOWN

#include "../../drivers/PortIO/port.h"
#include "../../drivers/ScreenIO/screen.h"
#include "../../cpu/types.h"

//Const Integer's representing shutdown values for VM's
#define __BOCHS__ 0
#define __QEMU__ 1
#define __VBOX__ 2

struct VM_TYPE {
    int BOCHS;
    int QEMU;
    int VBOX;
};


int VM_shutdown(int VM);

#endif
