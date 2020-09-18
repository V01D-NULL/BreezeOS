#include <BreezeOS/power/VM/shutdown.h>

static void internal_VM_shutdown_func(struct VM_TYPE vm, int type)
{
    
    if (type == vm.BOCHS) {
        kprint("Shutdown Bochs", TRUE, TRUE, LOG);
        sleep(100);
        outw(0xB004, 0x2000);
    }
    
    else if (type == vm.QEMU)
    {
        kprint("Shutdown Qemu", TRUE, TRUE, LOG);
        sleep(100);
        outw(0x604, 0x2000);
    }
    
    else if (type == vm.VBOX)
    {
        kprint("Shutdown VirtualBox", TRUE, TRUE, LOG);
        sleep(100);
        outw(0x4004, 0x3400);
    }
}

int VM_shutdown(int VM)
{
    //Init struct, call VM_shutdown
    struct VM_TYPE vm;
    vm.BOCHS = __BOCHS__;
    vm.QEMU = __QEMU__;
    vm.VBOX = __VBOX__;
    
    switch (VM)
    {
        case __BOCHS__:
            kprint("Shutting down BOCHS.", TRUE, FALSE, LOG);
            #ifdef aesthetic
            sleep(300);
            #endif
            internal_VM_shutdown_func(vm, vm.BOCHS);
            break;
            
        case __QEMU__:
            kprint("Shutting down QEMU.", TRUE, FALSE, LOG);
            #ifdef aesthetic
            sleep(300);
            #endif
            internal_VM_shutdown_func(vm, vm.QEMU);
            break;
            
        case __VBOX__:
            kprint("Shutting down VBOX.", TRUE, FALSE, LOG);
            #ifdef aesthetic
            sleep(300);
            #endif
            internal_VM_shutdown_func(vm, vm.VBOX);
            break;
            
        default:
            break;
    }
    
    //Assert the OS'es dominance by yelling at user.
    kprint("Could not shutdown VM!", TRUE, FALSE, ERROR);
    
#ifdef DEBUG
    char str_num[digit_count(VM)+1]; 
    itoa(VM, str_num);
    kprint(strcat("Parameter OS passed was: ", str_num), TRUE, FALSE, WARN);
#endif    
}

