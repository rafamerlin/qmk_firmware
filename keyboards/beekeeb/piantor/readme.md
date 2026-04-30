# Piantor

![Piantor](https://i.imgur.com/xIF754Qh.jpg)

Piantor is a Cantor fork with Raspberry Pi Pico, hybrid hotswap socket and soldered-in switches support, and a breakable column.

* Keyboard Maintainer: [beekeeb](https://github.com/beekeeb)
* Hardware Supported: RP2040
* Hardware Availability: https://shop.beekeeb.com

Make example for this keyboard (after setting up your build environment):

    make beekeeb/piantor:default

Flashing example for this keyboard:

    make beekeeb/piantor:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Hold the `BOOTSEL` button on the PCB while plugin in the usb cable.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

########

Rafa

I ran `make submodules`
and then `qmk git-submodule`




Do I need to flash each side invididually or not?

Yes, later, if you only change keybindings and nothing about the LED/split feature, flashing just the master/USB side should usually be enough.
Good one-side-only examples:
- remaps
- layer changes
- combo changes
- macro behavior
- tap-hold tuning
Flash both halves if you change anything involving:
- features/os_mode_led.c / .h
- split sync / transaction IDs
- housekeeping_task_user()
- custom shared state
- anything hardware- or side-specific