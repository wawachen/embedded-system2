# embedded-system2
for semester2

## review of semester1
- know how to use LPCX IDE to program the LPC1769
- architecture: superloop, timer, scheduler
- peripherals on board(like joystick, rotary encoder)
- adding functions into your project

## Task one
PCA9532 is a 16bit chip designded to control 16 LEDs. The smaller LPCXpresso board includes a **JTAG debugger** which allows real-time investigation of what is happening on the chip.

there are many debugger procedures:
- Step into (function) F5
- Step over (go to next line) F6
- Step return (function) F7

set a **break point** , double click the left panel, programs will stop before the breakpoint(not excute the selected line)

The most important thing is to review the difference between timer and scheduler
> 1. when setting timer, you need to set many parameters like TCR(time control register),MCR(match control register)
> How the Timer Works
The system clock updates at **25 megahertz**.
There are **four timers**.  For each timer, independently:
1.The timer control register is used to switch the timer on or off, and to reset the timer counter.

2.If the timer is active (on), the timer counter will increment – by default, this happens each time the system clock updates.

3.The prescale register divides this time, so the timer counter will increment more slowly than the system clock.  

4.There are up to four match registers.  When the timer counter reaches the value in one of the match registers, something will happen.

5.The match control register tells the processor what will happen when there is a match. 

This can be to:
a.Generate an interrupt (call an interrupt service routine or ISR).
b.Reset the timer (start the timer counter again at zero).
c.Stop the timer.

 in addition:
 - TCR <br>
 ![tcr](https://github.com/wawachen/embedded-system2/raw/wawachen-embeded_system/tcr.JPG)
 - MCR <br>
 ![mcr](https://github.com/wawachen/embedded-system2/raw/wawachen-embeded_system/mcr.JPG)
 
 
Example
 
1.Set the prescale register to (25000-1) – the timer counter will increment when the system clock reaches this value + 1, so it will update with 1 kilohertz frequency (25 MHz / 25000), i.e. once every millisecond.<br>
LPC_TIM0->PR = 25000 - 1;  so for each timer, the function will be updated in the frequency of  25MHz/(25000 * MR)

2.Set two match registers, one with the value 250, one with the value 750 (the -1 in each case is because counting starts from zero).<br>
LPC_TIM0->MR0 = 250 - 1;
LPC_TIM0->MR1 = 750 - 1;

3.Set up the match control register so that when MR0 is reached the ISR is called (page 505 of the manual – bit 0 of the MCR needs to be set to 1), and when MR1 is reached the ISR is called and the timer counter is reset (bits 3 and 4 of the MCR need to be set to 1).<br>
LPC_TIM0->MCR |= (1<<0 | 1<<3 | 1<<4);<br>
Enable interrupts, start the timer

About schduler, it is very simple. The first step is to build the schduler architecture. Iniatialize the scheduler and add Tasks. set each period for every function(containing in one task) <br>
finally we should edit the function in Tasks folder.<br>
-- package name 

    -- system folder
    -- main folder
    -- scheduler folder
    -- port folder
    -- tasks 

<br>requirments:
1.Investigate how the debugger works, as described in the seminar notes.

2.Replicate the behaviour in the demo project, but using the scheduler rather than the timer..

3.Create a project (using a scheduler, and re-using some of the code you wrote last term) so that the rotary encoder controls the PWM duty cycle for the green LEDs, and the joystick controls the PWM duty cycle for the red LEDs (or anything else you can think of - the main things are that you are confident in using the joystick and/or encoder for input, and the PCA9532 for output).



