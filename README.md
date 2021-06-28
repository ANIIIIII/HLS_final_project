# HLS Final Project - Hardware Design of Ciphers via HLS : The Case of PRESENT

## Folder Structure
```bash
.
├── _build
│   ├── design_1.bit
|   └── design_1.hwh
├── _data
│   └── README.md
├── _docs
│   ├── HLS Final Project Presentation.pdf
│   ├── present_fpga.pdf
│   └── rectangle_hls.pdf
├── _impl_result
│   ├── iterative/encrypt_export.rpt
│   ├── serial/encrypt_export.rpt
│   ├── 16bit/encrypt_export.rpt
│   └── proposed/encrypt_export.rpt
├── _src
|   ├── _host
|   |   ├── host.py
|   |   └── host.ipynb
│   ├── _basic
|   |   ├── encrypt.h
|   |   ├── encrypt.cpp
|   |   └── testbench.cpp
│   ├── _iterative
|   |   ├── encrypt.h
|   |   ├── encrypt.cpp
|   |   └── testbench.cpp
│   ├── _serial
|   |   ├── encrypt.h
|   |   ├── encrypt.cpp
|   |   └── testbench.cpp
│   ├── _16-bit
|   |   ├── encrypt.h
|   |   ├── encrypt.cpp
|   |   └── testbench.cpp
│   └── _proposed
|       ├── encrypt.h
|       ├── encrypt.cpp
|       └── testbench.cpp
├── LICENSE
└── README.md
```

## Abstract

  Implement RTL design of lightweight cipher PRESENT via HLS. 
  
  Demonstrate the ability of HLS in hardware design of ciphers.

## Target

  PRESENT with 128 bits key architectures in [1]


## Environment

  Vivado HLS 2019.2
  
  PYNQ-Z2

## Reference 

  [1] C. A. Lara-Nino, A. Diaz-Perez and M. Morales-Sandoval, "Lightweight Hardware Architectures for the Present Cipher in FPGA," in IEEE Transactions on Circuits and Systems I: Regular Papers, vol. 64, no. 9, pp. 2544-2555, Sept. 2017, doi: 10.1109/TCSI.2017.2686783.
