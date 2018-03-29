#include <stddef.h>
#include <stdint.h>

void *(**irqfuncs)(void *ctx);//array of pointers to functions for the IRQs
void *(**intfuncs)(void *ctx);//array of pointers to functions for the interrupts
void *(**intfuncs_err)(void *ctx, uint32_t errcode);//array of pointers to functions for the exceptions with error code

extern "C" void irqfunc(uint32_t irqnum, void *ctx)
{
    void *stack = NULL;
    if(PIC_isnormalIRQ(irqnum))
    {
        if(irqfuncs[irqfunc] != NULL)
        {
            stack = irqfuncs[irqnum](ctx);
        }
        PIC_EOI(irqnum);
        if(stack)
        {
            taskswitch(stack);
        }
    }
    else
    {
        PIC_EOI_spurious(irqnum);
    }
}

extern "C" void *irq_0_handler(void)
{
    volatile void *addr;
    asm(".intel_syntax noprefix");
    asm goto("jmp [endofISR]" ::: "memory" : endofISR); //Skip ISR code when calling C function (prevent the optimizer from removing it)
    asm volatile ("align 16" ::: "memory");
    startofISR:
    asm volatile ("pushal\n\tpushl\n\t ebp\n\tmovl ebp, esp\n\tcld" ::: "memory"); //Save registers, stack frame
    asm volatile (
        "pushm, ds \n\t" //Save segment registers
        "pushl, es \n\t"
        "movw cx, 16 \n\t" //Set segment registers for kernel
        "movw ds, cx \n\t"
        "movw es, cx \n\t"
        "pushl, ebp \n\t" //Push previous stack pointer
        "addl esp, 4 \n\t" //Add 4 to it to make it point to pushad structure
        "pushl ebx \n\t" //IRQ number parameter
        "call eax \n\t" //call IRQ function
        "addl esp, 8" //Pop the 2 parameters
        :: "a"(irqfunc), "b"((uint32_t) 0) : "memory");
        asm volatile("popl es\n\tpopl ds\n\tleave\n\tpopal\n\tiret" ::: "memory"); //Restore everything and iret
    endofISR:
    //return startofISR
    asm goto(
        ".intel_syntax noprefix"
        "mov eax, offset [startofISR]"
        "mov [ebx], eax"
        :: "b"(&addr) : "eax", "memory" : startofISR);
    return ((void *) addr);
}