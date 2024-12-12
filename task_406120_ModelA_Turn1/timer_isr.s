.globl timer_isr
.type timer_isr, @function

timer_isr:
    cli         ; Disable interrupts
    sti         ; Enable interrupts
    ; Add your interrupt handling code here
    ; For this example, we'll just return
    iret

.size timer_isr, . - timer_isr
