import sys
from time import time
from pynq import Overlay
from pynq import allocate
from __future__ import print_function

ROOT = '/home/xilinx/IPBitFile'
PATH = ROOT + '/design_1.bit'

ol = Overlay(PATH)
encIP = ol.encrypt_0

# contrl signal
CONTROL = 0x0
AP_START = 0x01
AP_DONE = 0x02
AP_IDLE = 0x04
AP_READY = 0x08

# i/O port
KEY_V = 0x10
# KEY_V_2 = 0x14
# KEY_V_3 = 0x18
# KEY_V_4 = 0x1C

P_V_I = 0x24
# P_V_I_2 = 0x28

P_V_O_1 = 0x30
P_V_O_2 = 0x34

key = input("Enter 128-bit key (in hex form): ") or "0x0"
plaintext = input("Enter 64-bit plaintext (in hex form): ") or "0x68656c6c6f030303"

print("key: ", key)
print("plaintext: ", plaintext)

key = int(key, 16)
plaintext = int(plaintext, 16)
flag = 0xffffffff

# write key input
for i in range(4):
    encIP.write(KEY_V + 4*i, key & flag)
    key = key >> 32

# write plain-text input
for i in range(2):
    encIP.write(P_V_I + 4*i, plaintext & flag)
    plaintext = plaintext >> 32

# start
encIP.write(CONTROL, AP_START)
exeStartTime = time()
while encIP.read(CONTROL) & AP_IDLE == 0x0:
	continue

exeEndTime = time()
res_low = encIP.read(P_V_O_1)
res_high = encIP.read(P_V_O_2)
print("encypted text: ", hex(res_high) + hex(res_low)[2:])
print("execute time: ", str(1000 * (exeEndTime - exeStartTime)), "ms")

print("=====================================")
print("process done!")
