After we flashed we then can just:
`qmk flash -kb beekeeb/piantor -km rafanovim`

To test
`qmk compile -kb beekeeb/piantor -km rafanovim`


Same as rafanovim but this one has the primary microcontroller as the right one instead of the left
to do it I changed config.h with this:
#define MASTER_RIGHT