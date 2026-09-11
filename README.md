# ExampleOBDH

## Case Study ##

On-Board Data Handling (OBDH) example for DATE27 paper.

## Setup ##

- Host OS: Ubuntu 22.04
- ForSyDe/Haskell: GHC 9.4.8, Stack 3.1.1, configured with GHCup

### ForSyDe ###

1) GHCup install:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://get-ghcup.haskell.org | sh
```
2) ForSyDe install with stack:
```sh
stack update
stack upgrade
stack install forsyde-shallow
```

### RTEMS ###

1) Follow the 'Quick Start' chapter from the [RTEMS User Manual](https://docs.rtems.org/docs/main/user.pdf)

2) Before building the BSP for the STM32F4, change the memory information of the linker configuration file (path/to/linkcmds.stm32f4) accordingly to the processor. In the case of the F446RET6:
```sh
RAM_INT : ORIGIN = 0x20000000, LENGTH = 128k
ROM_INT : ORIGIN = 0x08000000, LENGTH = 512k
```

NOTE: For the F446 Nucleo board the default USART mapped to printf is USART2. The BSP assumes USART3 since it was made for a different nucleo board. Change the config.ini file to enable the correct USART.

3) Instead of selecting the 'sparc/erc32' BSP, select 'arm/stm32f4' during the BSP cofiguration

## ForSyDe simulation ##

To simulate the OBDH example in ForSyDe, open the terminal in the ForSyDe folder and run the following command:
```sh
stack ghci --package=forsyde-shallow OBDH.hs
```

In the GHC interpreter:
```sh
ghci> obdh s_tc s_ev
({1,4,7,10},{4,10},{9,18})
ghci> obdh s_tc s_ev1
({1,4,7,10},{4,10,16,22},{9,18,27,36})
ghci> obdh s_tc s_ev2
({1,4,7,10},{},{})
```

## Running the OBDH example in the NUCLEO board ##

1) Open the examples folder and build with the make command:
```sh
make
```

2) Upload the binary to the board (we assume the stlink is already installed and configured)
```sh
make obdh
```

3) Use your preferred serial software to check the actor firing sequence and token flow
