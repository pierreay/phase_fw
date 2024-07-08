# State of experiments

## setup

We finished developing the testbed to induce transient consumption on a GPIO and mimic the CPU activity within the digital domain of a microcontroller. The testbed is composed by a chipwhisperer (CW), a realtime oscilloscope and a target MCU, currently the STM32F103x.
The CW connects to one of the target's GPIOs, which are configured to continuously provide an active-high output with an internal pull-up. On requests, the CW produces rapid short-circuits over an external resistive load. The target MCU is also configured to output one of its internal clocks to another GPIO, allowing for further observation and measurements by the oscilloscope. So far, we've focused mainly on the measurement of the instantaneous jitter and amplitude variation during a short-circuit event or a specific CPU state.

We tested different MCU clock configurations :
- Internal RC OSC at 16MHz (with and without the use of the digital PLL)
- External CLOCK at 16MHz supplied by the STM-Link MCU (with and without the use of the digital PLL)
- For both internal and external, we also tested various PLL configurations, producing a final system clock ranging from 1 to 64 MHz
All of which tested with two different short-circuit loads :
- 1kOhms (~10 mA)
- Direct short to ground
We measured various clock sources :
- Digital PLL output
- Internal RC OSC
- External CLK
- System clock. The main clock supplied to the CPU and peripherals


Our measurements are conducted under various CPU states or external events :
- STALL state: firmware running in a while loop with UART polling and delays (still active with conditional branching execution).
- AES state: continuous AES rounds computation.
- SLEEP state: the sleep state is described as complete power off of the CPU, which seems to involve clock gating for maximum consumption reduction.
- GLITCH event: external GPIO short-circuits (using the chipwhisperer) with various resistive loads.

Due to the technical impracticability of triggering our measurement tools on the execution of a specific firmware instruction, the proposed CPU states are considered asynchronous w.r.t. the oscilloscope sampling. This implies that we cannot precisely observe the effects of instructions and thus conduct fine grained modeling. However, the chosen experimental methodology is not affected by this limitation and perfectly catches the CPU impact on the clock jitter. In the case of GLITCH events, we can perfectly synchronize the scope with low latency, which allows for precise observation and characterization of its effect on the clock signal.


## Measurements

- Oscilloscope: jitter measured as one clock period time on a trigger. Multiple period measurements are accumulated by mean + STD var. 
- SDR (not detailed here *yet*):

*NOTES ON POWER SUPPLY*

Regulation within the chip ensures a stable and fixed supply voltage for the 
digital section, taking as input the externally supplied power supply on the VDD pin.
The regulator is not bypassable, and we have no information of its type.

The General Purpose IOs directly take the input VDD voltage as a level reference, 
not the internally regulated ones (digital). Thus, this suggests that inducing a 
transient current flow through a GPIO will probably not perfectly reproduce 
side-effects internally caused by the CPU activity (two distinct power-supply domains).

From the power supply schematic in [STM32F103x datasheet], TODO


## Observations

1. Jitter w.r.t. consumption (under a single target config : 64 MHz system clock, active PLL, internal OSC)

Under normal conditions on a STALL state, we observed the nominal jitter of the target clock on the oscilloscope, which is the sum of the measurement uncertainties plus the target "natural" jitter.
We observed a clock jitter higher than the nominal value in the event of a GPIO GLITCH. Right after the occurrence of a glitch event, the clock period shifts by a few hundred picoseconds (15.625 ns nominal 64 MHz). Alongside a phase/period shift, the clock RMS amplitude also appears to be affected, varying by a few mV. This reminded us of the well-known and well-exploited amplitude modulation, but we cannot conclude on this as of now.

When playing with various short-circuit loads (from a few kOhms to zero ohms), the period shift seems proportional to the short-circuit load used and, thus, the current intensity. More precisely, we observed that the shift only occurs during the transient effect of a short-circuit (which is not instantaneous due to parasitic capacitors). 
We thus assume that the internal clock jitter is a direct function of the derivative of the chip consumption. This makes sense when considering the characteristic of a voltage regulator to accommodate a varying load gradually.

It was harder to conduct measurements with CPU states as we didn't have any meaningful time reference to conduct the measurements (scope trigger). As of now, we simply observed the apparent clock jitter with a trigger on the rising slope of the clock. Thanks to a dedicated built-in function, the scope visually accumulates a small set of clock periods subsequent to the trigger event. Work is being done to provide period measurement output with mean + STD dev computation in an automated manner.
Given this, our overall observations on the scope show an apparent increase in jitter magnitude when CPU is put in the AES state. 
Conversely, when the CPU is in SLEEP state, we denote an overall jitter significantly lower than the nominal one.

2. Jitter w.r.t. OSC / PLL circuits in use:

We found no clear dependency between the target jitter and the type of internal clock reference in use. Either with the internal oscillator or an external clock, the target exhibits the same jitter behavior under the previous experiments detailed above (0).
We also tried to compare the use of the internal PLL, leading to the same observation. However, disabling the PLL causes the system clock to drop from a maximum of 64 MHz to 8 MHz, making the comparison inconsistent. We thus cannot conclude on the PLL dependency as of now, especially given the observations done in point 3.

Most of our measurements were done on the target system clock. Still, we also directly observed the internal RC oscillator and PLL output, and we surprisingly observed that the jitter dependency was only apparent on the system clock.

3. Phase leak w.r.t. the target clock frequency

By playing with various PLL configurations to generate a system clock at various frequencies, we denoted a higher jitter amplitude with clocks at higher frequencies.

We are still unsure about those results, as we may have been misled by the scope scale, which has been tuned multiple times to visually accommodate different clock frequencies. To confirm this, we need automated jitter measurements extraction (WIP).


## Current conclusion

In the case of the STM32F103:
* The Jitter dependency on the consumption (and thus the CPU activity) is confirmed with some degree of confidence.
* This consumption dependency doesn't appear to be caused by the internal oscillator or PLL circuits. We found a reference in the side-channels literature that shows the exploitation of a phase dependency phenomenon that doesn't find its root cause in oscillating circuits. Also, we still have some concerns about the observations and decided to conduct more experiments.
* The jitter prevalence seems higher with a system clock set at higher frequencies.

