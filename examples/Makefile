# Build and make the binary files
all:
	./waf configure --rtems=/opt/rtems/6 --rtems-tools=$(HOME)/quick-start/rtems/6
	./waf build

.PHONY: sdf sadf obdh
sdf:
	cd build/arm-rtems6-stm32f4/sdf; \
	arm-rtems6-objcopy -O binary sdf.exe sdf.bin; \
	STM32_Programmer_CLI -c port=SWD mode=UR reset=HWrst -w sdf.bin 0x08000000 -v -HardRst

sadf:
	cd build/arm-rtems6-stm32f4/sadf; \
	arm-rtems6-objcopy -O binary sadf.exe sadf.bin; \
	STM32_Programmer_CLI -c port=SWD mode=UR reset=HWrst -w sadf.bin 0x08000000 -v -HardRst

obdh:
	cd build/arm-rtems6-stm32f4/obdh; \
	arm-rtems6-objcopy -O binary obdh.exe obdh.bin; \
	STM32_Programmer_CLI -c port=SWD mode=UR reset=HWrst -w obdh.bin 0x08000000 -v -HardRst

clean:
	./waf clean
