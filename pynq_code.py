# coding: utf-8

from __future__ import print_function

import sys

sys.path.append('/home/xilinx')
from pynq import Overlay

print("Entry:", sys.argv[0])
print("System argument(s):", len(sys.argv))

print("Start of \"" + sys.argv[0] + "\"")

ol = Overlay("/home/xilinx/IPBitFile/design_1.bit")
regIP = ol.encrypt_0


regIP.write(16, 0)
regIP.write(20, 0)
regIP.write(24, 0)
regIP.write(28, 0)

regIP.write(36, 0x6f030303)
regIP.write(40, 0x68656c6c)

regIP.write(0x0, 0x01)

res_low = regIP.read(48)
res_high = regIP.read(52)
print(hex(res_high), hex(res_low))
