#!/usr/bin/env python

import chipwhisperer as cw
import time
import os
import signal
import sys
import subprocess
import atexit
from threading import Timer

def sigint_handler(sig, frame):
    print("Interruption detected. Shutting down the chip...")
    exit(0)

def sigint_handler2():
    print("Interruption detected. Shutting down the chip...")
    exit(0)

signal.signal(signal.SIGINT, sigint_handler)
signal.signal(signal.SIGTERM, sigint_handler)
atexit.register(sigint_handler2)

SCOPETYPE = 'OPENADC'
PLATFORM = 'CWLITEARM'
SS_VER = 'SS_VER_2_1'

try:
    if not scope.connectStatus:
        scope.con()
except NameError:
    scope = cw.scope()



print("INFO: Found ChipWhisperer😍")

# if "STM" in PLATFORM or PLATFORM == "CWLITEARM" or PLATFORM == "CWNANO":
#     prog = cw.programmers.STM32FProgrammer
# elif PLATFORM == "CW303" or PLATFORM == "CWLITEXMEGA":
#     prog = cw.programmers.XMEGAProgrammer
# elif "neorv32" in PLATFORM.lower():
#     prog = cw.programmers.NEORV32Programmer
# elif PLATFORM == "CW308_SAM4S":
#     prog = cw.programmers.SAM4SProgrammer
# else:
#     prog = None

scope.default_setup()

scope.vglitch_setup('lp', default_setup=False) # use both transistors
gc = cw.GlitchController(groups=["success", "reset", "normal"], parameters=["width", "offset", "ext_offset"])

# gc.set_range("width", 43.5, 47.8)
# gc.set_range("offset", -48, -10)
# gc.set_range("ext_offset", 7, 10)
# gc.set_range("ext_offset", 30, 45)
# scope.glitch.repeat = 11

scope.adc.timeout = 1000

scope.trigger.triggers = "tio4"

scope.io.hs2 = "glitch"

print(scope.io.glitch_hp)
scope.io.glitch_lp = False
scope.io.glitch_hp = True

#print("clkgen TCM enabled? = " + str(scope.LA.clkgen_enabled))
print("freq = " + str(scope.clock.clkgen_freq))
print("clkdiv = " + str(scope.clock.clkgen_div))
print("clkmul = " + str(scope.clock.clkgen_mul))
scope.clock.clkgen_freq = 3200000
scope.clock.clkgen_div = 36
scope.clock.clkgen_mul = 12
print("locked? = " + str(scope.clock.clkgen_locked))

scope.glitch.clk_src = "clkgen" 
scope.glitch.offset = 0
# scope.glitch.ext_offset = 15000 # 5V
scope.glitch.ext_offset = 0
scope.glitch.output = "enable_only"
scope.glitch.repeat = 8
scope.glitch.trigger_src = "ext_single"
# scope.glitch.width = 0

time.sleep(1)

nb_glitches = 1
while True:
    print(f"[*] Glitch {nb_glitches}")
    scope.arm()
    if scope.capture():
        print("Error: timeout for the chipwhisperer capture...")
        exit(1)
    #scope.io.vglitch_reset()
    nb_glitches += 1
