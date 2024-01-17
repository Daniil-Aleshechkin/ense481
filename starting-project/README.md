# Starting STM32F103 project file
This is a simple blinky program copied from https://github.com/artem-smotrakov/stm32f103-template

## Windows prerequisits
I have installed the following to build + debug the project
- WSL with any distro: https://learn.microsoft.com/en-us/windows/wsl/install
    - I used Ubuntu
- ARM GCC toolchain: https://developer.arm.com/downloads/-/gnu-rm
    - You need to copy each executable manually into your /usr/share/ drives, then add it to your paths
- St-flash utility: https://manpages.ubuntu.com/manpages/focal/en/man1/st-flash.1.html
- Usbipd (I used v4.0): https://github.com/dorssel/usbipd-win
    - Very useful utility to get around the WSL 2.0 serial ports
- Openocd:
    - For interacting with the ST-link

## Building
Compiling is simply done with

```
make
```

After that it should spit out a .bin file to flash on your board

## Flashing

First on your windows host you need to hook up usbipd to your WSL instance. You first need to identify what bus id your board is taking up. Run

```
usbipd list
```

That should output something like this:

```
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
1-1    0483:374b  ST-Link Debug, USB Mass Storage Device, STMicroelectronic...  Shared
1-8    04f2:b681  Integrated Camera, Integrated IR Camera                       Not shared
1-9    06cb:00bd  Synaptics UWP WBDI                                            Not shared
1-14   8087:0029  Intel(R) Wireless Bluetooth(R)                                Not shared

Persisted:
GUID                                  DEVICE
```

In my case it's hooked up to 1-1. It should be in the Shared state currently

You then attach it to your distro with the attach command. Using my bus id and Ubuntu that would be:

```
usbipd attach --busid 1-1 --wsl Ubuntu
```

You can verify it was attached correctly by running list again:

```
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
1-1    0483:374b  ST-Link Debug, USB Mass Storage Device, STMicroelectronic...  Attached
1-8    04f2:b681  Integrated Camera, Integrated IR Camera                       Not shared
1-9    06cb:00bd  Synaptics UWP WBDI                                            Not shared
1-14   8087:0029  Intel(R) Wireless Bluetooth(R)                                Not shared

Persisted:
GUID                                  DEVICE
```

Once usbipd is set up, on the WSL host you can flash the project using st-flash:
```
st-flash --reset write ./led.bin 0x08000000
```

That should output something like:

```
st-flash 1.7.0
2024-01-17T13:36:25 INFO common.c: F1xx Medium-density: 20 KiB SRAM, 128 KiB flash in at least 1 KiB pages.
file ./led.bin md5 checksum: 3d676b8f7a798149173f719e45929, stlink checksum: 0x0003b3d2
2024-01-17T13:36:25 INFO common.c: Attempting to write 2896 (0xb50) bytes to stm32 address: 134217728 (0x8000000)
2024-01-17T13:36:25 INFO common.c: Flash page at addr: 0x08000000 erased
2024-01-17T13:36:25 INFO common.c: Flash page at addr: 0x08000400 erased
2024-01-17T13:36:25 INFO common.c: Flash page at addr: 0x08000800 erased
2024-01-17T13:36:25 INFO common.c: Finished erasing 3 pages of 1024 (0x400) bytes
2024-01-17T13:36:25 INFO common.c: Starting Flash write for VL/F0/F3/F1_XL
2024-01-17T13:36:25 INFO flash_loader.c: Successfully loaded flash loader in sram
2024-01-17T13:36:25 INFO flash_loader.c: Clear DFSR
  3/  3 pages written
2024-01-17T13:36:25 INFO common.c: Starting verification of write complete
2024-01-17T13:36:25 INFO common.c: Flash written and verified! jolly good!
```

## Debugging 

Debugging is done via gdb + openocd.

First start by starting up the openocd server:

```
openocd -f ./openocd/ocd_stlv2_stm32f1.cfg
```

You should see the st-link light blinking rapidly. Then in a new terminal window run gdb with a few commands to link it up with openocd:

```
arm-none-eabi-gdb -ex "target extended-remote localhost:3333" -ex "file ./led.elf" -ex load
```