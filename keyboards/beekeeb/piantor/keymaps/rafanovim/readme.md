After we flashed we then can just:
`qmk flash -kb beekeeb/piantor -km rafanovim`

To test
`qmk compile -kb beekeeb/piantor -km rafanovim`

On macOS without the qmk CLI, build with Docker (Colima or Docker Desktop must be running), from the repo root:
`SKIP_FLASHING_SUPPORT=1 util/docker_build.sh beekeeb/piantor:rafanovim`

SKIP_FLASHING_SUPPORT is needed because the script otherwise demands docker-machine for USB passthrough on non-Linux hosts, which only matters for :flash targets.

Then flash each half (both, the LED sync needs matching firmware):
1. Enter the bootloader: QK_BOOT key (hold E + bottom-left, or hold Space + bottom-right), double-tap reset, or hold BOOT while plugging in
2. `cp beekeeb_piantor_rafanovim.uf2 /Volumes/RPI-RP2/` (it reboots by itself)
3. Repeat with the USB cable in the other half


Worth reading about debouncing in case more switches end up chattering

asym_eager_defer_pk was recommended in Reddit 

https://docs.qmk.fm/feature_debounce_type