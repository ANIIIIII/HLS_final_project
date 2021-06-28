import sys
from time import time
from pynq import Overlay
from pynq import allocate
from __future__ import print_function

ROOT = '/home/xilinx/IPBitFile'
PATH = ROOT+'/design_1.bit'

ol = Overlay(PATH)
encIP = ol.encrypt_0

# contrl signal
CONTROL = 0x0
AP_START = 0x01
AP_DONE = 0x02
AP_IDLE = 0x04
AP_READY = 0x08

# i/O port
KEY_V_1 = 0x10
KEY_V_2 = 0x14
KEY_V_3 = 0x18
KEY_V_4 = 0x1C

P_V_I_1 = 0x24
P_V_I_2 = 0x28

P_V_O_1 = 0x30
P_V_O_2 = 0x34

encIP.write(KEY_V_1, 0)
encIP.write(KEY_V_2, 0)
encIP.write(KEY_V_3, 0)
encIP.write(KEY_V_4, 0)

encIP.write(P_V_I_1, 0x6f030303)
encIP.write(P_V_I_2, 0x68656c6c)

# start
encIP.write(CONTROL, AP_START)
while encIP.read(CONTROL) & AP_IDLE == 0x0:
	continue

res_low = encIP.read(P_V_O_1)
res_high = encIP.read(P_V_O_2)
print(hex(res_high), hex(res_low))
