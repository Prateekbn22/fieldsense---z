# Resource Usage Results

## Build configuration

Board:

doit\_esp32\_devkit\_v1/esp32/procpu

Build directory:

build/resource\_analysis

Measurement build includes:

* logging
* serial shell
* thread analyzer
* stack initialization
* thread stack information
* fault injection diagnostics

Because this is a measurement build, flash and RAM include diagnostic overhead.

## Flash usage

Paste the flash / ROM usage summary from results/logs/thread\_analysis.txt here.

Not filled yet.

## Static RAM usage

Paste the RAM usage summary from results/logs/thread\_analysis.txt here.

Not filled yet.

## Thread stack high-water usage

Copy the actual node threads output into this table.

|Thread|Allocated stack|Used stack high-water|Unused stack|Notes|
|-|-:|-:|-:|-|
|fieldsense\_acq|Not filled yet|Not filled yet|Not filled yet|Sensor acquisition thread|
|fieldsense\_proc|Not filled yet|Not filled yet|Not filled yet|Processing/statistics/state thread|
|system workqueue / sysworkq|Not filled yet|Not filled yet|Not filled yet|Zephyr system workqueue|
|shell|Not filled yet|Not filled yet|Not filled yet|Serial diagnostic shell|
|idle|Not filled yet|Not filled yet|Not filled yet|Kernel idle thread|
|logging-related thread if present|Not filled yet|Not filled yet|Not filled yet|Deferred logging/backend work|

## Message queue allocation

The sample queue stores struct sensor\_sample elements.

|Item|Value|
|-|-:|
|Queue depth|4|
|Item size|Not filled yet|
|Payload storage estimate|Not filled yet|

The firmware boot log should print the queue item size and storage estimate.

## Sampling timing

Paste the actual node timing values.

|Metric|Normal operation|Processing-delay injection|After recovery|
|-|-:|-:|-:|
|requested\_period|Not filled yet|Not filled yet|Not filled yet|
|latest\_interval|Not filled yet|Not filled yet|Not filled yet|
|mean\_interval|Not filled yet|Not filled yet|Not filled yet|
|scheduler\_delay|Not filled yet|Not filled yet|Not filled yet|
|missed\_deadlines|Not filled yet|Not filled yet|Not filled yet|
|stale\_data|Not filled yet|Not filled yet|Not filled yet|

## Missed deadlines

During normal operation:

Not filled yet.

During processing-delay injection:

Not filled yet.

After recovery:

Not filled yet.

## Interpretation

The resource measurement showed actual stack high-water usage, static RAM use, flash use, message queue allocation, and timing behavior.

Stacks were not reduced in this milestone.

Any future stack reduction should be done only after repeated testing across:

* normal sampling
* serial shell commands
* fault injection
* queue pressure
* processing delay
* recovery

## Evidence

Raw evidence is saved in:

results/logs/thread\_analysis.txt

results\\logs\\thread\_analysis.txt:132:\[89/286] Building C object zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/h

al/espressif/components/esp\_hal\_mspi/spi\_flash\_encrypt\_hal\_iram.c.obj

results\\logs\\thread\_analysis.txt:134:\[91/286] Building C object zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/h

al/espressif/components/bootloader\_support/src/flash\_encrypt.c.obj

results\\logs\\thread\_analysis.txt:137:\[94/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_hal\_mspi/spi\_flash\_hal.c.obj

results\\logs\\thread\_analysis.txt:138:\[95/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_hal\_mspi/spi\_flash\_hal\_iram.c.obj

results\\logs\\thread\_analysis.txt:139:\[96/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_boya.c.obj

results\\logs\\thread\_analysis.txt:140:\[97/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_issi.c.obj

results\\logs\\thread\_analysis.txt:141:\[98/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_gd.c.obj

results\\logs\\thread\_analysis.txt:142:\[99/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/flash\_mmap.c.obj

results\\logs\\thread\_analysis.txt:143:\[100/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/memspi\_host\_driver.c.obj

results\\logs\\thread\_analysis.txt:144:\[101/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_drivers.c.obj

results\\logs\\thread\_analysis.txt:145:\[102/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_mxic.c.obj

results\\logs\\thread\_analysis.txt:146:\[103/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_mxic\_opi.c.obj

results\\logs\\thread\_analysis.txt:147:\[104/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_th.c.obj

results\\logs\\thread\_analysis.txt:148:\[105/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/esp\_flash\_spi\_init.c.obj

results\\logs\\thread\_analysis.txt:149:\[106/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_generic.c.obj

results\\logs\\thread\_analysis.txt:150:\[107/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_chip\_winbond.c.obj

results\\logs\\thread\_analysis.txt:151:\[108/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/esp\_flash\_api.c.obj

results\\logs\\thread\_analysis.txt:152:\[109/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/flash\_ops.c.obj

results\\logs\\thread\_analysis.txt:153:\[110/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_hal\_i2c/i2c\_hal\_iram.c.obj

results\\logs\\thread\_analysis.txt:155:\[112/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_hal\_uart/uart\_hal\_iram.c.obj

results\\logs\\thread\_analysis.txt:156:\[113/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_os\_func\_noos.c.obj

results\\logs\\thread\_analysis.txt:159:\[116/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/spi\_flash\_os\_func\_app.c.obj

results\\logs\\thread\_analysis.txt:163:\[120/286] Building C object zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/

hal/espressif/components/bootloader\_support/bootloader\_flash/src/flash\_qio\_mode.c.obj

results\\logs\\thread\_analysis.txt:166:\[123/286] Building C object zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/

hal/espressif/components/bootloader\_support/bootloader\_flash/src/bootloader\_flash\_config\_esp32.c.obj

results\\logs\\thread\_analysis.txt:170:\[127/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_hal\_wdt/wdt\_hal\_iram.c.obj

results\\logs\\thread\_analysis.txt:189:\[146/286] Building ASM object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_rom/patches/esp\_rom\_longjmp.S.obj

results\\logs\\thread\_analysis.txt:193:\[150/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_rom/patches/esp\_rom\_crc.c.obj

results\\logs\\thread\_analysis.txt:196:\[153/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_rom/patches/esp\_rom\_efuse.c.obj

results\\logs\\thread\_analysis.txt:198:\[155/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_rom/patches/esp\_rom\_gpio.c.obj

results\\logs\\thread\_analysis.txt:200:\[157/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_rom/patches/esp\_rom\_print.c.obj

results\\logs\\thread\_analysis.txt:201:\[158/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_rom/patches/esp\_rom\_sys.c.obj

results\\logs\\thread\_analysis.txt:202:\[159/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/esp\_rom/patches/esp\_rom\_spiflash.c.obj

results\\logs\\thread\_analysis.txt:203:\[160/286] Building C object zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/

hal/espressif/components/esp\_rom/patches/esp\_rom\_serial\_output.c.obj

results\\logs\\thread\_analysis.txt:219:\[176/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/components/spi\_flash/cache\_utils.c.obj

results\\logs\\thread\_analysis.txt:220:\[177/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/zephyr/common/flash\_init.c.obj

results\\logs\\thread\_analysis.txt:224:\[181/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/zephyr/port/bootloader/bootloader\_flash.c.obj

results\\logs\\thread\_analysis.txt:229:\[186/286] Building C object

zephyr/CMakeFiles/zephyr.dir/C\_/zephyrproject/modules/hal/espressif/zephyr/esp32/src/soc\_flash\_init.c.obj

results\\logs\\thread\_analysis.txt:330:Memory region         Used Size  Region Size  %age Used

results\\logs\\thread\_analysis.txt:331:           FLASH:      181968 B    4194048 B      4.34%

results\\logs\\thread\_analysis.txt:332:     iram0\_0\_seg:       43520 B       221 KB     19.23%

results\\logs\\thread\_analysis.txt:333:     dram0\_0\_seg:       17312 B       192 KB      8.81%

results\\logs\\thread\_analysis.txt:334:     dram1\_0\_seg:       12944 B        93 KB     13.59%

results\\logs\\thread\_analysis.txt:335:     irom0\_0\_seg:       50896 B     11456 KB      0.43%

results\\logs\\thread\_analysis.txt:336:     drom0\_0\_seg:         64 KB         4 MB      1.56%

results\\logs\\thread\_analysis.txt:337:    rtc\_iram\_seg:           0 B         8 KB      0.00%

results\\logs\\thread\_analysis.txt:341:Generating files from

C:/dev/fieldsense-z/build/resource\_analysis/zephyr/zephyr.elf for board: doit\_esp32\_devkit\_v1/esp32/procpu

results\\logs\\thread\_analysis.txt:344:Image has only RAM segments visible. ROM segments are hidden and SHA256 digest is

not appended.

results\\logs\\thread\_analysis.txt:378:===== RAM REPORT =====

results\\logs\\thread\_analysis.txt:379:-- west build: running target ram\_report

results\\logs\\thread\_analysis.txt:380:\[0/1] C:\\WINDOWS\\system32\\cmd.exe /C "cd /D

C:\\dev\\fieldsense-z\\build\\resource\_analysis \&\& C:\\zephyrproject\\.venv\\Scripts\\python.exe

C:/zephyrproject/zephyr/scripts/footprint/size\_report -k C:/dev/fieldsense-z/build/resource\_analysis/zephyr/zephyr.elf

\-z C:/zephyrproject/zephyr -o C:/dev/fieldsense-z/build/resource\_analysis --workspace=C:/zephyrproject -d 99 --json

ram.json ram"

results\\logs\\thread\_analysis.txt:386:Γöé   Γö£ΓöÇΓöÇ CSWTCH$21

&#x20;                         7   0.01%  0x3ffb10d4 .dram0.data

results\\logs\\thread\_analysis.txt:387:Γöé   Γö£ΓöÇΓöÇ CSWTCH$3

&#x20;                       260   0.29%  0x3ffb01e8 .dram0.data

results\\logs\\thread\_analysis.txt:388:Γöé   Γö£ΓöÇΓöÇ CSWTCH$4

&#x20;                        64   0.07%  0x3ffb1038 .dram0.data

results\\logs\\thread\_analysis.txt:389:Γöé   Γö£ΓöÇΓöÇ CSWTCH$409

&#x20;                        20   0.02%  0x3ffb0308 .dram0.data

results\\logs\\thread\_analysis.txt:390:Γöé   Γö£ΓöÇΓöÇ CSWTCH$5

&#x20;                        32   0.04%  0x3ffb1018 .dram0.data

results\\logs\\thread\_analysis.txt:391:Γöé   Γö£ΓöÇΓöÇ CSWTCH$79

&#x20;                        17   0.02%  0x3ffb1797 .dram0.data

results\\logs\\thread\_analysis.txt:392:Γöé   Γö£ΓöÇΓöÇ CSWTCH$80

&#x20;                        17   0.02%  0x3ffb1786 .dram0.data

results\\logs\\thread\_analysis.txt:393:Γöé   Γö£ΓöÇΓöÇ CSWTCH$81

&#x20;                        17   0.02%  0x3ffb1775 .dram0.data

results\\logs\\thread\_analysis.txt:394:Γöé   Γö£ΓöÇΓöÇ CSWTCH$83

&#x20;                        17   0.02%  0x3ffb1753 .dram0.data

results\\logs\\thread\_analysis.txt:395:Γöé   Γö£ΓöÇΓöÇ CSWTCH$86

&#x20;                        17   0.02%  0x3ffb1731 .dram0.data

results\\logs\\thread\_analysis.txt:396:Γöé   Γö£ΓöÇΓöÇ CSWTCH$88

&#x20;                        17   0.02%  0x3ffb1764 .dram0.data

results\\logs\\thread\_analysis.txt:397:Γöé   ΓööΓöÇΓöÇ CSWTCH$90

&#x20;                        17   0.02%  0x3ffb1742 .dram0.data

results\\logs\\thread\_analysis.txt:405:Γöé                   Γöé   Γö£ΓöÇΓöÇ diagnostics\_snapshot

&#x20;                         320   0.36%  0x3ffb38a0 .dram0.bss

results\\logs\\thread\_analysis.txt:406:Γöé                   Γöé   Γö£ΓöÇΓöÇ diagnostics\_snapshot\_valid

&#x20;                           1   0.00%  0x3ffb4364 .dram0.bss

results\\logs\\thread\_analysis.txt:408:Γöé                   Γöé   ΓööΓöÇΓöÇ reset\_stats\_requested

&#x20;                           4   0.00%  0x3ffb3ec4 .dram0.bss

results\\logs\\thread\_analysis.txt:410:Γöé                   Γöé   ΓööΓöÇΓöÇ active\_fault\_injection\_mask

&#x20;                           4   0.00%  0x3ffb3ec8 .dram0.bss

results\\logs\\thread\_analysis.txt:412:Γöé                   Γöé   Γö£ΓöÇΓöÇ \_k\_fifo\_buf\_sensor\_sample\_msgq

&#x20;                         144   0.16%  0x3ffebe00 .dram0.noinit

results\\logs\\thread\_analysis.txt:413:Γöé                   Γöé   Γö£ΓöÇΓöÇ \_k\_thread\_obj\_sensor\_acq\_thread\_id

&#x20;                         176   0.20%  0x3ffb37f0 .dram0.bss

results\\logs\\thread\_analysis.txt:414:Γöé                   Γöé   Γö£ΓöÇΓöÇ \_k\_thread\_obj\_sensor\_processing\_thread\_id

&#x20;                         176   0.20%  0x3ffb3740 .dram0.bss

results\\logs\\thread\_analysis.txt:415:Γöé                   Γöé   Γö£ΓöÇΓöÇ \_k\_thread\_stack\_sensor\_acq\_thread\_id

&#x20;                        2048   2.30%  0x3ffe9400 .dram0.noinit

results\\logs\\thread\_analysis.txt:416:Γöé                   Γöé   Γö£ΓöÇΓöÇ \_k\_thread\_stack\_sensor\_processing\_thread\_id

&#x20;                        2048   2.30%  0x3ffe8c00 .dram0.noinit

results\\logs\\thread\_analysis.txt:418:Γöé                   Γöé   Γö£ΓöÇΓöÇ queue\_full\_count

&#x20;                           4   0.00%  0x3ffb3ec0 .dram0.bss

results\\logs\\thread\_analysis.txt:422:Γöé                       ΓööΓöÇΓöÇ next\_sequence

&#x20;                         4   0.00%  0x3ffb00b8 .dram0.data

results\\logs\\thread\_analysis.txt:435:Γöé               Γöé   Γöé           ΓööΓöÇΓöÇ s\_rtcio\_spinlock

&#x20;                            12   0.01%  0x3ffb0140 .dram0.data

results\\logs\\thread\_analysis.txt:439:Γöé               Γöé   Γöé           ΓööΓöÇΓöÇ rtc\_io\_num\_map

&#x20;                            40   0.04%  0x3ffb1908 .dram0.data

results\\logs\\thread\_analysis.txt:442:Γöé               Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ periph\_spinlock

&#x20;                              12   0.01%  0x3ffb014c .dram0.data

results\\logs\\thread\_analysis.txt:443:Γöé               Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ ref\_counts

&#x20;                              15   0.02%  0x3ffb438b .dram0.bss

results\\logs\\thread\_analysis.txt:447:Γöé               Γöé   Γöé   Γöé   Γöé       Γö£ΓöÇΓöÇ dfs\_lact\_compensate\_table

&#x20;                                18   0.02%  0x3ffb18e0 .dram0.data

results\\logs\\thread\_analysis.txt:448:Γöé               Γöé   Γöé   Γöé   Γöé       ΓööΓöÇΓöÇ s\_cur\_pll\_freq

&#x20;                                 4   0.00%  0x3ffb4234 .dram0.bss

results\\logs\\thread\_analysis.txt:450:Γöé               Γöé   Γöé   Γöé       ΓööΓöÇΓöÇ s\_calibrated\_freq

&#x20;                               8   0.01%  0x3ffb4238 .dram0.bss

results\\logs\\thread\_analysis.txt:452:Γöé               Γöé   Γöé       Γö£ΓöÇΓöÇ s\_config

&#x20;                           184   0.21%  0x3ffb0000 .dram0.data

results\\logs\\thread\_analysis.txt:456:Γöé               Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ s\_cache\_drv

&#x20;                               8   0.01%  0x3ffb011c .dram0.data

results\\logs\\thread\_analysis.txt:458:Γöé               Γöé   Γöé       ΓööΓöÇΓöÇ s\_mmu\_ctx

&#x20;                           144   0.16%  0x3ffb4240 .dram0.bss

results\\logs\\thread\_analysis.txt:464:Γöé               Γöé   Γöé                   ΓööΓöÇΓöÇ s\_reset\_reason

&#x20;                             4   0.00%  0x3ffb42d0 .dram0.bss

results\\logs\\thread\_analysis.txt:467:Γöé               Γöé   Γöé       ΓööΓöÇΓöÇ s\_ctx

&#x20;                             1   0.00%  0x3ffb438a .dram0.bss

results\\logs\\thread\_analysis.txt:471:Γöé               Γöé   Γöé           ΓööΓöÇΓöÇ GPIO\_PIN\_MUX\_REG\_OFFSET

&#x20;                            40   0.04%  0x3ffb1930 .dram0.data

results\\logs\\thread\_analysis.txt:472:Γöé               Γöé   ΓööΓöÇΓöÇ spi\_flash

&#x20;                        1195   1.34%  -

results\\logs\\thread\_analysis.txt:473:Γöé               Γöé       Γö£ΓöÇΓöÇ esp\_flash\_api.c

&#x20;                         210   0.24%  -

results\\logs\\thread\_analysis.txt:474:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ TAG

&#x20;                            10   0.01%  0x3ffb18f2 .dram0.data

results\\logs\\thread\_analysis.txt:475:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_api\_funcs\_patched

&#x20;                            16   0.02%  0x3ffb17ac .dram0.data

results\\logs\\thread\_analysis.txt:476:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_api\_funcs\_patched\_ptr

&#x20;                             4   0.00%  0x3ffb17a8 .dram0.data

results\\logs\\thread\_analysis.txt:477:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ io\_mode\_str

&#x20;                           180   0.20%  0x3ffb167d .dram0.data

results\\logs\\thread\_analysis.txt:478:Γöé               Γöé       Γö£ΓöÇΓöÇ esp\_flash\_spi\_init.c

&#x20;                          88   0.10%  -

results\\logs\\thread\_analysis.txt:479:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ default\_chip

&#x20;                            36   0.04%  0x3ffb17bc .dram0.data

results\\logs\\thread\_analysis.txt:480:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_default\_chip

&#x20;                             4   0.00%  0x3ffb4230 .dram0.bss

results\\logs\\thread\_analysis.txt:481:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_default\_host

&#x20;                            48   0.05%  0x3ffb17e0 .dram0.data

results\\logs\\thread\_analysis.txt:483:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ TAG

&#x20;                             7   0.01%  0x3ffb13b4 .dram0.data

results\\logs\\thread\_analysis.txt:484:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_default\_host

&#x20;                            88   0.10%  0x3ffb1810 .dram0.data

results\\logs\\thread\_analysis.txt:485:Γöé               Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_drivers.c

&#x20;                          28   0.03%  -

results\\logs\\thread\_analysis.txt:486:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ default\_registered\_chips

&#x20;                            24   0.03%  0x3ffb0128 .dram0.data

results\\logs\\thread\_analysis.txt:487:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_registered\_chips

&#x20;                             4   0.00%  0x3ffb0124 .dram0.data

results\\logs\\thread\_analysis.txt:488:Γöé               Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_gd.c

&#x20;                         127   0.14%  -

results\\logs\\thread\_analysis.txt:489:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ chip\_name

&#x20;                             3   0.00%  0x3ffb1170 .dram0.data

results\\logs\\thread\_analysis.txt:490:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_chip\_gd

&#x20;                           124   0.14%  0x3ffb10f4 .dram0.data

results\\logs\\thread\_analysis.txt:491:Γöé               Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic.c

&#x20;                         209   0.23%  -

results\\logs\\thread\_analysis.txt:492:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ TAG

&#x20;                            13   0.01%  0x3ffb1210 .dram0.data

results\\logs\\thread\_analysis.txt:493:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ chip\_name

&#x20;                             8   0.01%  0x3ffb1208 .dram0.data

results\\logs\\thread\_analysis.txt:494:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ default\_flash\_chip\_dummy

&#x20;                             6   0.01%  0x3ffb1902 .dram0.data

results\\logs\\thread\_analysis.txt:495:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_chip\_generic

&#x20;                           124   0.14%  0x3ffb118c .dram0.data

results\\logs\\thread\_analysis.txt:496:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_encryption\_default

&#x20;                            24   0.03%  0x3ffb187c .dram0.data

results\\logs\\thread\_analysis.txt:497:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ hpm\_flash\_chip\_dummy

&#x20;                             6   0.01%  0x3ffb18fc .dram0.data

results\\logs\\thread\_analysis.txt:498:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ rom\_flash\_chip\_dummy

&#x20;                             4   0.00%  0x3ffb1898 .dram0.data

results\\logs\\thread\_analysis.txt:499:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ rom\_flash\_chip\_dummy\_hpm

&#x20;                             4   0.00%  0x3ffb1894 .dram0.data

results\\logs\\thread\_analysis.txt:500:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ spi\_flash\_chip\_generic\_timeout

&#x20;                            20   0.02%  0x3ffb1868 .dram0.data

results\\logs\\thread\_analysis.txt:501:Γöé               Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_issi.c

&#x20;                         129   0.14%  -

results\\logs\\thread\_analysis.txt:502:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ chip\_name

&#x20;                             5   0.01%  0x3ffb129c .dram0.data

results\\logs\\thread\_analysis.txt:503:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_chip\_issi

&#x20;                           124   0.14%  0x3ffb1220 .dram0.data

results\\logs\\thread\_analysis.txt:504:Γöé               Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_mxic.c

&#x20;                         129   0.14%  -

results\\logs\\thread\_analysis.txt:505:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ chip\_name

&#x20;                             5   0.01%  0x3ffb1320 .dram0.data

results\\logs\\thread\_analysis.txt:506:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_chip\_mxic

&#x20;                           124   0.14%  0x3ffb12a4 .dram0.data

results\\logs\\thread\_analysis.txt:507:Γöé               Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_winbond.c

&#x20;                         140   0.16%  -

results\\logs\\thread\_analysis.txt:508:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ TAG

&#x20;                             8   0.01%  0x3ffb13ac .dram0.data

results\\logs\\thread\_analysis.txt:509:Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ chip\_name

&#x20;                             8   0.01%  0x3ffb13a4 .dram0.data

results\\logs\\thread\_analysis.txt:510:Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_chip\_winbond

&#x20;                           124   0.14%  0x3ffb1328 .dram0.data

results\\logs\\thread\_analysis.txt:511:Γöé               Γöé       ΓööΓöÇΓöÇ spi\_flash\_os\_func\_noos.c

&#x20;                          40   0.04%  -

results\\logs\\thread\_analysis.txt:512:Γöé               Γöé           ΓööΓöÇΓöÇ esp\_flash\_noos\_functions

&#x20;                          40   0.04%  0x3ffb189c .dram0.data

results\\logs\\thread\_analysis.txt:516:Γöé                           ΓööΓöÇΓöÇ bootloader\_flash.c

&#x20;                         4   0.00%  -

results\\logs\\thread\_analysis.txt:517:Γöé                               ΓööΓöÇΓöÇ current\_read\_mapping

&#x20;                         4   0.00%  0x3ffb0158 .dram0.data

results\\logs\\thread\_analysis.txt:523:    Γöé           Γöé   ΓööΓöÇΓöÇ xtensa\_lvl\_mask

&#x20;                          28   0.03%  0x3ffb02ec .dram0.data

results\\logs\\thread\_analysis.txt:525:    Γöé               Γö£ΓöÇΓöÇ cause

&#x20;                         4   0.00%  0x3ffb42d4 .dram0.bss

results\\logs\\thread\_analysis.txt:526:    Γöé               ΓööΓöÇΓöÇ mask

&#x20;                         4   0.00%  0x3ffb42d8 .dram0.bss

results\\logs\\thread\_analysis.txt:533:    Γöé   Γöé       ΓööΓöÇΓöÇ clock\_init\_done

&#x20;                           1   0.00%  0x3ffb439a .dram0.bss

results\\logs\\thread\_analysis.txt:538:    Γöé   Γöé       Γö£ΓöÇΓöÇ gpio\_config\_0

&#x20;                          16   0.02%  0x3ffb017c .dram0.data

results\\logs\\thread\_analysis.txt:539:    Γöé   Γöé       Γö£ΓöÇΓöÇ gpio\_config\_1

&#x20;                          16   0.02%  0x3ffb016c .dram0.data

results\\logs\\thread\_analysis.txt:540:    Γöé   Γöé       Γö£ΓöÇΓöÇ gpio\_data\_0

&#x20;                          12   0.01%  0x3ffb4310 .dram0.bss

results\\logs\\thread\_analysis.txt:541:    Γöé   Γöé       Γö£ΓöÇΓöÇ gpio\_data\_1

&#x20;                          12   0.01%  0x3ffb4304 .dram0.bss

results\\logs\\thread\_analysis.txt:542:    Γöé   Γöé       Γö£ΓöÇΓöÇ isr\_connected$0

&#x20;                           1   0.00%  0x3ffb439b .dram0.bss

results\\logs\\thread\_analysis.txt:549:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_esp32\_data\_0

&#x20;                          52   0.06%  0x3ffb018c .dram0.data

results\\logs\\thread\_analysis.txt:554:    Γöé   Γöé       Γö£ΓöÇΓöÇ non\_iram\_int\_mask

&#x20;                           4   0.00%  0x3ffb42fc .dram0.bss

results\\logs\\thread\_analysis.txt:555:    Γöé   Γöé       ΓööΓöÇΓöÇ vector\_desc\_head

&#x20;                           4   0.00%  0x3ffb4300 .dram0.bss

results\\logs\\thread\_analysis.txt:561:    Γöé   Γöé               Γö£ΓöÇΓöÇ bme280\_data\_0

&#x20;                          56   0.06%  0x3ffb431c .dram0.bss

results\\logs\\thread\_analysis.txt:565:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_meta\_dts\_ord\_72

&#x20;                           4   0.00%  0x3ffb10a8 .dram0.data

results\\logs\\thread\_analysis.txt:566:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_nodelabels\_dts\_ord\_72

&#x20;                           8   0.01%  0x3ffb10ac .dram0.data

results\\logs\\thread\_analysis.txt:568:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_pinctrl\_dev\_config\_\_device\_dts\_ord\_72

&#x20;                           8   0.01%  0x3ffb10b4 .dram0.data

results\\logs\\thread\_analysis.txt:569:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_pinctrl\_state\_pins\_0\_\_device\_dts\_ord\_72

&#x20;                          16   0.02%  0x3ffb10c4 .dram0.data

results\\logs\\thread\_analysis.txt:570:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_pinctrl\_states\_\_device\_dts\_ord\_72

&#x20;                           8   0.01%  0x3ffb10bc .dram0.data

results\\logs\\thread\_analysis.txt:572:    Γöé   Γöé       Γö£ΓöÇΓöÇ uart\_esp32\_cfg\_port\_0

&#x20;                          28   0.03%  0x3ffb18c4 .dram0.data

results\\logs\\thread\_analysis.txt:573:    Γöé   Γöé       ΓööΓöÇΓöÇ uart\_esp32\_data\_0

&#x20;                          24   0.03%  0x3ffb01c0 .dram0.data

results\\logs\\thread\_analysis.txt:576:    Γöé           ΓööΓöÇΓöÇ last\_count

&#x20;                         4   0.00%  0x3ffb4354 .dram0.bss

results\\logs\\thread\_analysis.txt:579:    Γöé   Γöé   Γö£ΓöÇΓöÇ \_kernel

&#x20;                          64   0.07%  0x3ffb3db0 .dram0.bss

results\\logs\\thread\_analysis.txt:580:    Γöé   Γöé   Γö£ΓöÇΓöÇ levels$0

&#x20;                          24   0.03%  0x3ffb031c .dram0.data

results\\logs\\thread\_analysis.txt:582:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_idle\_stacks

&#x20;                        1024   1.15%  0x3ffeb000 .dram0.noinit

results\\logs\\thread\_analysis.txt:583:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_idle\_threads

&#x20;                         176   0.20%  0x3ffb3c50 .dram0.bss

results\\logs\\thread\_analysis.txt:584:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_interrupt\_stacks

&#x20;                        2048   2.30%  0x3ffea800 .dram0.noinit

results\\logs\\thread\_analysis.txt:585:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_main\_stack

&#x20;                        2048   2.30%  0x3ffeb400 .dram0.noinit

results\\logs\\thread\_analysis.txt:586:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_main\_thread

&#x20;                         176   0.20%  0x3ffb3d00 .dram0.bss

results\\logs\\thread\_analysis.txt:587:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_sys\_post\_kernel

&#x20;                           1   0.00%  0x3ffb439c .dram0.bss

results\\logs\\thread\_analysis.txt:590:    Γöé   Γöé   ΓööΓöÇΓöÇ kheap\_\_system\_heap

&#x20;                        4164   4.67%  0x3ffb20f0 .dram0.bss

results\\logs\\thread\_analysis.txt:592:    Γöé   Γöé   ΓööΓöÇΓöÇ \_thread\_dummy

&#x20;                         176   0.20%  0x3ffb3df0 .dram0.bss

results\\logs\\thread\_analysis.txt:594:    Γöé   Γöé   Γö£ΓöÇΓöÇ announce\_remaining

&#x20;                           4   0.00%  0x3ffb4360 .dram0.bss

results\\logs\\thread\_analysis.txt:595:    Γöé   Γöé   Γö£ΓöÇΓöÇ announcing\_cpu

&#x20;                           4   0.00%  0x3ffb01e4 .dram0.data

results\\logs\\thread\_analysis.txt:596:    Γöé   Γöé   Γö£ΓöÇΓöÇ curr\_tick

&#x20;                           8   0.01%  0x3ffb3eb8 .dram0.bss

results\\logs\\thread\_analysis.txt:597:    Γöé   Γöé   ΓööΓöÇΓöÇ inflight\_timeout

&#x20;                           4   0.00%  0x3ffb435c .dram0.bss

results\\logs\\thread\_analysis.txt:599:    Γöé   Γöé   ΓööΓöÇΓöÇ timeout\_list

&#x20;                           8   0.01%  0x3ffb01dc .dram0.data

results\\logs\\thread\_analysis.txt:601:    Γöé       Γö£ΓöÇΓöÇ slice\_expired

&#x20;                         1   0.00%  0x3ffb439d .dram0.bss

results\\logs\\thread\_analysis.txt:602:    Γöé       Γö£ΓöÇΓöÇ slice\_max\_prio

&#x20;                         4   0.00%  0x3ffb4358 .dram0.bss

results\\logs\\thread\_analysis.txt:603:    Γöé       Γö£ΓöÇΓöÇ slice\_ticks

&#x20;                         4   0.00%  0x3ffb01d8 .dram0.data

results\\logs\\thread\_analysis.txt:604:    Γöé       ΓööΓöÇΓöÇ slice\_timeouts

&#x20;                        24   0.03%  0x3ffb3ea0 .dram0.bss

results\\logs\\thread\_analysis.txt:614:    Γöé   Γöé   Γöé               ΓööΓöÇΓöÇ z\_malloc\_heap

&#x20;                            12   0.01%  0x3ffb42e0 .dram0.bss

results\\logs\\thread\_analysis.txt:617:    Γöé   Γöé           Γö£ΓöÇΓöÇ \_\_stdout

&#x20;                          16   0.02%  0x3ffb015c .dram0.data

results\\logs\\thread\_analysis.txt:618:    Γöé   Γöé           ΓööΓöÇΓöÇ \_stdout\_hook

&#x20;                           4   0.00%  0x3ffb42dc .dram0.bss

results\\logs\\thread\_analysis.txt:623:    Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ rt\_clock\_offset

&#x20;                            16   0.02%  0x3ffb39e0 .dram0.bss

results\\logs\\thread\_analysis.txt:625:    Γöé   Γöé       ΓööΓöÇΓöÇ \_char\_out

&#x20;                           4   0.00%  0x3ffb00bc .dram0.data

results\\logs\\thread\_analysis.txt:631:    Γöé               Γö£ΓöÇΓöÇ m\_getopt\_common\_state

&#x20;                        24   0.03%  0x3ffb00c0 .dram0.data

results\\logs\\thread\_analysis.txt:632:    Γöé               Γö£ΓöÇΓöÇ sys\_getopt\_optarg

&#x20;                         4   0.00%  0x3ffb3ecc .dram0.bss

results\\logs\\thread\_analysis.txt:633:    Γöé               Γö£ΓöÇΓöÇ sys\_getopt\_opterr

&#x20;                         4   0.00%  0x3ffb00dc .dram0.data

results\\logs\\thread\_analysis.txt:634:    Γöé               Γö£ΓöÇΓöÇ sys\_getopt\_optind

&#x20;                         4   0.00%  0x3ffb00d8 .dram0.data

results\\logs\\thread\_analysis.txt:635:    Γöé               Γö£ΓöÇΓöÇ sys\_getopt\_optopt

&#x20;                         4   0.00%  0x3ffb3ed4 .dram0.bss

results\\logs\\thread\_analysis.txt:636:    Γöé               ΓööΓöÇΓöÇ sys\_getopt\_optreset

&#x20;                         4   0.00%  0x3ffb3ed0 .dram0.bss

results\\logs\\thread\_analysis.txt:641:    Γöé               Γö£ΓöÇΓöÇ bootloader\_image\_hdr

&#x20;                        24   0.03%  0x3ffb3ed8 .dram0.bss

results\\logs\\thread\_analysis.txt:642:    Γöé               Γö£ΓöÇΓöÇ libc\_heap\_size

&#x20;                         4   0.00%  0x3ffb03a0 .dram0.data

results\\logs\\thread\_analysis.txt:643:    Γöé               ΓööΓöÇΓöÇ map

&#x20;                        24   0.03%  0x3ffb00e0 .dram0.data

results\\logs\\thread\_analysis.txt:651:        Γöé   Γöé   Γö£ΓöÇΓöÇ backend\_attached

&#x20;                           1   0.00%  0x3ffb4365 .dram0.bss

results\\logs\\thread\_analysis.txt:652:        Γöé   Γöé   Γö£ΓöÇΓöÇ buf32

&#x20;                        1024   1.15%  0x3ffb3140 .dram0.bss

results\\logs\\thread\_analysis.txt:653:        Γöé   Γöé   Γö£ΓöÇΓöÇ buffered\_cnt

&#x20;                           4   0.00%  0x3ffb3efc .dram0.bss

results\\logs\\thread\_analysis.txt:654:        Γöé   Γöé   Γö£ΓöÇΓöÇ curr\_log\_buffer

&#x20;                           4   0.00%  0x3ffb3ef0 .dram0.bss

results\\logs\\thread\_analysis.txt:655:        Γöé   Γöé   Γö£ΓöÇΓöÇ dropped\_cnt

&#x20;                           4   0.00%  0x3ffb3ef8 .dram0.bss

results\\logs\\thread\_analysis.txt:656:        Γöé   Γöé   Γö£ΓöÇΓöÇ initialized

&#x20;                           4   0.00%  0x3ffb3f00 .dram0.bss

results\\logs\\thread\_analysis.txt:657:        Γöé   Γöé   Γö£ΓöÇΓöÇ last\_failure\_report

&#x20;                           8   0.01%  0x3ffb3aa0 .dram0.bss

results\\logs\\thread\_analysis.txt:662:        Γöé   Γöé   Γö£ΓöÇΓöÇ log\_process\_thread\_timer

&#x20;                          56   0.06%  0x3ffb3aa8 .dram0.bss

results\\logs\\thread\_analysis.txt:663:        Γöé   Γöé   Γö£ΓöÇΓöÇ logging\_stack

&#x20;                        1024   1.15%  0x3ffe9c00 .dram0.noinit

results\\logs\\thread\_analysis.txt:664:        Γöé   Γöé   Γö£ΓöÇΓöÇ logging\_thread

&#x20;                         176   0.20%  0x3ffb39f0 .dram0.bss

results\\logs\\thread\_analysis.txt:665:        Γöé   Γöé   Γö£ΓöÇΓöÇ mpsc\_config

&#x20;                          20   0.02%  0x3ffb0334 .dram0.data

results\\logs\\thread\_analysis.txt:666:        Γöé   Γöé   Γö£ΓöÇΓöÇ panic\_mode

&#x20;                           1   0.00%  0x3ffb4366 .dram0.bss

results\\logs\\thread\_analysis.txt:667:        Γöé   Γöé   Γö£ΓöÇΓöÇ proc\_tid

&#x20;                           4   0.00%  0x3ffb3ef4 .dram0.bss

results\\logs\\thread\_analysis.txt:668:        Γöé   Γöé   ΓööΓöÇΓöÇ timestamp\_func

&#x20;                           4   0.00%  0x3ffb00f8 .dram0.data

results\\logs\\thread\_analysis.txt:672:        Γöé       Γö£ΓöÇΓöÇ colors

&#x20;                        20   0.02%  0x3ffb0348 .dram0.data

results\\logs\\thread\_analysis.txt:673:        Γöé       Γö£ΓöÇΓöÇ freq

&#x20;                         4   0.00%  0x3ffb3f08 .dram0.bss

results\\logs\\thread\_analysis.txt:674:        Γöé       Γö£ΓöÇΓöÇ func\_on\_lut

&#x20;                         5   0.01%  0x3ffb0398 .dram0.data

results\\logs\\thread\_analysis.txt:675:        Γöé       Γö£ΓöÇΓöÇ postfix$0

&#x20;                        28   0.03%  0x3ffb0370 .dram0.data

results\\logs\\thread\_analysis.txt:676:        Γöé       Γö£ΓöÇΓöÇ prefix$1

&#x20;                        12   0.01%  0x3ffb038c .dram0.data

results\\logs\\thread\_analysis.txt:677:        Γöé       Γö£ΓöÇΓöÇ severity

&#x20;                        20   0.02%  0x3ffb035c .dram0.data

results\\logs\\thread\_analysis.txt:678:        Γöé       ΓööΓöÇΓöÇ timestamp\_div

&#x20;                         4   0.00%  0x3ffb3f04 .dram0.bss

results\\logs\\thread\_analysis.txt:683:        Γöé               Γö£ΓöÇΓöÇ optarg

&#x20;                         4   0.00%  0x3ffb42f8 .dram0.bss

results\\logs\\thread\_analysis.txt:684:        Γöé               Γö£ΓöÇΓöÇ opterr

&#x20;                         4   0.00%  0x3ffb42f4 .dram0.bss

results\\logs\\thread\_analysis.txt:685:        Γöé               Γö£ΓöÇΓöÇ optind

&#x20;                         4   0.00%  0x3ffb42f0 .dram0.bss

results\\logs\\thread\_analysis.txt:686:        Γöé               ΓööΓöÇΓöÇ optopt

&#x20;                         4   0.00%  0x3ffb42ec .dram0.bss

results\\logs\\thread\_analysis.txt:690:            Γöé       Γö£ΓöÇΓöÇ backend\_cb\_shell\_uart\_backend

&#x20;                         8   0.01%  0x3ffb4228 .dram0.bss

results\\logs\\thread\_analysis.txt:691:            Γöé       Γö£ΓöÇΓöÇ kheap\_shell\_uart\_history\_heap

&#x20;                       512   0.57%  0x3ffebc00 .dram0.noinit

results\\logs\\thread\_analysis.txt:694:            Γöé       Γö£ΓöÇΓöÇ shell\_transport\_uart

&#x20;                         8   0.01%  0x3ffb0114 .dram0.data

results\\logs\\thread\_analysis.txt:695:            Γöé       Γö£ΓöÇΓöÇ shell\_transport\_uart\_shell\_uart

&#x20;                       192   0.22%  0x3ffb3b90 .dram0.bss

results\\logs\\thread\_analysis.txt:696:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_control\_block

&#x20;                         8   0.01%  0x3ffb4214 .dram0.bss

results\\logs\\thread\_analysis.txt:697:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_ctx

&#x20;                       700   0.79%  0x3ffb3f20 .dram0.bss

results\\logs\\thread\_analysis.txt:698:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_fprintf\_shell\_fprintf\_ctx

&#x20;                         8   0.01%  0x3ffb00fc .dram0.data

results\\logs\\thread\_analysis.txt:699:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_history

&#x20;                        16   0.02%  0x3ffb0104 .dram0.data

results\\logs\\thread\_analysis.txt:701:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_log\_output\_control\_block

&#x20;                        12   0.01%  0x3ffb421c .dram0.bss

results\\logs\\thread\_analysis.txt:702:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_mpsc\_buffer

&#x20;                        56   0.06%  0x3ffb41dc .dram0.bss

results\\logs\\thread\_analysis.txt:703:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_out\_buffer

&#x20;                        30   0.03%  0x3ffb436c .dram0.bss

results\\logs\\thread\_analysis.txt:704:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_stack

&#x20;                      2048   2.30%  0x3ffea000 .dram0.noinit

results\\logs\\thread\_analysis.txt:705:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_stats

&#x20;                         4   0.00%  0x3ffb3f1c .dram0.bss

results\\logs\\thread\_analysis.txt:706:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_thread

&#x20;                       176   0.20%  0x3ffb3ae0 .dram0.bss

results\\logs\\thread\_analysis.txt:707:            Γöé       ΓööΓöÇΓöÇ shell\_uartshell\_uart\_out\_buffer

&#x20;                       512   0.57%  0x3ffb3540 .dram0.bss

results\\logs\\thread\_analysis.txt:710:                    Γö£ΓöÇΓöÇ bytes

&#x20;                       4   0.00%  0x3ffb3f18 .dram0.bss

results\\logs\\thread\_analysis.txt:711:                    Γö£ΓöÇΓöÇ chunk

&#x20;                       2   0.00%  0x3ffb436a .dram0.bss

results\\logs\\thread\_analysis.txt:712:                    Γö£ΓöÇΓöÇ chunk\_element

&#x20;                       4   0.00%  0x3ffb3f0c .dram0.bss

results\\logs\\thread\_analysis.txt:713:                    Γö£ΓöÇΓöÇ data

&#x20;                       4   0.00%  0x3ffb3f14 .dram0.bss

results\\logs\\thread\_analysis.txt:714:                    Γö£ΓöÇΓöÇ in\_use$0

&#x20;                       1   0.00%  0x3ffb4367 .dram0.bss

results\\logs\\thread\_analysis.txt:715:                    Γö£ΓöÇΓöÇ littleendian

&#x20;                       1   0.00%  0x3ffb4369 .dram0.bss

results\\logs\\thread\_analysis.txt:716:                    Γö£ΓöÇΓöÇ sum

&#x20;                       4   0.00%  0x3ffb3f10 .dram0.bss

results\\logs\\thread\_analysis.txt:717:                    ΓööΓöÇΓöÇ tail$1

&#x20;                       1   0.00%  0x3ffb4368 .dram0.bss

results\\logs\\thread\_analysis.txt:721:===== ROM REPORT =====

results\\logs\\thread\_analysis.txt:722:-- west build: running target rom\_report

results\\logs\\thread\_analysis.txt:723:\[0/1] C:\\WINDOWS\\system32\\cmd.exe /C "cd /D

C:\\dev\\fieldsense-z\\build\\resource\_analysis \&\& C:\\zephyrproject\\.venv\\Scripts\\python.exe

C:/zephyrproject/zephyr/scripts/footprint/size\_report -k C:/dev/fieldsense-z/build/resource\_analysis/zephyr/zephyr.elf

\-z C:/zephyrproject/zephyr -o C:/dev/fieldsense-z/build/resource\_analysis --workspace=C:/zephyrproject -d 99 --json

rom.json rom"

results\\logs\\thread\_analysis.txt:729:Γöé   Γö£ΓöÇΓöÇ CSWTCH$1152

&#x20;                        12   0.01%  0x3f400e3c .flash.rodata

results\\logs\\thread\_analysis.txt:730:Γöé   Γö£ΓöÇΓöÇ CSWTCH$23

&#x20;                        16   0.01%  0x3f400084 .flash.rodata

results\\logs\\thread\_analysis.txt:731:Γöé   Γö£ΓöÇΓöÇ CSWTCH$25

&#x20;                        16   0.01%  0x3f400074 .flash.rodata

results\\logs\\thread\_analysis.txt:732:Γöé   Γö£ΓöÇΓöÇ CSWTCH$265

&#x20;                         6   0.01%  0x3f404675 .flash.rodata

results\\logs\\thread\_analysis.txt:733:Γöé   Γö£ΓöÇΓöÇ CSWTCH$27

&#x20;                        20   0.02%  0x3f400060 .flash.rodata

results\\logs\\thread\_analysis.txt:734:Γöé   Γö£ΓöÇΓöÇ CSWTCH$284

&#x20;                        56   0.05%  0x3f400dcc .flash.rodata

results\\logs\\thread\_analysis.txt:735:Γöé   Γö£ΓöÇΓöÇ CSWTCH$369

&#x20;                        24   0.02%  0x3f400020 .flash.rodata

results\\logs\\thread\_analysis.txt:741:Γöé   Γö£ΓöÇΓöÇ \_\_FUNCTION\_\_$10

&#x20;                        20   0.02%  0x3f40464e .flash.rodata

results\\logs\\thread\_analysis.txt:742:Γöé   Γö£ΓöÇΓöÇ \_\_FUNCTION\_\_$11

&#x20;                        19   0.02%  0x3f404662 .flash.rodata

results\\logs\\thread\_analysis.txt:743:Γöé   Γö£ΓöÇΓöÇ \_\_FUNCTION\_\_$8

&#x20;                        22   0.02%  0x3f404623 .flash.rodata

results\\logs\\thread\_analysis.txt:744:Γöé   Γö£ΓöÇΓöÇ \_\_FUNCTION\_\_$9

&#x20;                        21   0.02%  0x3f404639 .flash.rodata

results\\logs\\thread\_analysis.txt:745:Γöé   Γö£ΓöÇΓöÇ \_\_compound\_literal$0

&#x20;                        12   0.01%  0x3f4001cc .flash.rodata

results\\logs\\thread\_analysis.txt:753:Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal\_supports\_direct\_read

&#x20;                        18   0.02%  0x4008a878 .loader.text

results\\logs\\thread\_analysis.txt:754:Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal\_suspend

&#x20;                         6   0.01%  0x40088440 .iram0.text

results\\logs\\thread\_analysis.txt:758:Γöé   Γö£ΓöÇΓöÇ xthal\_window\_spill

&#x20;                        35   0.03%  0x40084ddc .iram0.text

results\\logs\\thread\_analysis.txt:759:Γöé   ΓööΓöÇΓöÇ xthal\_window\_spill\_nw

&#x20;                       273   0.24%  0x40084cc8 .iram0.text

results\\logs\\thread\_analysis.txt:766:Γöé                   Γöé   Γö£ΓöÇΓöÇ \_shell\_node

&#x20;                          20   0.02%  0x3f400094 .flash.rodata

results\\logs\\thread\_analysis.txt:787:Γöé                   Γöé   ΓööΓöÇΓöÇ env\_stats\_update\_from\_sample

&#x20;                          50   0.04%  0x400d196c .text

results\\logs\\thread\_analysis.txt:833:Γöé       Γöé               Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_static\_create$constprop$0

&#x20;                            19   0.02%  0x400827a0 .iram0.text

results\\logs\\thread\_analysis.txt:849:Γöé   Γöé           Γöé   Γöé   Γö£ΓöÇΓöÇ bootloader\_flash

&#x20;                             110   0.10%  -

results\\logs\\thread\_analysis.txt:851:Γöé   Γöé           Γöé   Γöé   Γöé       ΓööΓöÇΓöÇ

bootloader\_flash\_config\_esp32.c                               110   0.10%  -

results\\logs\\thread\_analysis.txt:852:Γöé   Γöé           Γöé   Γöé   Γöé           ΓööΓöÇΓöÇ

bootloader\_flash\_cs\_timing\_config                         110   0.10%  0x40080d28 .iram0.text

results\\logs\\thread\_analysis.txt:855:Γöé   Γöé           Γöé   Γöé           ΓööΓöÇΓöÇ

bootloader\_common\_get\_chip\_ver\_pkg                             30   0.03%  0x40080d98 .iram0.text

results\\logs\\thread\_analysis.txt:859:Γöé   Γöé           Γöé   Γöé           Γö£ΓöÇΓöÇ rtc\_gpio\_is\_valid\_gpio

&#x20;                              30   0.03%  0x40086974 .iram0.text

results\\logs\\thread\_analysis.txt:860:Γöé   Γöé           Γöé   Γöé           Γö£ΓöÇΓöÇ rtc\_gpio\_pulldown\_dis

&#x20;                             145   0.13%  0x40086b44 .iram0.text

results\\logs\\thread\_analysis.txt:861:Γöé   Γöé           Γöé   Γöé           Γö£ΓöÇΓöÇ rtc\_gpio\_pulldown\_en

&#x20;                             140   0.12%  0x40086ab8 .iram0.text

results\\logs\\thread\_analysis.txt:862:Γöé   Γöé           Γöé   Γöé           Γö£ΓöÇΓöÇ rtc\_gpio\_pullup\_dis

&#x20;                             145   0.13%  0x40086a24 .iram0.text

results\\logs\\thread\_analysis.txt:863:Γöé   Γöé           Γöé   Γöé           ΓööΓöÇΓöÇ rtc\_gpio\_pullup\_en

&#x20;                             141   0.12%  0x40086994 .iram0.text

results\\logs\\thread\_analysis.txt:876:Γöé   Γöé           Γöé   Γöé                   Γö£ΓöÇΓöÇ

periph\_ll\_disable\_clk\_set\_rst                          94   0.08%  0x40089c68 .iram0.text

results\\logs\\thread\_analysis.txt:877:Γöé   Γöé           Γöé   Γöé                   ΓööΓöÇΓöÇ

periph\_ll\_enable\_clk\_clear\_rst                         94   0.08%  0x40089cc8 .iram0.text

results\\logs\\thread\_analysis.txt:885:Γöé   Γöé           Γöé   Γöé           ΓööΓöÇΓöÇ rtc\_io\_desc

&#x20;                            1008   0.88%  0x3f4006ac .flash.rodata

results\\logs\\thread\_analysis.txt:891:Γöé   Γöé           Γöé   Γöé   ΓööΓöÇΓöÇ i2c\_hal\_iram.c

&#x20;                             246   0.21%  -

results\\logs\\thread\_analysis.txt:892:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_hal\_master\_handle\_rx\_event

&#x20;                             123   0.11%  0x40087d28 .iram0.text

results\\logs\\thread\_analysis.txt:893:Γöé   Γöé           Γöé   Γöé       ΓööΓöÇΓöÇ i2c\_hal\_master\_handle\_tx\_event

&#x20;                             123   0.11%  0x40087cac .iram0.text

results\\logs\\thread\_analysis.txt:895:Γöé   Γöé           Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_encrypt\_hal\_iram.c

&#x20;                             127   0.11%  -

results\\logs\\thread\_analysis.txt:896:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_encryption\_hal\_check

&#x20;                                14   0.01%  0x400886bc .iram0.text

results\\logs\\thread\_analysis.txt:897:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_encryption\_hal\_destroy

&#x20;                                 5   0.00%  0x400886b4 .iram0.text

results\\logs\\thread\_analysis.txt:898:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_encryption\_hal\_disable

&#x20;                                24   0.02%  0x40088660 .iram0.text

results\\logs\\thread\_analysis.txt:899:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_encryption\_hal\_done

&#x20;                                16   0.01%  0x400886a4 .iram0.text

results\\logs\\thread\_analysis.txt:900:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_encryption\_hal\_enable

&#x20;                                24   0.02%  0x40088648 .iram0.text

results\\logs\\thread\_analysis.txt:901:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ spi\_flash\_encryption\_hal\_prepare

&#x20;                                44   0.04%  0x40088678 .iram0.text

results\\logs\\thread\_analysis.txt:902:Γöé   Γöé           Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal.c

&#x20;                             354   0.31%  -

results\\logs\\thread\_analysis.txt:903:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ get\_flash\_clock\_divider

&#x20;                                59   0.05%  0x4008a710 .loader.text

results\\logs\\thread\_analysis.txt:904:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal\_init

&#x20;                               277   0.24%  0x4008a74c .loader.text

results\\logs\\thread\_analysis.txt:905:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ

spi\_flash\_hal\_supports\_direct\_write                                18   0.02%  0x4008a864 .loader.text

results\\logs\\thread\_analysis.txt:906:Γöé   Γöé           Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal\_common.inc

&#x20;                            1518   1.32%  -

results\\logs\\thread\_analysis.txt:907:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal\_common\_command

&#x20;                               478   0.42%  0x40088074 .iram0.text

results\\logs\\thread\_analysis.txt:908:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_hal\_configure\_host\_io\_mode                              544   0.47%  0x40087e54 .iram0.text

results\\logs\\thread\_analysis.txt:909:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal\_device\_config

&#x20;                               219   0.19%  0x40088458 .iram0.text

results\\logs\\thread\_analysis.txt:910:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ spi\_flash\_hal\_poll\_cmd\_done

&#x20;                                15   0.01%  0x40088448 .iram0.text

results\\logs\\thread\_analysis.txt:911:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ spi\_flash\_hal\_read

&#x20;                               262   0.23%  0x40088254 .iram0.text

results\\logs\\thread\_analysis.txt:912:Γöé   Γöé           Γöé   Γöé   ΓööΓöÇΓöÇ spi\_flash\_hal\_iram.c

&#x20;                             496   0.43%  -

results\\logs\\thread\_analysis.txt:913:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ spi\_flash\_hal\_check\_status

&#x20;                              47   0.04%  0x40088408 .iram0.text

results\\logs\\thread\_analysis.txt:914:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ spi\_flash\_hal\_erase\_block

&#x20;                              88   0.08%  0x400885b8 .iram0.text

results\\logs\\thread\_analysis.txt:915:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ spi\_flash\_hal\_erase\_chip

&#x20;                              35   0.03%  0x40088534 .iram0.text

results\\logs\\thread\_analysis.txt:916:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ spi\_flash\_hal\_erase\_sector

&#x20;                              95   0.08%  0x40088558 .iram0.text

results\\logs\\thread\_analysis.txt:917:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ spi\_flash\_hal\_program\_page

&#x20;                             170   0.15%  0x4008835c .iram0.text

results\\logs\\thread\_analysis.txt:918:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ spi\_flash\_hal\_resume

&#x20;                               6   0.01%  0x40088438 .iram0.text

results\\logs\\thread\_analysis.txt:919:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ spi\_flash\_hal\_set\_write\_protect

&#x20;                              48   0.04%  0x40088610 .iram0.text

results\\logs\\thread\_analysis.txt:920:Γöé   Γöé           Γöé   Γöé       ΓööΓöÇΓöÇ spi\_flash\_hal\_setup\_read\_suspend

&#x20;                               7   0.01%  0x40088640 .iram0.text

results\\logs\\thread\_analysis.txt:939:Γöé   Γöé           Γöé   Γöé   ΓööΓöÇΓöÇ uart\_hal\_iram.c

&#x20;                             402   0.35%  -

results\\logs\\thread\_analysis.txt:940:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ uart\_hal\_read\_rxfifo

&#x20;                             179   0.16%  0x40089ba8 .iram0.text

results\\logs\\thread\_analysis.txt:941:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ uart\_hal\_rxfifo\_rst

&#x20;                              86   0.07%  0x40089af4 .iram0.text

results\\logs\\thread\_analysis.txt:942:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ uart\_hal\_txfifo\_rst

&#x20;                              47   0.04%  0x40089ac4 .iram0.text

results\\logs\\thread\_analysis.txt:943:Γöé   Γöé           Γöé   Γöé       ΓööΓöÇΓöÇ uart\_hal\_write\_txfifo

&#x20;                              90   0.08%  0x40089b4c .iram0.text

results\\logs\\thread\_analysis.txt:945:Γöé   Γöé           Γöé   Γöé   ΓööΓöÇΓöÇ wdt\_hal\_iram.c

&#x20;                             173   0.15%  -

results\\logs\\thread\_analysis.txt:946:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ wdt\_hal\_disable

&#x20;                              48   0.04%  0x40087de0 .iram0.text

results\\logs\\thread\_analysis.txt:947:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ wdt\_hal\_set\_flashboot\_en

&#x20;                              68   0.06%  0x40087e10 .iram0.text

results\\logs\\thread\_analysis.txt:948:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ wdt\_hal\_write\_protect\_disable

&#x20;                              29   0.03%  0x40087da4 .iram0.text

results\\logs\\thread\_analysis.txt:949:Γöé   Γöé           Γöé   Γöé       ΓööΓöÇΓöÇ wdt\_hal\_write\_protect\_enable

&#x20;                              28   0.02%  0x40087dc4 .iram0.text

results\\logs\\thread\_analysis.txt:952:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ esp\_clk\_apb\_freq

&#x20;                                25   0.02%  0x40080db8 .iram0.text

results\\logs\\thread\_analysis.txt:955:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ esp\_ptr\_executable

&#x20;                                69   0.06%  0x40089a7c .iram0.text

results\\logs\\thread\_analysis.txt:957:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ non\_shared\_periph\_module\_disable

&#x20;                               277   0.24%  0x4008a0d0 .iram0.text

results\\logs\\thread\_analysis.txt:958:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ non\_shared\_periph\_module\_enable

&#x20;                               729   0.63%  0x40089df4 .iram0.text

results\\logs\\thread\_analysis.txt:959:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ periph\_module\_disable

&#x20;                                45   0.04%  0x40089d78 .iram0.text

results\\logs\\thread\_analysis.txt:960:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ periph\_module\_enable

&#x20;                                42   0.04%  0x40089d4c .iram0.text

results\\logs\\thread\_analysis.txt:961:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ periph\_module\_reset

&#x20;                                76   0.07%  0x40089da8 .iram0.text

results\\logs\\thread\_analysis.txt:962:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ periph\_rcc\_acquire\_enter

&#x20;                                16   0.01%  0x40089d28 .iram0.text

results\\logs\\thread\_analysis.txt:963:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ periph\_rcc\_acquire\_exit

&#x20;                                18   0.02%  0x40089d38 .iram0.text

results\\logs\\thread\_analysis.txt:964:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ periph\_rcc\_enter

&#x20;                                27   0.02%  0x40080dd4 .iram0.text

results\\logs\\thread\_analysis.txt:965:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ periph\_rcc\_exit

&#x20;                                46   0.04%  0x40080df0 .iram0.text

results\\logs\\thread\_analysis.txt:972:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ intr\_desc\_table

&#x20;                                   512   0.45%  0x3f400a9c .flash.rodata

results\\logs\\thread\_analysis.txt:974:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_32k\_enable

&#x20;                                    53   0.05%  0x40086ca0 .iram0.text

results\\logs\\thread\_analysis.txt:975:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_32k\_enable\_common                                 137   0.12%  0x40086bd8 .iram0.text

results\\logs\\thread\_analysis.txt:976:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_32k\_enable\_external                                10   0.01%  0x40086cd8 .iram0.text

results\\logs\\thread\_analysis.txt:977:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_8m\_enable

&#x20;                                   130   0.11%  0x40086ce4 .iram0.text

results\\logs\\thread\_analysis.txt:978:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_apb\_freq\_get

&#x20;                                    45   0.04%  0x40087364 .iram0.text

results\\logs\\thread\_analysis.txt:979:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_apb\_freq\_update                                    25   0.02%  0x40080e78 .iram0.text

results\\logs\\thread\_analysis.txt:980:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_bbpll\_disable

&#x20;                                    60   0.05%  0x40086c64 .iram0.text

results\\logs\\thread\_analysis.txt:981:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_cpu\_freq\_get\_config                               140   0.12%  0x40086eb4 .iram0.text

results\\logs\\thread\_analysis.txt:982:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_cpu\_freq\_mhz\_to\_config                             91   0.08%  0x40086e58 .iram0.text

results\\logs\\thread\_analysis.txt:983:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_cpu\_freq\_set\_config                               700   0.61%  0x400870a8 .iram0.text

results\\logs\\thread\_analysis.txt:984:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_cpu\_freq\_to\_pll\_mhz                               320   0.28%  0x40086f68 .iram0.text

results\\logs\\thread\_analysis.txt:985:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_cpu\_freq\_to\_xtal                                  170   0.15%  0x40080e94 .iram0.text

results\\logs\\thread\_analysis.txt:986:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_fast\_src\_set

&#x20;                                    67   0.06%  0x40086e14 .iram0.text

results\\logs\\thread\_analysis.txt:987:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_clk\_get\_lact\_compensation\_delay                        52   0.05%  0x40080e20 .iram0.text

results\\logs\\thread\_analysis.txt:988:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_slow\_src\_get

&#x20;                                    16   0.01%  0x40086e04 .iram0.text

results\\logs\\thread\_analysis.txt:989:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_slow\_src\_set

&#x20;                                   156   0.14%  0x40086d68 .iram0.text

results\\logs\\thread\_analysis.txt:990:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_xtal\_freq\_get

&#x20;                                    36   0.03%  0x40080e54 .iram0.text

results\\logs\\thread\_analysis.txt:991:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ

rtc\_clk\_xtal\_freq\_update                                   40   0.03%  0x40086f40 .iram0.text

results\\logs\\thread\_analysis.txt:993:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_init

&#x20;                                   922   0.80%  0x40087394 .iram0.text

results\\logs\\thread\_analysis.txt:994:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ

rtc\_vddsdio\_get\_config                                    156   0.14%  0x40087730 .iram0.text

results\\logs\\thread\_analysis.txt:995:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ

rtc\_vddsdio\_set\_config                                     72   0.06%  0x400877cc .iram0.text

results\\logs\\thread\_analysis.txt:997:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_cal

&#x20;                                   163   0.14%  0x400879e8 .iram0.text

results\\logs\\thread\_analysis.txt:998:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_cal\_internal

&#x20;                                   465   0.40%  0x40087814 .iram0.text

results\\logs\\thread\_analysis.txt:999:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ rtc\_clk\_freq\_cal

&#x20;                                    28   0.02%  0x40087b30 .iram0.text

results\\logs\\thread\_analysis.txt:1000:Γöé   Γöé           Γöé   Γöé   Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ

rtc\_clk\_wait\_for\_slow\_cycle                               162   0.14%  0x40087a8c .iram0.text

results\\logs\\thread\_analysis.txt:1010:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ regi2c\_ctrl\_read\_reg\_mask

&#x20;                                 37   0.03%  0x4008a1e8 .iram0.text

results\\logs\\thread\_analysis.txt:1011:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ regi2c\_ctrl\_write\_reg

&#x20;                                 32   0.03%  0x4008a210 .iram0.text

results\\logs\\thread\_analysis.txt:1016:Γöé   Γöé           Γöé   Γöé       ΓööΓöÇΓöÇ s\_submode2str

&#x20;                               40   0.03%  0x3f400c9c .flash.rodata

results\\logs\\thread\_analysis.txt:1019:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ cache\_sync

&#x20;                                 22   0.02%  0x40087c94 .iram0.text

results\\logs\\thread\_analysis.txt:1022:Γöé   Γöé           Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ esp\_mmu\_paddr\_find\_caps

&#x20;                                 90   0.08%  0x40080f40 .iram0.text

results\\logs\\thread\_analysis.txt:1027:Γöé   Γöé           Γöé   Γöé               ΓööΓöÇΓöÇ g\_mmu\_mem\_regions

&#x20;                               72   0.06%  0x3f400cc4 .flash.rodata

results\\logs\\thread\_analysis.txt:1028:Γöé   Γöé           Γöé   Γö£ΓöÇΓöÇ esp\_rom

&#x20;                           1022   0.89%  -

results\\logs\\thread\_analysis.txt:1032:Γöé   Γöé           Γöé   Γöé   Γöé           ΓööΓöÇΓöÇ rom

&#x20;                                 14   0.01%  -

results\\logs\\thread\_analysis.txt:1034:Γöé   Γöé           Γöé   Γöé   Γöé                   ΓööΓöÇΓöÇ Cache\_Flush

&#x20;                                 14   0.01%  0x40080c28 .iram0.text

results\\logs\\thread\_analysis.txt:1036:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ esp\_rom\_gpio.c

&#x20;                               70   0.06%  -

results\\logs\\thread\_analysis.txt:1037:Γöé   Γöé           Γöé   Γöé       Γöé   ΓööΓöÇΓöÇ

esp\_rom\_gpio\_connect\_out\_signal                                70   0.06%  0x40080f9c .iram0.text

results\\logs\\thread\_analysis.txt:1038:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ esp\_rom\_serial\_output.c

&#x20;                               64   0.06%  -

results\\logs\\thread\_analysis.txt:1039:Γöé   Γöé           Γöé   Γöé       Γöé   ΓööΓöÇΓöÇ esp\_rom\_output\_tx\_wait\_idle

&#x20;                                 64   0.06%  0x40080fe4 .iram0.text

results\\logs\\thread\_analysis.txt:1040:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ esp\_rom\_spiflash.c

&#x20;                              864   0.75%  -

results\\logs\\thread\_analysis.txt:1041:Γöé   Γöé           Γöé   Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_rom\_spiflash\_read

&#x20;                                720   0.63%  0x4008a2c4 .iram0.text

results\\logs\\thread\_analysis.txt:1042:Γöé   Γöé           Γöé   Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_rom\_spiflash\_read\_status

&#x20;                                 99   0.09%  0x4008a230 .iram0.text

results\\logs\\thread\_analysis.txt:1043:Γöé   Γöé           Γöé   Γöé       Γöé   ΓööΓöÇΓöÇ esp\_rom\_spiflash\_wait\_idle

&#x20;                                 45   0.04%  0x4008a294 .iram0.text

results\\logs\\thread\_analysis.txt:1044:Γöé   Γöé           Γöé   Γöé       ΓööΓöÇΓöÇ esp\_rom\_sys.c

&#x20;                               10   0.01%  -

results\\logs\\thread\_analysis.txt:1045:Γöé   Γöé           Γöé   Γöé           ΓööΓöÇΓöÇ esp\_rom\_set\_cpu\_ticks\_per\_us

&#x20;                               10   0.01%  0x40089c5c .iram0.text

results\\logs\\thread\_analysis.txt:1064:Γöé   Γöé           Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ efuse\_hal\_chip\_revision

&#x20;                                 24   0.02%  0x40081074 .iram0.text

results\\logs\\thread\_analysis.txt:1067:Γöé   Γöé           Γöé   Γöé   Γöé       Γö£ΓöÇΓöÇ

efuse\_hal\_get\_major\_chip\_version                               62   0.05%  0x40081024 .iram0.text

results\\logs\\thread\_analysis.txt:1068:Γöé   Γöé           Γöé   Γöé   Γöé       ΓööΓöÇΓöÇ

efuse\_hal\_get\_minor\_chip\_version                               16   0.01%  0x40081064 .iram0.text

results\\logs\\thread\_analysis.txt:1070:Γöé   Γöé           Γöé   Γöé       Γö£ΓöÇΓöÇ mmu\_hal\_ctx\_init

&#x20;                               14   0.01%  0x40087c40 .iram0.text

results\\logs\\thread\_analysis.txt:1071:Γöé   Γöé           Γöé   Γöé       ΓööΓöÇΓöÇ mmu\_hal\_unmap\_all

&#x20;                               65   0.06%  0x40087c50 .iram0.text

results\\logs\\thread\_analysis.txt:1075:Γöé   Γöé           Γöé   Γöé           ΓööΓöÇΓöÇ GPIO\_PIN\_MUX\_REG

&#x20;                              160   0.14%  0x3f400d2c .flash.rodata

results\\logs\\thread\_analysis.txt:1076:Γöé   Γöé           Γöé   ΓööΓöÇΓöÇ spi\_flash

&#x20;                           5389   4.69%  -

results\\logs\\thread\_analysis.txt:1077:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ esp\_flash\_api.c

&#x20;                            845   0.74%  -

results\\logs\\thread\_analysis.txt:1078:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ check\_chip\_pointer\_default

&#x20;                               31   0.03%  0x40089784 .iram0.text

results\\logs\\thread\_analysis.txt:1079:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ detect\_spi\_flash\_chip

&#x20;                              100   0.09%  0x400897ec .iram0.text

results\\logs\\thread\_analysis.txt:1080:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_get\_physical\_size

&#x20;                               94   0.08%  0x40089874 .iram0.text

results\\logs\\thread\_analysis.txt:1081:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_init\_main

&#x20;                              284   0.25%  0x400898f4 .iram0.text

results\\logs\\thread\_analysis.txt:1082:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_is\_quad\_mode

&#x20;                               29   0.03%  0x400898d4 .iram0.text

results\\logs\\thread\_analysis.txt:1083:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_flash\_read\_chip\_id

&#x20;                               16   0.01%  0x40089864 .iram0.text

results\\logs\\thread\_analysis.txt:1084:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ flash\_end\_flush\_cache

&#x20;                               70   0.06%  0x400897a4 .iram0.text

results\\logs\\thread\_analysis.txt:1085:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ read\_id\_core

&#x20;                               98   0.09%  0x40080c38 .iram0.text

results\\logs\\thread\_analysis.txt:1086:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spiflash\_end\_default

&#x20;                               31   0.03%  0x40089a5c .iram0.text

results\\logs\\thread\_analysis.txt:1087:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spiflash\_start\_core

&#x20;                               75   0.07%  0x40089a10 .iram0.text

results\\logs\\thread\_analysis.txt:1088:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ spiflash\_start\_default

&#x20;                               17   0.01%  0x40089850 .iram0.text

results\\logs\\thread\_analysis.txt:1089:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ esp\_flash\_spi\_init.c

&#x20;                            178   0.15%  -

results\\logs\\thread\_analysis.txt:1091:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ esp\_flash\_init\_default\_chip

&#x20;                              168   0.15%  0x4008a88c .loader.text

results\\logs\\thread\_analysis.txt:1092:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ flash\_mmap.c

&#x20;                             90   0.08%  -

results\\logs\\thread\_analysis.txt:1093:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ spi\_flash\_check\_and\_flush\_cache

&#x20;                               90   0.08%  0x40080c9c .iram0.text

results\\logs\\thread\_analysis.txt:1094:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ flash\_ops.c

&#x20;                             19   0.02%  -

results\\logs\\thread\_analysis.txt:1095:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

esp\_mspi\_32bit\_address\_flash\_feature\_check                          7   0.01%  0x400822f0 .iram0.text

results\\logs\\thread\_analysis.txt:1096:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ esp\_mspi\_pin\_init

&#x20;                                5   0.00%  0x400822e0 .iram0.text

results\\logs\\thread\_analysis.txt:1097:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ spi\_flash\_init\_chip\_state

&#x20;                                7   0.01%  0x400822e8 .iram0.text

results\\logs\\thread\_analysis.txt:1099:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ memspi\_host\_flush\_cache

&#x20;                               25   0.02%  0x400896c0 .iram0.text

results\\logs\\thread\_analysis.txt:1100:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ memspi\_host\_init\_pointers

&#x20;                               56   0.05%  0x400896dc .iram0.text

results\\logs\\thread\_analysis.txt:1101:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ memspi\_host\_read\_data\_slicer

&#x20;                               42   0.04%  0x40089748 .iram0.text

results\\logs\\thread\_analysis.txt:1102:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ memspi\_host\_read\_id\_hs

&#x20;                              126   0.11%  0x40089640 .iram0.text

results\\logs\\thread\_analysis.txt:1103:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ memspi\_host\_read\_status\_hs

&#x20;                               58   0.05%  0x40089604 .iram0.text

results\\logs\\thread\_analysis.txt:1104:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ memspi\_host\_write\_data\_slicer

&#x20;                               51   0.04%  0x40089714 .iram0.text

results\\logs\\thread\_analysis.txt:1105:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_drivers.c

&#x20;                              5   0.00%  -

results\\logs\\thread\_analysis.txt:1106:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ spi\_flash\_chip\_list\_check

&#x20;                                5   0.00%  0x400dbd18 .text

results\\logs\\thread\_analysis.txt:1107:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_gd.c

&#x20;                            247   0.22%  -

results\\logs\\thread\_analysis.txt:1108:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_gd\_detect\_size

&#x20;                               52   0.05%  0x4008875c .iram0.text

results\\logs\\thread\_analysis.txt:1109:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_gd\_get\_caps

&#x20;                               25   0.02%  0x40088740 .iram0.text

results\\logs\\thread\_analysis.txt:1110:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_gd\_get\_io\_mode

&#x20;                               26   0.02%  0x400886ec .iram0.text

results\\logs\\thread\_analysis.txt:1111:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_gd\_probe

&#x20;                               59   0.05%  0x40088790 .iram0.text

results\\logs\\thread\_analysis.txt:1112:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_gd\_set\_io\_mode

&#x20;                               56   0.05%  0x40088708 .iram0.text

results\\logs\\thread\_analysis.txt:1113:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ spi\_flash\_chip\_gd\_suspend\_cmd\_conf

&#x20;                               29   0.03%  0x400886cc .iram0.text

results\\logs\\thread\_analysis.txt:1114:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic.c

&#x20;                           2571   2.24%  -

results\\logs\\thread\_analysis.txt:1115:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_config\_host\_io\_mode                        246   0.21%  0x40088824 .iram0.text

results\\logs\\thread\_analysis.txt:1116:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_detect\_size

&#x20;                               67   0.06%  0x40089040 .iram0.text

results\\logs\\thread\_analysis.txt:1117:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_erase\_block

&#x20;                              194   0.17%  0x40088d04 .iram0.text

results\\logs\\thread\_analysis.txt:1118:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_erase\_chip

&#x20;                              134   0.12%  0x4008908c .iram0.text

results\\logs\\thread\_analysis.txt:1119:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_erase\_sector                               194   0.17%  0x40088dc8 .iram0.text

results\\logs\\thread\_analysis.txt:1120:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_get\_caps

&#x20;                              105   0.09%  0x4008891c .iram0.text

results\\logs\\thread\_analysis.txt:1121:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_get\_io\_mode

&#x20;                               26   0.02%  0x40088f44 .iram0.text

results\\logs\\thread\_analysis.txt:1122:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_get\_write\_protect                           44   0.04%  0x40088ad4 .iram0.text

results\\logs\\thread\_analysis.txt:1123:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_page\_program                               168   0.15%  0x40088e8c .iram0.text

results\\logs\\thread\_analysis.txt:1124:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_probe

&#x20;                                7   0.01%  0x40089084 .iram0.text

results\\logs\\thread\_analysis.txt:1125:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_read

&#x20;                              151   0.13%  0x400889a8 .iram0.text

results\\logs\\thread\_analysis.txt:1126:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_read\_reg

&#x20;                               18   0.02%  0x40089164 .iram0.text

results\\logs\\thread\_analysis.txt:1127:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_read\_unique\_id                             108   0.09%  0x40088b40 .iram0.text

results\\logs\\thread\_analysis.txt:1128:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_read\_unique\_id\_none                          8   0.01%  0x400891f8 .iram0.text

results\\logs\\thread\_analysis.txt:1129:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_reset

&#x20;                               85   0.07%  0x400887cc .iram0.text

results\\logs\\thread\_analysis.txt:1130:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_set\_io\_mode

&#x20;                               24   0.02%  0x40089028 .iram0.text

results\\logs\\thread\_analysis.txt:1131:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_set\_write\_protect                           79   0.07%  0x40089114 .iram0.text

results\\logs\\thread\_analysis.txt:1132:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_suspend\_cmd\_conf                            29   0.03%  0x40088988 .iram0.text

results\\logs\\thread\_analysis.txt:1133:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_wait\_idle

&#x20;                              126   0.11%  0x40089178 .iram0.text

results\\logs\\thread\_analysis.txt:1134:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_write

&#x20;                              148   0.13%  0x40088a40 .iram0.text

results\\logs\\thread\_analysis.txt:1135:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_generic\_write\_encrypted                            168   0.15%  0x40088bac .iram0.text

results\\logs\\thread\_analysis.txt:1136:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_generic\_yield

&#x20;                               62   0.05%  0x40088b00 .iram0.text

results\\logs\\thread\_analysis.txt:1137:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_common\_read\_qe\_sr$constprop$0$isra$0                     52   0.05%  0x40088c54 .iram0.text

results\\logs\\thread\_analysis.txt:1138:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_common\_read\_status\_16b\_rdsr\_rdsr2                        52   0.05%  0x40088c88 .iram0.text

results\\logs\\thread\_analysis.txt:1139:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_common\_read\_status\_8b\_rdsr                               16   0.01%  0x40088f60 .iram0.text

results\\logs\\thread\_analysis.txt:1140:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_common\_read\_status\_8b\_rdsr2                              16   0.01%  0x40088f34 .iram0.text

results\\logs\\thread\_analysis.txt:1141:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_common\_set\_io\_mode

&#x20;                              135   0.12%  0x40088fa0 .iram0.text

results\\logs\\thread\_analysis.txt:1142:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_common\_write\_qe\_sr$isra$0                                46   0.04%  0x40088cbc .iram0.text

results\\logs\\thread\_analysis.txt:1143:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_common\_write\_status\_16b\_wrsr                             21   0.02%  0x40088cec .iram0.text

results\\logs\\thread\_analysis.txt:1144:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_common\_write\_status\_8b\_wrsr                              21   0.02%  0x40088f70 .iram0.text

results\\logs\\thread\_analysis.txt:1145:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ

spi\_flash\_common\_write\_status\_8b\_wrsr2                             21   0.02%  0x40088f88 .iram0.text

results\\logs\\thread\_analysis.txt:1146:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_issi.c

&#x20;                             89   0.08%  -

results\\logs\\thread\_analysis.txt:1147:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_issi\_get\_caps

&#x20;                                7   0.01%  0x40089254 .iram0.text

results\\logs\\thread\_analysis.txt:1148:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_issi\_get\_io\_mode

&#x20;                               26   0.02%  0x40089214 .iram0.text

results\\logs\\thread\_analysis.txt:1149:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_issi\_probe

&#x20;                               36   0.03%  0x40089230 .iram0.text

results\\logs\\thread\_analysis.txt:1150:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ spi\_flash\_chip\_issi\_set\_io\_mode

&#x20;                               20   0.02%  0x40089200 .iram0.text

results\\logs\\thread\_analysis.txt:1151:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_mxic.c

&#x20;                            102   0.09%  -

results\\logs\\thread\_analysis.txt:1152:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_mxic\_detect\_size

&#x20;                               67   0.06%  0x40089278 .iram0.text

results\\logs\\thread\_analysis.txt:1153:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_mxic\_get\_caps

&#x20;                                7   0.01%  0x400892bc .iram0.text

results\\logs\\thread\_analysis.txt:1154:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ spi\_flash\_chip\_mxic\_probe

&#x20;                               28   0.02%  0x4008925c .iram0.text

results\\logs\\thread\_analysis.txt:1155:Γöé   Γöé           Γöé       Γö£ΓöÇΓöÇ spi\_flash\_chip\_winbond.c

&#x20;                            821   0.71%  -

results\\logs\\thread\_analysis.txt:1156:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_winbond\_erase\_block

&#x20;                              224   0.20%  0x4008937c .iram0.text

results\\logs\\thread\_analysis.txt:1157:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_winbond\_erase\_sector                               224   0.20%  0x4008945c .iram0.text

results\\logs\\thread\_analysis.txt:1158:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_winbond\_get\_caps

&#x20;                               25   0.02%  0x400895e8 .iram0.text

results\\logs\\thread\_analysis.txt:1159:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ

spi\_flash\_chip\_winbond\_page\_program                               149   0.13%  0x4008953c .iram0.text

results\\logs\\thread\_analysis.txt:1160:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_winbond\_probe

&#x20;                               19   0.02%  0x400895d4 .iram0.text

results\\logs\\thread\_analysis.txt:1161:Γöé   Γöé           Γöé       Γöé   Γö£ΓöÇΓöÇ spi\_flash\_chip\_winbond\_read

&#x20;                              151   0.13%  0x400892e4 .iram0.text

results\\logs\\thread\_analysis.txt:1162:Γöé   Γöé           Γöé       Γöé   ΓööΓöÇΓöÇ

spi\_flash\_chip\_winbond\_suspend\_cmd\_conf                            29   0.03%  0x400892c4 .iram0.text

results\\logs\\thread\_analysis.txt:1163:Γöé   Γöé           Γöé       ΓööΓöÇΓöÇ spi\_flash\_os\_func\_noos.c

&#x20;                             64   0.06%  -

results\\logs\\thread\_analysis.txt:1164:Γöé   Γöé           Γöé           Γö£ΓöÇΓöÇ delay\_us

&#x20;                             16   0.01%  0x40089774 .iram0.text

results\\logs\\thread\_analysis.txt:1165:Γöé   Γöé           Γöé           Γö£ΓöÇΓöÇ end

&#x20;                             24   0.02%  0x40080cf8 .iram0.text

results\\logs\\thread\_analysis.txt:1166:Γöé   Γöé           Γöé           ΓööΓöÇΓöÇ start

&#x20;                             24   0.02%  0x40080d10 .iram0.text

results\\logs\\thread\_analysis.txt:1170:Γöé   Γöé               Γöé   Γöé   ΓööΓöÇΓöÇ esp\_console\_init

&#x20;                               90   0.08%  0x40086280 .iram0.text

results\\logs\\thread\_analysis.txt:1171:Γöé   Γöé               Γöé   Γö£ΓöÇΓöÇ flash\_init.c

&#x20;                             42   0.04%  -

results\\logs\\thread\_analysis.txt:1172:Γöé   Γöé               Γöé   Γöé   ΓööΓöÇΓöÇ esp\_flash\_config

&#x20;                               42   0.04%  0x40085e3c .iram0.text

results\\logs\\thread\_analysis.txt:1174:Γöé   Γöé               Γöé       Γö£ΓöÇΓöÇ check\_bootloader\_validity

&#x20;                            178   0.15%  0x40086670 .iram0.text

results\\logs\\thread\_analysis.txt:1175:Γöé   Γöé               Γöé       Γö£ΓöÇΓöÇ config\_wdt

&#x20;                             66   0.06%  0x4008662c .iram0.text

results\\logs\\thread\_analysis.txt:1176:Γöé   Γöé               Γöé       Γö£ΓöÇΓöÇ print\_banner

&#x20;                             42   0.04%  0x400865d8 .iram0.text

results\\logs\\thread\_analysis.txt:1177:Γöé   Γöé               Γöé       ΓööΓöÇΓöÇ read\_bootloader\_header

&#x20;                             38   0.03%  0x40086604 .iram0.text

results\\logs\\thread\_analysis.txt:1180:Γöé   Γöé               Γöé       Γö£ΓöÇΓöÇ soc\_flash\_init.c

&#x20;                           1037   0.90%  -

results\\logs\\thread\_analysis.txt:1181:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ flash\_cs\_timing\_config

&#x20;                              110   0.10%  0x40085e78 .iram0.text

results\\logs\\thread\_analysis.txt:1182:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ flash\_dummy\_config

&#x20;                              145   0.13%  0x400860dc .iram0.text

results\\logs\\thread\_analysis.txt:1183:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ flash\_gpio\_config

&#x20;                              498   0.43%  0x40085ee8 .iram0.text

results\\logs\\thread\_analysis.txt:1184:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ flash\_update\_id

&#x20;                               13   0.01%  0x40085e68 .iram0.text

results\\logs\\thread\_analysis.txt:1185:Γöé   Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ init\_spi\_flash

&#x20;                              271   0.24%  0x40086170 .iram0.text

results\\logs\\thread\_analysis.txt:1187:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ ana\_clock\_glitch\_reset\_config

&#x20;                                5   0.00%  0x400868ec .iram0.text

results\\logs\\thread\_analysis.txt:1188:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ bootloader\_clock\_configure

&#x20;                              194   0.17%  0x40086820 .iram0.text

results\\logs\\thread\_analysis.txt:1189:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ check\_wdt\_reset

&#x20;                               46   0.04%  0x400867b0 .iram0.text

results\\logs\\thread\_analysis.txt:1190:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ reset\_mmu

&#x20;                               64   0.06%  0x400867e0 .iram0.text

results\\logs\\thread\_analysis.txt:1191:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ soc\_hw\_init

&#x20;                                5   0.00%  0x400868e4 .iram0.text

results\\logs\\thread\_analysis.txt:1192:Γöé   Γöé               Γöé       Γöé   Γö£ΓöÇΓöÇ wdt\_reset\_cpu0\_info\_enable

&#x20;                               39   0.03%  0x40086788 .iram0.text

results\\logs\\thread\_analysis.txt:1193:Γöé   Γöé               Γöé       Γöé   ΓööΓöÇΓöÇ wdt\_reset\_info\_dump

&#x20;                               98   0.09%  0x40086724 .iram0.text

results\\logs\\thread\_analysis.txt:1195:Γöé   Γöé               Γöé           Γö£ΓöÇΓöÇ soc\_random\_disable

&#x20;                            281   0.24%  0x400864bc .iram0.text

results\\logs\\thread\_analysis.txt:1196:Γöé   Γöé               Γöé           ΓööΓöÇΓöÇ soc\_random\_enable

&#x20;                            479   0.42%  0x400862dc .iram0.text

results\\logs\\thread\_analysis.txt:1199:Γöé   Γöé                       ΓööΓöÇΓöÇ bootloader\_flash.c

&#x20;                         1457   1.27%  -

results\\logs\\thread\_analysis.txt:1201:Γöé   Γöé                           Γö£ΓöÇΓöÇ bootloader\_execute\_flash\_command

&#x20;                           32   0.03%  0x400812d8 .iram0.text

results\\logs\\thread\_analysis.txt:1202:Γöé   Γöé                           Γö£ΓöÇΓöÇ

bootloader\_flash\_execute\_command\_common                       586   0.51%  0x4008108c .iram0.text

results\\logs\\thread\_analysis.txt:1203:Γöé   Γöé                           Γö£ΓöÇΓöÇ bootloader\_flash\_read\_sfdp

&#x20;                           33   0.03%  0x40081424 .iram0.text

results\\logs\\thread\_analysis.txt:1204:Γöé   Γöé                           Γö£ΓöÇΓöÇ bootloader\_flash\_unlock\_default

&#x20;                          300   0.26%  0x400812f8 .iram0.text

results\\logs\\thread\_analysis.txt:1205:Γöé   Γöé                           Γö£ΓöÇΓöÇ bootloader\_flash\_xmc\_startup

&#x20;                          136   0.12%  0x4008146c .iram0.text

results\\logs\\thread\_analysis.txt:1206:Γöé   Γöé                           Γö£ΓöÇΓöÇ bootloader\_read\_flash\_id

&#x20;                           36   0.03%  0x40081448 .iram0.text

results\\logs\\thread\_analysis.txt:1207:Γöé   Γöé                           Γö£ΓöÇΓöÇ esp\_rom\_flash\_read

&#x20;                          237   0.21%  0x4008a60c .loader.text

results\\logs\\thread\_analysis.txt:1208:Γöé   Γöé                           ΓööΓöÇΓöÇ is\_xmc\_chip\_strict

&#x20;                           78   0.07%  0x400822f8 .iram0.text

results\\logs\\thread\_analysis.txt:1223:    Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ arch\_irq\_connect\_dynamic

&#x20;                             14   0.01%  0x40082e80 .iram0.text

results\\logs\\thread\_analysis.txt:1224:    Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ z\_isr\_install

&#x20;                             20   0.02%  0x40082e6c .iram0.text

results\\logs\\thread\_analysis.txt:1226:    Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ arch\_bss\_zero

&#x20;                             19   0.02%  0x40082ea4 .iram0.text

results\\logs\\thread\_analysis.txt:1227:    Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ arch\_early\_memset

&#x20;                             18   0.02%  0x40082e90 .iram0.text

results\\logs\\thread\_analysis.txt:1229:    Γöé   Γöé       ΓööΓöÇΓöÇ z\_get\_sw\_isr\_table\_idx

&#x20;                            5   0.00%  0x40082eb8 .iram0.text

results\\logs\\thread\_analysis.txt:1233:    Γöé           Γöé   ΓööΓöÇΓöÇ arch\_cpu\_idle

&#x20;                            8   0.01%  0x40082e5c .iram0.text

results\\logs\\thread\_analysis.txt:1235:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_exccause

&#x20;                           23   0.02%  0x40082460 .iram0.text

results\\logs\\thread\_analysis.txt:1236:    Γöé           Γöé   ΓööΓöÇΓöÇ xtensa\_fatal\_error

&#x20;                           38   0.03%  0x40082478 .iram0.text

results\\logs\\thread\_analysis.txt:1238:    Γöé           Γöé   ΓööΓöÇΓöÇ z\_irq\_spurious

&#x20;                           68   0.06%  0x400826c4 .iram0.text

results\\logs\\thread\_analysis.txt:1240:    Γöé           Γöé   ΓööΓöÇΓöÇ z\_prep\_c

&#x20;                           44   0.04%  0x40082c9c .iram0.text

results\\logs\\thread\_analysis.txt:1242:    Γöé           Γöé   Γö£ΓöÇΓöÇ arch\_coprocessors\_disable

&#x20;                            8   0.01%  0x40082e64 .iram0.text

results\\logs\\thread\_analysis.txt:1243:    Γöé           Γöé   ΓööΓöÇΓöÇ arch\_new\_thread

&#x20;                           56   0.05%  0x40082708 .iram0.text

results\\logs\\thread\_analysis.txt:1245:    Γöé           Γöé   Γö£ΓöÇΓöÇ return\_to

&#x20;                           20   0.02%  0x4008278c .iram0.text

results\\logs\\thread\_analysis.txt:1246:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_dump\_stack

&#x20;                           20   0.02%  0x400829ec .iram0.text

results\\logs\\thread\_analysis.txt:1247:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_dump\_stack$part$0

&#x20;                          462   0.40%  0x400827b4 .iram0.text

results\\logs\\thread\_analysis.txt:1248:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_excint1\_c

&#x20;                          514   0.45%  0x40082a98 .iram0.text

results\\logs\\thread\_analysis.txt:1249:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_handle\_irq\_lvl

&#x20;                           76   0.07%  0x40082740 .iram0.text

results\\logs\\thread\_analysis.txt:1250:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_int2\_c

&#x20;                           21   0.02%  0x40082a00 .iram0.text

results\\logs\\thread\_analysis.txt:1251:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_int3\_c

&#x20;                           21   0.02%  0x40082a18 .iram0.text

results\\logs\\thread\_analysis.txt:1252:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_int4\_c

&#x20;                           21   0.02%  0x40082a30 .iram0.text

results\\logs\\thread\_analysis.txt:1253:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_int5\_c

&#x20;                           21   0.02%  0x40082a48 .iram0.text

results\\logs\\thread\_analysis.txt:1254:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_int6\_c

&#x20;                           21   0.02%  0x40082a60 .iram0.text

results\\logs\\thread\_analysis.txt:1255:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_is\_frame\_pointer\_valid

&#x20;                           40   0.03%  0x400829c4 .iram0.text

results\\logs\\thread\_analysis.txt:1256:    Γöé           Γöé   Γö£ΓöÇΓöÇ xtensa\_is\_outside\_stack\_bounds

&#x20;                           62   0.05%  0x40082984 .iram0.text

results\\logs\\thread\_analysis.txt:1257:    Γöé           Γöé   ΓööΓöÇΓöÇ xtensa\_nmi\_c

&#x20;                           29   0.03%  0x40082a78 .iram0.text

results\\logs\\thread\_analysis.txt:1259:    Γöé               Γö£ΓöÇΓöÇ xtensa\_backtrace\_get\_next\_frame

&#x20;                         58   0.05%  0x40082d18 .iram0.text

results\\logs\\thread\_analysis.txt:1260:    Γöé               Γö£ΓöÇΓöÇ xtensa\_backtrace\_print

&#x20;                        264   0.23%  0x40082d54 .iram0.text

results\\logs\\thread\_analysis.txt:1261:    Γöé               Γö£ΓöÇΓöÇ xtensa\_cpu\_process\_stack\_pc

&#x20;                         43   0.04%  0x40082cc8 .iram0.text

results\\logs\\thread\_analysis.txt:1262:    Γöé               ΓööΓöÇΓöÇ xtensa\_stack\_ptr\_is\_sane

&#x20;                         36   0.03%  0x40082cf4 .iram0.text

results\\logs\\thread\_analysis.txt:1266:    Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ \_\_dev\_dt\_meta\_dts\_ord\_39

&#x20;                              4   0.00%  0x3f400e04 .flash.rodata

results\\logs\\thread\_analysis.txt:1267:    Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ \_\_dev\_dt\_nodelabels\_dts\_ord\_39

&#x20;                              8   0.01%  0x3f400e08 .flash.rodata

results\\logs\\thread\_analysis.txt:1277:    Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ esp32\_clock\_config0

&#x20;                             20   0.02%  0x3f400e10 .flash.rodata

results\\logs\\thread\_analysis.txt:1286:    Γöé   Γöé       Γö£ΓöÇΓöÇ console\_out

&#x20;                           34   0.03%  0x40087c1c .iram0.text

results\\logs\\thread\_analysis.txt:1290:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_meta\_dts\_ord\_103

&#x20;                            4   0.00%  0x3f400e24 .flash.rodata

results\\logs\\thread\_analysis.txt:1291:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_meta\_dts\_ord\_8

&#x20;                            4   0.00%  0x3f400e30 .flash.rodata

results\\logs\\thread\_analysis.txt:1292:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_nodelabels\_dts\_ord\_103

&#x20;                            8   0.01%  0x3f400e28 .flash.rodata

results\\logs\\thread\_analysis.txt:1293:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_nodelabels\_dts\_ord\_8

&#x20;                            8   0.01%  0x3f400e34 .flash.rodata

results\\logs\\thread\_analysis.txt:1299:    Γöé   Γöé       Γö£ΓöÇΓöÇ gpio\_esp32\_config

&#x20;                          945   0.82%  0x400815c4 .iram0.text

results\\logs\\thread\_analysis.txt:1301:    Γöé   Γöé       Γö£ΓöÇΓöÇ gpio\_esp32\_fire\_callbacks

&#x20;                          171   0.15%  0x40082380 .iram0.text

results\\logs\\thread\_analysis.txt:1304:    Γöé   Γöé       Γö£ΓöÇΓöÇ gpio\_esp32\_isr

&#x20;                           17   0.01%  0x400815b0 .iram0.text

results\\logs\\thread\_analysis.txt:1318:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_meta\_dts\_ord\_104

&#x20;                            4   0.00%  0x3f400e48 .flash.rodata

results\\logs\\thread\_analysis.txt:1319:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_dev\_dt\_nodelabels\_dts\_ord\_104

&#x20;                            8   0.01%  0x3f400e4c .flash.rodata

results\\logs\\thread\_analysis.txt:1322:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_pinctrl\_dev\_config\_\_device\_dts\_ord\_104

&#x20;                            8   0.01%  0x3f400e8c .flash.rodata

results\\logs\\thread\_analysis.txt:1323:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_pinctrl\_state\_pins\_0\_\_device\_dts\_ord\_104

&#x20;                           16   0.01%  0x3f400e9c .flash.rodata

results\\logs\\thread\_analysis.txt:1324:    Γöé   Γöé       Γö£ΓöÇΓöÇ \_\_pinctrl\_states\_\_device\_dts\_ord\_104

&#x20;                            8   0.01%  0x3f400e94 .flash.rodata

results\\logs\\thread\_analysis.txt:1325:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_esp32\_config\_0

&#x20;                           56   0.05%  0x3f400e54 .flash.rodata

results\\logs\\thread\_analysis.txt:1330:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_esp32\_init

&#x20;                          438   0.38%  0x40081d58 .iram0.text

results\\logs\\thread\_analysis.txt:1331:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_esp32\_isr

&#x20;                           92   0.08%  0x40081cfc .iram0.text

results\\logs\\thread\_analysis.txt:1333:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_esp32\_transfer

&#x20;                          927   0.81%  0x40081f10 .iram0.text

results\\logs\\thread\_analysis.txt:1334:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_esp32\_transmit

&#x20;                           80   0.07%  0x40081c18 .iram0.text

results\\logs\\thread\_analysis.txt:1335:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_esp32\_write\_addr

&#x20;                          146   0.13%  0x40081c68 .iram0.text

results\\logs\\thread\_analysis.txt:1336:    Γöé   Γöé       Γö£ΓöÇΓöÇ i2c\_hw\_fsm\_reset

&#x20;                          670   0.58%  0x40081978 .iram0.text

results\\logs\\thread\_analysis.txt:1342:    Γöé   Γöé       Γö£ΓöÇΓöÇ esp\_intr\_disable

&#x20;                          159   0.14%  0x40081510 .iram0.text

results\\logs\\thread\_analysis.txt:1347:    Γöé   Γöé       ΓööΓöÇΓöÇ shared\_intr\_isr

&#x20;                           53   0.05%  0x40082348 .iram0.text

results\\logs\\thread\_analysis.txt:1352:    Γöé   Γöé       Γö£ΓöÇΓöÇ esp32\_gpio\_ports\_addrs

&#x20;                            8   0.01%  0x3f400eac .flash.rodata

results\\logs\\thread\_analysis.txt:1358:    Γöé   Γöé           Γöé   Γö£ΓöÇΓöÇ \_\_dev\_dt\_meta\_dts\_ord\_105

&#x20;                              4   0.00%  0x3f400eb4 .flash.rodata

results\\logs\\thread\_analysis.txt:1359:    Γöé   Γöé           Γöé   Γö£ΓöÇΓöÇ \_\_dev\_dt\_nodelabels\_dts\_ord\_105

&#x20;                              8   0.01%  0x3f400eb8 .flash.rodata

results\\logs\\thread\_analysis.txt:1365:    Γöé   Γöé           Γöé   Γö£ΓöÇΓöÇ bme280\_config\_0

&#x20;                             12   0.01%  0x3f400ec0 .flash.rodata

results\\logs\\thread\_analysis.txt:1374:    Γöé   Γöé               Γö£ΓöÇΓöÇ bme280\_bus\_io\_i2c

&#x20;                           12   0.01%  0x3f400ecc .flash.rodata

results\\logs\\thread\_analysis.txt:1401:    Γöé   Γöé       Γö£ΓöÇΓöÇ uart\_esp32\_isr

&#x20;                           46   0.04%  0x400822b0 .iram0.text

results\\logs\\thread\_analysis.txt:1407:    Γöé           Γö£ΓöÇΓöÇ ccompare\_isr

&#x20;                         47   0.04%  0x40087b4c .iram0.text

results\\logs\\thread\_analysis.txt:1408:    Γöé           Γö£ΓöÇΓöÇ sys\_clock\_cycle\_get\_32

&#x20;                          8   0.01%  0x40087c14 .iram0.text

results\\logs\\thread\_analysis.txt:1409:    Γöé           Γö£ΓöÇΓöÇ sys\_clock\_driver\_init

&#x20;                         33   0.03%  0x40087bf0 .iram0.text

results\\logs\\thread\_analysis.txt:1410:    Γöé           Γö£ΓöÇΓöÇ sys\_clock\_elapsed

&#x20;                         25   0.02%  0x40087bd4 .iram0.text

results\\logs\\thread\_analysis.txt:1411:    Γöé           ΓööΓöÇΓöÇ sys\_clock\_set\_timeout

&#x20;                         86   0.07%  0x40087b7c .iram0.text

results\\logs\\thread\_analysis.txt:1436:    Γöé       Γöé   Γöé   ΓööΓöÇΓöÇ z\_log\_notify\_drop

&#x20;                             10   0.01%  0x40085008 .iram0.text

results\\logs\\thread\_analysis.txt:1438:    Γöé       Γöé   Γöé   Γö£ΓöÇΓöÇ log\_msg\_generic\_get\_wlen

&#x20;                             36   0.03%  0x40085340 .iram0.text

results\\logs\\thread\_analysis.txt:1441:    Γöé       Γöé       Γö£ΓöÇΓöÇ log\_output\_flush

&#x20;                           24   0.02%  0x4008567c .iram0.text

results\\logs\\thread\_analysis.txt:1442:    Γöé       Γöé       ΓööΓöÇΓöÇ log\_output\_write

&#x20;                           26   0.02%  0x40085a44 .iram0.text

results\\logs\\thread\_analysis.txt:1449:    Γöé           Γöé   Γö£ΓöÇΓöÇ atomic\_inc

&#x20;                           27   0.02%  0x4008536c .iram0.text

results\\logs\\thread\_analysis.txt:1452:    Γöé           Γöé   ΓööΓöÇΓöÇ z\_cbprintf\_cpy

&#x20;                           43   0.04%  0x40085390 .iram0.text

results\\logs\\thread\_analysis.txt:1454:    Γöé           Γöé   ΓööΓöÇΓöÇ sys\_dlist\_remove

&#x20;                           19   0.02%  0x40084be0 .iram0.text

results\\logs\\thread\_analysis.txt:1462:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_impl\_k\_busy\_wait

&#x20;                           32   0.03%  0x40082ec0 .iram0.text

results\\logs\\thread\_analysis.txt:1464:    Γöé   Γöé   Γö£ΓöÇΓöÇ do\_device\_init

&#x20;                           53   0.05%  0x40084af8 .iram0.text

results\\logs\\thread\_analysis.txt:1465:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_device\_get\_all\_static

&#x20;                           19   0.02%  0x40082efc .iram0.text

results\\logs\\thread\_analysis.txt:1466:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_device\_init

&#x20;                           26   0.02%  0x40082ee0 .iram0.text

results\\logs\\thread\_analysis.txt:1467:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_impl\_device\_is\_ready

&#x20;                           28   0.02%  0x40084b30 .iram0.text

results\\logs\\thread\_analysis.txt:1469:    Γöé   Γöé   Γö£ΓöÇΓöÇ event\_walk\_op

&#x20;                           66   0.06%  0x400848b4 .iram0.text

results\\logs\\thread\_analysis.txt:1470:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_event\_post\_internal

&#x20;                           64   0.06%  0x40084804 .iram0.text

results\\logs\\thread\_analysis.txt:1471:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_event\_wait\_internal

&#x20;                          112   0.10%  0x40084844 .iram0.text

results\\logs\\thread\_analysis.txt:1472:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_event\_clear

&#x20;                           16   0.01%  0x40084908 .iram0.text

results\\logs\\thread\_analysis.txt:1473:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_event\_init

&#x20;                           13   0.01%  0x40084c68 .iram0.text

results\\logs\\thread\_analysis.txt:1474:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_event\_post

&#x20;                           16   0.01%  0x400848f8 .iram0.text

results\\logs\\thread\_analysis.txt:1475:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_impl\_k\_event\_wait

&#x20;                           26   0.02%  0x40084918 .iram0.text

results\\logs\\thread\_analysis.txt:1477:    Γöé   Γöé   Γö£ΓöÇΓöÇ arch\_system\_halt

&#x20;                            9   0.01%  0x40084b4c .iram0.text

results\\logs\\thread\_analysis.txt:1478:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_sys\_fatal\_error\_handler

&#x20;                           30   0.03%  0x40082f10 .iram0.text

results\\logs\\thread\_analysis.txt:1479:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_fatal\_error

&#x20;                          188   0.16%  0x40082f30 .iram0.text

results\\logs\\thread\_analysis.txt:1481:    Γöé   Γöé   ΓööΓöÇΓöÇ idle

&#x20;                           12   0.01%  0x400832b0 .iram0.text

results\\logs\\thread\_analysis.txt:1486:    Γöé   Γöé   Γöé   Γö£ΓöÇΓöÇ unpend\_thread\_no\_timeout

&#x20;                             32   0.03%  0x40084b58 .iram0.text

results\\logs\\thread\_analysis.txt:1487:    Γöé   Γöé   Γöé   ΓööΓöÇΓöÇ unpend\_thread\_no\_timeout

&#x20;                             25   0.02%  0x400839e8 .iram0.text

results\\logs\\thread\_analysis.txt:1489:    Γöé   Γöé       ΓööΓöÇΓöÇ z\_swap$isra$0

&#x20;                           59   0.05%  0x40083af8 .iram0.text

results\\logs\\thread\_analysis.txt:1491:    Γöé   Γöé   Γö£ΓöÇΓöÇ bg\_thread\_main

&#x20;                          174   0.15%  0x40083018 .iram0.text

results\\logs\\thread\_analysis.txt:1493:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_cstart

&#x20;                          160   0.14%  0x40083138 .iram0.text

results\\logs\\thread\_analysis.txt:1494:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_init\_cpu

&#x20;                          111   0.10%  0x400830c8 .iram0.text

results\\logs\\thread\_analysis.txt:1495:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_sys\_init\_run\_level

&#x20;                           44   0.04%  0x40082fec .iram0.text

results\\logs\\thread\_analysis.txt:1498:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_heap\_alloc

&#x20;                           28   0.02%  0x4008326c .iram0.text

results\\logs\\thread\_analysis.txt:1499:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_heap\_free

&#x20;                           40   0.03%  0x40083288 .iram0.text

results\\logs\\thread\_analysis.txt:1500:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_heap\_init

&#x20;                           23   0.02%  0x40083230 .iram0.text

results\\logs\\thread\_analysis.txt:1501:    Γöé   Γöé   Γö£ΓöÇΓöÇ statics\_init

&#x20;                           34   0.03%  0x40083248 .iram0.text

results\\logs\\thread\_analysis.txt:1502:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_heap\_alloc\_helper

&#x20;                           86   0.07%  0x400831d8 .iram0.text

results\\logs\\thread\_analysis.txt:1504:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_free

&#x20;                           25   0.02%  0x40084abc .iram0.text

results\\logs\\thread\_analysis.txt:1505:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_malloc

&#x20;                           20   0.02%  0x40084ad8 .iram0.text

results\\logs\\thread\_analysis.txt:1506:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_thread\_system\_pool\_assign

&#x20;                           11   0.01%  0x40084aec .iram0.text

results\\logs\\thread\_analysis.txt:1507:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_alloc\_helper

&#x20;                           43   0.04%  0x40084c9c .iram0.text

results\\logs\\thread\_analysis.txt:1509:    Γöé   Γöé   Γö£ΓöÇΓöÇ put\_msg\_in\_queue

&#x20;                          189   0.16%  0x400832bc .iram0.text

results\\logs\\thread\_analysis.txt:1510:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_msgq\_get

&#x20;                          176   0.15%  0x40083390 .iram0.text

results\\logs\\thread\_analysis.txt:1511:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_impl\_k\_msgq\_put

&#x20;                           20   0.02%  0x4008337c .iram0.text

results\\logs\\thread\_analysis.txt:1513:    Γöé   Γöé   Γö£ΓöÇΓöÇ adjust\_owner\_prio$isra$0

&#x20;                           28   0.02%  0x40083440 .iram0.text

results\\logs\\thread\_analysis.txt:1514:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_mutex\_init

&#x20;                           17   0.01%  0x40084b78 .iram0.text

results\\logs\\thread\_analysis.txt:1515:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_mutex\_lock

&#x20;                          187   0.16%  0x4008345c .iram0.text

results\\logs\\thread\_analysis.txt:1516:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_impl\_k\_mutex\_unlock

&#x20;                          138   0.12%  0x40083518 .iram0.text

results\\logs\\thread\_analysis.txt:1518:    Γöé   Γöé   Γö£ΓöÇΓöÇ add\_to\_waitq\_locked

&#x20;                           84   0.07%  0x40083b60 .iram0.text

results\\logs\\thread\_analysis.txt:1519:    Γöé   Γöé   Γö£ΓöÇΓöÇ move\_current\_to\_end\_of\_prio\_q

&#x20;                          120   0.10%  0x40083bb4 .iram0.text

results\\logs\\thread\_analysis.txt:1520:    Γöé   Γöé   Γö£ΓöÇΓöÇ ready\_thread

&#x20;                          152   0.13%  0x40083a60 .iram0.text

results\\logs\\thread\_analysis.txt:1521:    Γöé   Γöé   Γö£ΓöÇΓöÇ reschedule$isra$0

&#x20;                           44   0.04%  0x40083b34 .iram0.text

results\\logs\\thread\_analysis.txt:1522:    Γöé   Γöé   Γö£ΓöÇΓöÇ unready\_thread

&#x20;                           90   0.08%  0x40083a04 .iram0.text

results\\logs\\thread\_analysis.txt:1523:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_get\_next\_switch\_handle

&#x20;                           32   0.03%  0x40083fec .iram0.text

results\\logs\\thread\_analysis.txt:1524:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_pend\_curr

&#x20;                           41   0.04%  0x40083e9c .iram0.text

results\\logs\\thread\_analysis.txt:1525:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_ready\_thread

&#x20;                           19   0.02%  0x40083c2c .iram0.text

results\\logs\\thread\_analysis.txt:1526:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_reschedule

&#x20;                           10   0.01%  0x40083fe0 .iram0.text

results\\logs\\thread\_analysis.txt:1527:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_sched\_lock\_reschedule

&#x20;                           74   0.06%  0x40083d68 .iram0.text

results\\logs\\thread\_analysis.txt:1528:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_sched\_ready\_locked

&#x20;                           10   0.01%  0x40083c40 .iram0.text

results\\logs\\thread\_analysis.txt:1529:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_sched\_unready\_locked

&#x20;                           10   0.01%  0x40083c4c .iram0.text

results\\logs\\thread\_analysis.txt:1530:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_sched\_wake\_thread\_locked

&#x20;                           42   0.04%  0x40083e50 .iram0.text

results\\logs\\thread\_analysis.txt:1531:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_sched\_yield

&#x20;                          132   0.11%  0x40083db4 .iram0.text

results\\logs\\thread\_analysis.txt:1532:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_thread\_halt

&#x20;                          272   0.24%  0x40083c58 .iram0.text

results\\logs\\thread\_analysis.txt:1533:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_thread\_prio\_set

&#x20;                          243   0.21%  0x40083eec .iram0.text

results\\logs\\thread\_analysis.txt:1534:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_thread\_suspend\_current

&#x20;                           76   0.07%  0x40084040 .iram0.text

results\\logs\\thread\_analysis.txt:1535:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_thread\_timeout

&#x20;                           29   0.03%  0x40083e7c .iram0.text

results\\logs\\thread\_analysis.txt:1536:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_unpend1\_no\_timeout

&#x20;                           34   0.03%  0x40083ec8 .iram0.text

results\\logs\\thread\_analysis.txt:1537:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_unpend\_all

&#x20;                           52   0.05%  0x4008400c .iram0.text

results\\logs\\thread\_analysis.txt:1538:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_unpend\_thread\_no\_timeout

&#x20;                           24   0.02%  0x40083e38 .iram0.text

results\\logs\\thread\_analysis.txt:1540:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_sched\_lock

&#x20;                           27   0.02%  0x4008413c .iram0.text

results\\logs\\thread\_analysis.txt:1541:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_sched\_unlock

&#x20;                           27   0.02%  0x40084158 .iram0.text

results\\logs\\thread\_analysis.txt:1542:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_sched\_current\_thread\_query

&#x20;                           10   0.01%  0x40084174 .iram0.text

results\\logs\\thread\_analysis.txt:1543:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_sched\_init

&#x20;                           15   0.01%  0x4008412c .iram0.text

results\\logs\\thread\_analysis.txt:1544:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_sched\_waitq\_walk

&#x20;                           84   0.07%  0x40084bf4 .iram0.text

results\\logs\\thread\_analysis.txt:1546:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_sem\_give

&#x20;                           96   0.08%  0x400835a4 .iram0.text

results\\logs\\thread\_analysis.txt:1547:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_sem\_init

&#x20;                           25   0.02%  0x40084b8c .iram0.text

results\\logs\\thread\_analysis.txt:1548:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_impl\_k\_sem\_take

&#x20;                           58   0.05%  0x40083604 .iram0.text

results\\logs\\thread\_analysis.txt:1550:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_sleep

&#x20;                           47   0.04%  0x400840fc .iram0.text

results\\logs\\thread\_analysis.txt:1551:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_tick\_sleep

&#x20;                          112   0.10%  0x4008408c .iram0.text

results\\logs\\thread\_analysis.txt:1556:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_can\_yield

&#x20;                           50   0.04%  0x400839ac .iram0.text

results\\logs\\thread\_analysis.txt:1557:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_is\_in\_isr

&#x20;                           15   0.01%  0x40084ba8 .iram0.text

results\\logs\\thread\_analysis.txt:1558:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_thread\_name\_get

&#x20;                            8   0.01%  0x40084bb8 .iram0.text

results\\logs\\thread\_analysis.txt:1559:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_thread\_runtime\_stats\_all\_get

&#x20;                          100   0.09%  0x400837ec .iram0.text

results\\logs\\thread\_analysis.txt:1560:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_thread\_runtime\_stats\_get

&#x20;                           37   0.03%  0x400837c4 .iram0.text

results\\logs\\thread\_analysis.txt:1561:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_thread\_state\_str

&#x20;                          117   0.10%  0x40083668 .iram0.text

results\\logs\\thread\_analysis.txt:1562:    Γöé   Γöé   Γö£ΓöÇΓöÇ state\_string$0

&#x20;                           64   0.06%  0x3f400ed8 .flash.rodata

results\\logs\\thread\_analysis.txt:1563:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_dummy\_thread\_init

&#x20;                           39   0.03%  0x40083850 .iram0.text

results\\logs\\thread\_analysis.txt:1564:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_thread\_abort

&#x20;                           10   0.01%  0x400839a0 .iram0.text

results\\logs\\thread\_analysis.txt:1565:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_thread\_create

&#x20;                           82   0.07%  0x40083920 .iram0.text

results\\logs\\thread\_analysis.txt:1566:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_thread\_name\_set

&#x20;                           40   0.03%  0x40083640 .iram0.text

results\\logs\\thread\_analysis.txt:1567:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_thread\_resume

&#x20;                           50   0.04%  0x400838b4 .iram0.text

results\\logs\\thread\_analysis.txt:1568:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_thread\_stack\_space\_get

&#x20;                           21   0.02%  0x400837ac .iram0.text

results\\logs\\thread\_analysis.txt:1569:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_thread\_suspend

&#x20;                           58   0.05%  0x40083878 .iram0.text

results\\logs\\thread\_analysis.txt:1570:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_wakeup

&#x20;                           56   0.05%  0x400838e8 .iram0.text

results\\logs\\thread\_analysis.txt:1571:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_yield

&#x20;                            8   0.01%  0x400839e0 .iram0.text

results\\logs\\thread\_analysis.txt:1572:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_setup\_new\_thread

&#x20;                          203   0.18%  0x400836e0 .iram0.text

results\\logs\\thread\_analysis.txt:1573:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_stack\_space\_get

&#x20;                           31   0.03%  0x40084bc0 .iram0.text

results\\logs\\thread\_analysis.txt:1574:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_thread\_abort

&#x20;                           43   0.04%  0x40083974 .iram0.text

results\\logs\\thread\_analysis.txt:1576:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_thread\_foreach

&#x20;                           14   0.01%  0x400842dc .iram0.text

results\\logs\\thread\_analysis.txt:1577:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_thread\_foreach\_unlocked

&#x20;                           14   0.01%  0x400842ec .iram0.text

results\\logs\\thread\_analysis.txt:1578:    Γöé   Γöé   Γö£ΓöÇΓöÇ thread\_foreach\_helper$constprop$0

&#x20;                           58   0.05%  0x40084270 .iram0.text

results\\logs\\thread\_analysis.txt:1579:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_thread\_monitor\_exit

&#x20;                           46   0.04%  0x400842ac .iram0.text

results\\logs\\thread\_analysis.txt:1581:    Γöé   Γöé   Γö£ΓöÇΓöÇ elapsed

&#x20;                           22   0.02%  0x40084350 .iram0.text

results\\logs\\thread\_analysis.txt:1582:    Γöé   Γöé   Γö£ΓöÇΓöÇ next\_timeout

&#x20;                           66   0.06%  0x4008430c .iram0.text

results\\logs\\thread\_analysis.txt:1583:    Γöé   Γöé   Γö£ΓöÇΓöÇ sys\_clock\_announce\_locked

&#x20;                          195   0.17%  0x4008451c .iram0.text

results\\logs\\thread\_analysis.txt:1584:    Γöé   Γöé   Γö£ΓöÇΓöÇ sys\_clock\_tick\_get

&#x20;                           32   0.03%  0x400845e0 .iram0.text

results\\logs\\thread\_analysis.txt:1585:    Γöé   Γöé   Γö£ΓöÇΓöÇ sys\_clock\_tick\_get\_32

&#x20;                           10   0.01%  0x40084600 .iram0.text

results\\logs\\thread\_analysis.txt:1586:    Γöé   Γöé   Γö£ΓöÇΓöÇ sys\_timepoint\_calc

&#x20;                           66   0.06%  0x4008461c .iram0.text

results\\logs\\thread\_analysis.txt:1587:    Γöé   Γöé   Γö£ΓöÇΓöÇ sys\_timepoint\_timeout

&#x20;                           66   0.06%  0x40084660 .iram0.text

results\\logs\\thread\_analysis.txt:1588:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_add\_timeout

&#x20;                          282   0.25%  0x40084368 .iram0.text

results\\logs\\thread\_analysis.txt:1589:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_uptime\_ticks

&#x20;                           15   0.01%  0x4008460c .iram0.text

results\\logs\\thread\_analysis.txt:1590:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_timeout\_inflight\_superseded

&#x20;                           33   0.03%  0x400844f8 .iram0.text

results\\logs\\thread\_analysis.txt:1591:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_try\_abort\_timeout

&#x20;                          116   0.10%  0x40084484 .iram0.text

results\\logs\\thread\_analysis.txt:1593:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_timeout\_q\_first

&#x20;                           15   0.01%  0x400842fc .iram0.text

results\\logs\\thread\_analysis.txt:1595:    Γöé   Γöé   Γö£ΓöÇΓöÇ k\_timer\_init

&#x20;                           32   0.03%  0x40084c48 .iram0.text

results\\logs\\thread\_analysis.txt:1596:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_timer\_start

&#x20;                           48   0.04%  0x40084790 .iram0.text

results\\logs\\thread\_analysis.txt:1597:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_k\_timer\_stop

&#x20;                           67   0.06%  0x400847c0 .iram0.text

results\\logs\\thread\_analysis.txt:1598:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_timer\_expiration\_handler

&#x20;                          236   0.21%  0x400846a4 .iram0.text

results\\logs\\thread\_analysis.txt:1600:    Γöé   Γöé   Γö£ΓöÇΓöÇ slice\_reset

&#x20;                           58   0.05%  0x400841e4 .iram0.text

results\\logs\\thread\_analysis.txt:1601:    Γöé   Γöé   Γö£ΓöÇΓöÇ slice\_timeout

&#x20;                           30   0.03%  0x400841c4 .iram0.text

results\\logs\\thread\_analysis.txt:1602:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_time\_slice

&#x20;                           64   0.06%  0x40084230 .iram0.text

results\\logs\\thread\_analysis.txt:1603:    Γöé   Γöé   Γö£ΓöÇΓöÇ z\_time\_slice\_reset

&#x20;                           13   0.01%  0x40084220 .iram0.text

results\\logs\\thread\_analysis.txt:1604:    Γöé   Γöé   ΓööΓöÇΓöÇ z\_time\_slice\_size

&#x20;                           66   0.06%  0x40084180 .iram0.text

results\\logs\\thread\_analysis.txt:1606:    Γöé       Γö£ΓöÇΓöÇ sched\_cpu\_update\_usage

&#x20;                         34   0.03%  0x40084c78 .iram0.text

results\\logs\\thread\_analysis.txt:1607:    Γöé       Γö£ΓöÇΓöÇ z\_sched\_cpu\_usage

&#x20;                        210   0.18%  0x40084990 .iram0.text

results\\logs\\thread\_analysis.txt:1608:    Γöé       Γö£ΓöÇΓöÇ z\_sched\_thread\_usage

&#x20;                         86   0.07%  0x40084a64 .iram0.text

results\\logs\\thread\_analysis.txt:1609:    Γöé       Γö£ΓöÇΓöÇ z\_sched\_usage\_start

&#x20;                         21   0.02%  0x40084934 .iram0.text

results\\logs\\thread\_analysis.txt:1610:    Γöé       ΓööΓöÇΓöÇ z\_sched\_usage\_stop

&#x20;                         66   0.06%  0x4008494c .iram0.text

results\\logs\\thread\_analysis.txt:1627:    Γöé   Γöé       ΓööΓöÇΓöÇ set\_chunk\_used

&#x20;                           26   0.02%  0x400db89c .text

results\\logs\\thread\_analysis.txt:1679:    Γöé   Γöé       ΓööΓöÇΓöÇ printk

&#x20;                           43   0.04%  0x40084e00 .iram0.text

results\\logs\\thread\_analysis.txt:1702:    Γöé       Γöé       Γö£ΓöÇΓöÇ \_\_start

&#x20;                           95   0.08%  0x40085ddc .iram0.text

results\\logs\\thread\_analysis.txt:1703:    Γöé       Γöé       ΓööΓöÇΓöÇ map\_rom\_segments

&#x20;                          890   0.77%  0x40085a60 .iram0.text

results\\logs\\thread\_analysis.txt:1706:    Γöé           Γöé   ΓööΓöÇΓöÇ hardware\_init

&#x20;                          128   0.11%  0x400868f4 .iram0.text

results\\logs\\thread\_analysis.txt:1708:    Γöé               Γö£ΓöÇΓöÇ \_\_esp\_platform\_app\_start

&#x20;                         15   0.01%  0x40080bfc .iram0.text

results\\logs\\thread\_analysis.txt:1709:    Γöé               Γö£ΓöÇΓöÇ arch\_printk\_char\_out

&#x20;                         27   0.02%  0x40080c0c .iram0.text

results\\logs\\thread\_analysis.txt:1724:        Γöé   Γöé   Γö£ΓöÇΓöÇ activate\_foreach\_backend

&#x20;                           93   0.08%  0x40084e2c .iram0.text

results\\logs\\thread\_analysis.txt:1725:        Γöé   Γöé   Γö£ΓöÇΓöÇ default\_lf\_get\_timestamp

&#x20;                           20   0.02%  0x40084ecc .iram0.text

results\\logs\\thread\_analysis.txt:1726:        Γöé   Γöé   Γö£ΓöÇΓöÇ dropped\_notify

&#x20;                           48   0.04%  0x40085034 .iram0.text

results\\logs\\thread\_analysis.txt:1727:        Γöé   Γöé   Γö£ΓöÇΓöÇ dummy\_timestamp

&#x20;                            7   0.01%  0x40085364 .iram0.text

results\\logs\\thread\_analysis.txt:1728:        Γöé   Γöé   Γö£ΓöÇΓöÇ enable\_logger

&#x20;                           62   0.05%  0x40084e8c .iram0.text

results\\logs\\thread\_analysis.txt:1730:        Γöé   Γöé   Γö£ΓöÇΓöÇ log\_core\_init

&#x20;                           73   0.06%  0x4008507c .iram0.text

results\\logs\\thread\_analysis.txt:1731:        Γöé   Γöé   Γö£ΓöÇΓöÇ log\_process\_thread\_func

&#x20;                          133   0.12%  0x40085240 .iram0.text

results\\logs\\thread\_analysis.txt:1732:        Γöé   Γöé   Γö£ΓöÇΓöÇ log\_process\_thread\_timer\_expiry\_fn

&#x20;                           11   0.01%  0x40084ee0 .iram0.text

results\\logs\\thread\_analysis.txt:1733:        Γöé   Γöé   Γö£ΓöÇΓöÇ log\_set\_timestamp\_func

&#x20;                           26   0.02%  0x40084f9c .iram0.text

results\\logs\\thread\_analysis.txt:1734:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_log\_panic

&#x20;                           66   0.06%  0x400851fc .iram0.text

results\\logs\\thread\_analysis.txt:1735:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_log\_process

&#x20;                          230   0.20%  0x40085114 .iram0.text

results\\logs\\thread\_analysis.txt:1736:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_dropped

&#x20;                           52   0.05%  0x40084fd4 .iram0.text

results\\logs\\thread\_analysis.txt:1737:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_dropped\_read\_and\_clear

&#x20;                           29   0.03%  0x40085014 .iram0.text

results\\logs\\thread\_analysis.txt:1738:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_get\_tag

&#x20;                            7   0.01%  0x40085388 .iram0.text

results\\logs\\thread\_analysis.txt:1739:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_init

&#x20;                          144   0.13%  0x40084eec .iram0.text

results\\logs\\thread\_analysis.txt:1740:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_alloc

&#x20;                           22   0.02%  0x400850c8 .iram0.text

results\\logs\\thread\_analysis.txt:1741:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_commit

&#x20;                           29   0.03%  0x40085320 .iram0.text

results\\logs\\thread\_analysis.txt:1742:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_free

&#x20;                           18   0.02%  0x400850f0 .iram0.text

results\\logs\\thread\_analysis.txt:1743:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_init

&#x20;                           24   0.02%  0x40085064 .iram0.text

results\\logs\\thread\_analysis.txt:1744:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_local\_claim

&#x20;                           13   0.01%  0x400850e0 .iram0.text

results\\logs\\thread\_analysis.txt:1745:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_pending

&#x20;                           13   0.01%  0x40085104 .iram0.text

results\\logs\\thread\_analysis.txt:1746:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_post\_finalize

&#x20;                           85   0.07%  0x400852c8 .iram0.text

results\\logs\\thread\_analysis.txt:1747:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_notify\_backend\_enabled

&#x20;                           27   0.02%  0x40084fb8 .iram0.text

results\\logs\\thread\_analysis.txt:1748:        Γöé   Γöé   ΓööΓöÇΓöÇ z\_log\_vprintk

&#x20;                           31   0.03%  0x40084f7c .iram0.text

results\\logs\\thread\_analysis.txt:1761:        Γöé   Γöé   Γö£ΓöÇΓöÇ log\_msg\_get\_source\_id

&#x20;                           23   0.02%  0x40085664 .iram0.text

results\\logs\\thread\_analysis.txt:1762:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_z\_log\_msg\_simple\_create\_0

&#x20;                           18   0.02%  0x40085450 .iram0.text

results\\logs\\thread\_analysis.txt:1763:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_z\_log\_msg\_simple\_create\_1

&#x20;                           23   0.02%  0x40085464 .iram0.text

results\\logs\\thread\_analysis.txt:1764:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_z\_log\_msg\_simple\_create\_2

&#x20;                           22   0.02%  0x4008547c .iram0.text

results\\logs\\thread\_analysis.txt:1765:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_impl\_z\_log\_msg\_static\_create

&#x20;                          270   0.24%  0x40085494 .iram0.text

results\\logs\\thread\_analysis.txt:1766:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_finalize

&#x20;                           50   0.04%  0x400853bc .iram0.text

results\\logs\\thread\_analysis.txt:1767:        Γöé   Γöé   Γö£ΓöÇΓöÇ z\_log\_msg\_runtime\_vcreate

&#x20;                          192   0.17%  0x400855a4 .iram0.text

results\\logs\\thread\_analysis.txt:1768:        Γöé   Γöé   ΓööΓöÇΓöÇ z\_log\_msg\_simple\_create

&#x20;                           95   0.08%  0x400853f0 .iram0.text

results\\logs\\thread\_analysis.txt:1770:        Γöé       Γö£ΓöÇΓöÇ cr\_out\_func

&#x20;                         26   0.02%  0x4008570c .iram0.text

results\\logs\\thread\_analysis.txt:1771:        Γöé       Γö£ΓöÇΓöÇ log\_output\_dropped\_process

&#x20;                         68   0.06%  0x400859d4 .iram0.text

results\\logs\\thread\_analysis.txt:1772:        Γöé       Γö£ΓöÇΓöÇ log\_output\_msg\_process

&#x20;                         78   0.07%  0x40085984 .iram0.text

results\\logs\\thread\_analysis.txt:1773:        Γöé       Γö£ΓöÇΓöÇ log\_output\_process

&#x20;                        604   0.53%  0x40085728 .iram0.text

results\\logs\\thread\_analysis.txt:1774:        Γöé       Γö£ΓöÇΓöÇ log\_output\_timestamp\_freq\_set

&#x20;                         43   0.04%  0x40085a18 .iram0.text

results\\logs\\thread\_analysis.txt:1775:        Γöé       Γö£ΓöÇΓöÇ newline\_print

&#x20;                         22   0.02%  0x400856c0 .iram0.text

results\\logs\\thread\_analysis.txt:1776:        Γöé       Γö£ΓöÇΓöÇ out\_func

&#x20;                         50   0.04%  0x400856d8 .iram0.text

results\\logs\\thread\_analysis.txt:1777:        Γöé       ΓööΓöÇΓöÇ print\_formatted

&#x20;                         44   0.04%  0x40085694 .iram0.text

results\\logs\\thread\_analysis.txt:1799:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_fprintf

&#x20;                         20   0.02%  0x3f400280 .flash.rodata

results\\logs\\thread\_analysis.txt:1800:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_log\_backend

&#x20;                         24   0.02%  0x3f400294 .flash.rodata

results\\logs\\thread\_analysis.txt:1801:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_log\_output

&#x20;                         16   0.01%  0x3f4002c0 .flash.rodata

results\\logs\\thread\_analysis.txt:1802:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_mpsc\_buffer\_config

&#x20;                         20   0.02%  0x3f4002ac .flash.rodata

results\\logs\\thread\_analysis.txt:1803:            Γöé       Γö£ΓöÇΓöÇ shell\_uart\_transport\_api

&#x20;                         24   0.02%  0x3f4002d0 .flash.rodata

results\\logs\\thread\_analysis.txt:1809:            Γöé   Γöé   Γö£ΓöÇΓöÇ \_shell\_date

&#x20;                           20   0.02%  0x3f4001d8 .flash.rodata

results\\logs\\thread\_analysis.txt:1814:            Γöé   Γöé   Γö£ΓöÇΓöÇ shell\_sub\_date

&#x20;                           60   0.05%  0x3f4001f0 .flash.rodata

results\\logs\\thread\_analysis.txt:1815:            Γöé   Γöé   ΓööΓöÇΓöÇ sub\_date

&#x20;                            4   0.00%  0x3f4001ec .flash.rodata

results\\logs\\thread\_analysis.txt:1817:            Γöé   Γöé   Γö£ΓöÇΓöÇ \_shell\_device

&#x20;                           20   0.02%  0x3f400178 .flash.rodata

results\\logs\\thread\_analysis.txt:1825:            Γöé   Γöé   Γö£ΓöÇΓöÇ shell\_sub\_device

&#x20;                           60   0.05%  0x3f400190 .flash.rodata

results\\logs\\thread\_analysis.txt:1826:            Γöé   Γöé   ΓööΓöÇΓöÇ sub\_device

&#x20;                            4   0.00%  0x3f40018c .flash.rodata

results\\logs\\thread\_analysis.txt:1828:            Γöé   Γöé   Γö£ΓöÇΓöÇ \_shell\_devmem

&#x20;                           20   0.02%  0x3f40022c .flash.rodata

results\\logs\\thread\_analysis.txt:1835:            Γöé   Γöé   Γö£ΓöÇΓöÇ shell\_sub\_devmem

&#x20;                           60   0.05%  0x3f400244 .flash.rodata

results\\logs\\thread\_analysis.txt:1836:            Γöé   Γöé   ΓööΓöÇΓöÇ sub\_devmem

&#x20;                            4   0.00%  0x3f400240 .flash.rodata

results\\logs\\thread\_analysis.txt:1842:            Γöé       Γöé   Γö£ΓöÇΓöÇ \_shell\_kernel

&#x20;                           20   0.02%  0x3f400164 .flash.rodata

results\\logs\\thread\_analysis.txt:1881:            Γöé   Γö£ΓöÇΓöÇ \_shell\_help

&#x20;                         20   0.02%  0x3f4003b4 .flash.rodata

results\\logs\\thread\_analysis.txt:1897:            Γöé   Γö£ΓöÇΓöÇ shell\_prompt\_change

&#x20;                         82   0.07%  0x400d61dc .text

results\\logs\\thread\_analysis.txt:1908:            Γöé   Γö£ΓöÇΓöÇ \_shell\_clear

&#x20;                         20   0.02%  0x3f400434 .flash.rodata

results\\logs\\thread\_analysis.txt:1909:            Γöé   Γö£ΓöÇΓöÇ \_shell\_history

&#x20;                         20   0.02%  0x3f40040c .flash.rodata

results\\logs\\thread\_analysis.txt:1910:            Γöé   Γö£ΓöÇΓöÇ \_shell\_rem

&#x20;                         20   0.02%  0x3f400448 .flash.rodata

results\\logs\\thread\_analysis.txt:1911:            Γöé   Γö£ΓöÇΓöÇ \_shell\_resize

&#x20;                         20   0.02%  0x3f4003f8 .flash.rodata

results\\logs\\thread\_analysis.txt:1912:            Γöé   Γö£ΓöÇΓöÇ \_shell\_retval

&#x20;                         20   0.02%  0x3f4003e4 .flash.rodata

results\\logs\\thread\_analysis.txt:1913:            Γöé   Γö£ΓöÇΓöÇ \_shell\_shell

&#x20;                         20   0.02%  0x3f400420 .flash.rodata

results\\logs\\thread\_analysis.txt:1925:            Γöé   Γö£ΓöÇΓöÇ cmd\_get\_terminal\_size$0

&#x20;                          5   0.00%  0x3f40461e .flash.rodata

results\\logs\\thread\_analysis.txt:1927:            Γöé   Γö£ΓöÇΓöÇ cmd\_prompt\_off

&#x20;                         18   0.02%  0x400d78e4 .text

results\\logs\\thread\_analysis.txt:1928:            Γöé   Γö£ΓöÇΓöÇ cmd\_prompt\_on

&#x20;                         17   0.01%  0x400d78d0 .text

results\\logs\\thread\_analysis.txt:1935:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_backspace\_mode

&#x20;                          4   0.00%  0x3f40052c .flash.rodata

results\\logs\\thread\_analysis.txt:1936:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_colors

&#x20;                          4   0.00%  0x3f40066c .flash.rodata

results\\logs\\thread\_analysis.txt:1937:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_echo

&#x20;                          4   0.00%  0x3f4005ac .flash.rodata

results\\logs\\thread\_analysis.txt:1938:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_prompt

&#x20;                          4   0.00%  0x3f4005ec .flash.rodata

results\\logs\\thread\_analysis.txt:1939:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_resize

&#x20;                          4   0.00%  0x3f40045c .flash.rodata

results\\logs\\thread\_analysis.txt:1940:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_shell

&#x20;                          4   0.00%  0x3f400488 .flash.rodata

results\\logs\\thread\_analysis.txt:1941:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_shell\_stats

&#x20;                          4   0.00%  0x3f40056c .flash.rodata

results\\logs\\thread\_analysis.txt:1942:            Γöé   Γö£ΓöÇΓöÇ m\_sub\_vt100

&#x20;                          4   0.00%  0x3f40062c .flash.rodata

results\\logs\\thread\_analysis.txt:1949:            Γöé   Γö£ΓöÇΓöÇ shell\_m\_sub\_backspace\_mode

&#x20;                         60   0.05%  0x3f400530 .flash.rodata

results\\logs\\thread\_analysis.txt:1950:            Γöé   Γö£ΓöÇΓöÇ shell\_m\_sub\_colors

&#x20;                         60   0.05%  0x3f400670 .flash.rodata

results\\logs\\thread\_analysis.txt:1951:            Γöé   Γö£ΓöÇΓöÇ shell\_m\_sub\_echo

&#x20;                         60   0.05%  0x3f4005b0 .flash.rodata

results\\logs\\thread\_analysis.txt:1952:            Γöé   Γö£ΓöÇΓöÇ shell\_m\_sub\_prompt

&#x20;                         60   0.05%  0x3f4005f0 .flash.rodata

results\\logs\\thread\_analysis.txt:1953:            Γöé   Γö£ΓöÇΓöÇ shell\_m\_sub\_resize

&#x20;                         40   0.03%  0x3f400460 .flash.rodata

results\\logs\\thread\_analysis.txt:1954:            Γöé   Γö£ΓöÇΓöÇ shell\_m\_sub\_shell

&#x20;                        160   0.14%  0x3f40048c .flash.rodata

results\\logs\\thread\_analysis.txt:1955:            Γöé   Γö£ΓöÇΓöÇ shell\_m\_sub\_shell\_stats

&#x20;                         60   0.05%  0x3f400570 .flash.rodata

results\\logs\\thread\_analysis.txt:1956:            Γöé   ΓööΓöÇΓöÇ shell\_m\_sub\_vt100

&#x20;                         60   0.05%  0x3f400630 .flash.rodata

results\\logs\\thread\_analysis.txt:1963:            Γöé   Γö£ΓöÇΓöÇ cmd\_sep$0

&#x20;                          4   0.00%  0x3f4045fd .flash.rodata

results\\logs\\thread\_analysis.txt:1966:            Γöé   Γö£ΓöÇΓöÇ tabulator$2

&#x20;                          3   0.00%  0x3f404601 .flash.rodata

results\\logs\\thread\_analysis.txt:1977:            Γöé   Γö£ΓöÇΓöÇ log\_backend\_shell\_api

&#x20;                         28   0.02%  0x3f4003c8 .flash.rodata

results\\logs\\thread\_analysis.txt:1981:            Γöé   Γö£ΓöÇΓöÇ process\_msg\_from\_buffer

&#x20;                         60   0.05%  0x400d73a4 .text

results\\logs\\thread\_analysis.txt:1989:            Γöé   Γö£ΓöÇΓöÇ reprint\_from\_cursor

&#x20;                        206   0.18%  0x400d7058 .text

results\\logs\\thread\_analysis.txt:2007:            Γöé   Γö£ΓöÇΓöÇ z\_shell\_op\_delete\_from\_cursor

&#x20;                         30   0.03%  0x400d6d04 .text

results\\logs\\thread\_analysis.txt:2013:            Γöé   Γö£ΓöÇΓöÇ z\_shell\_print\_prompt\_and\_cmd

&#x20;                         43   0.04%  0x400d7270 .text

results\\logs\\thread\_analysis.txt:2078:rst:0x1 (POWERON\_RESET),boot:0x13 (SPI\_FAST\_FLASH\_BOOT)

results\\logs\\thread\_analysis.txt:2090:I (flash\_init): SPI Speed      : 40MHz

results\\logs\\thread\_analysis.txt:2091:I (flash\_init): SPI Mode       : DIO

results\\logs\\thread\_analysis.txt:2092:I (flash\_init): SPI Flash Size : 4MB

results\\logs\\thread\_analysis.txt:2093:I (boot): DRAM  : lma=00001020h vma=3ffb0000h size=020f0h (  8432)

results\\logs\\thread\_analysis.txt:2094:I (boot): IRAM  : lma=00003118h vma=40080000h size=0a950h ( 43344)

results\\logs\\thread\_analysis.txt:2096:I (boot): IROM  : lma=00010000h vma=400d0000h size=0c6d0h ( 50896)

results\\logs\\thread\_analysis.txt:2097:I (boot): DROM  : lma=00020000h vma=3f400000h size=10000h ( 65536)

results\\logs\\thread\_analysis.txt:2099:I (spi\_flash): detected chip: generic

results\\logs\\thread\_analysis.txt:2100:I (spi\_flash): flash io: dio

results\\logs\\thread\_analysis.txt:2136:queue\_used\_count: 0 samples

results\\logs\\thread\_analysis.txt:2162:Use this output to record allocated stack, used stack high-water, and unused

stack.

results\\logs\\thread\_analysis.txt:2164:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_proc     : STACK: unused  896 usage

1152 / 2048 ( 56 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2165:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

239645

results\\logs\\thread\_analysis.txt:2166:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_acq      : STACK: unused 1248 usage

800 / 2048 ( 39 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2167:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

710611

results\\logs\\thread\_analysis.txt:2168:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J shell\_uart          : STACK: unused  144 usage

1904 / 2048 ( 92 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2169:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

2847505

results\\logs\\thread\_analysis.txt:2170:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J logging             : STACK: unused  736 usage

288 / 1024 ( 28 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2171:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used: 67005

results\\logs\\thread\_analysis.txt:2172:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J idle                : STACK: unused  816 usage

208 / 1024 ( 20 %); CPU:  99 %

results\\logs\\thread\_analysis.txt:2173:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

10576768260

results\\logs\\thread\_analysis.txt:2174:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J ISR0                : STACK: unused 1504 usage

544 / 2048 ( 26 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2175:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used: 0

results\\logs\\thread\_analysis.txt:2205:Use this output to record allocated stack, used stack high-water, and unused

stack.

results\\logs\\thread\_analysis.txt:2207:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_proc     : STACK: unused  896 usage

1152 / 2048 ( 56 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2208:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

605483

results\\logs\\thread\_analysis.txt:2209:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_acq      : STACK: unused 1248 usage

800 / 2048 ( 39 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2210:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

2263946

results\\logs\\thread\_analysis.txt:2211:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J shell\_uart          : STACK: unused  144 usage

1904 / 2048 ( 92 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2212:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

5597955

results\\logs\\thread\_analysis.txt:2213:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J logging             : STACK: unused  608 usage

416 / 1024 ( 40 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2214:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

166041

results\\logs\\thread\_analysis.txt:2215:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J idle                : STACK: unused  816 usage

208 / 1024 ( 20 %); CPU:  99 %

results\\logs\\thread\_analysis.txt:2216:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

39181013336

results\\logs\\thread\_analysis.txt:2217:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J ISR0                : STACK: unused 1504 usage

544 / 2048 ( 26 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2218:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used: 0

results\\logs\\thread\_analysis.txt:2278:queue\_used\_count: 4 samples

results\\logs\\thread\_analysis.txt:2296:Use this output to record allocated stack, used stack high-water, and unused

stack.

results\\logs\\thread\_analysis.txt:2298:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_proc     : STACK: unused  896 usage

1152 / 2048 ( 56 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2299:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

895931

results\\logs\\thread\_analysis.txt:2300:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_acq      : STACK: unused 1248 usage

800 / 2048 ( 39 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2301:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

3281150

results\\logs\\thread\_analysis.txt:2302:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J shell\_uart          : STACK: unused  144 usage

1904 / 2048 ( 92 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2303:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

10623951

results\\logs\\thread\_analysis.txt:2304:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J logging             : STACK: unused  608 usage

416 / 1024 ( 40 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2305:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

367253

results\\logs\\thread\_analysis.txt:2306:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J idle                : STACK: unused  816 usage

208 / 1024 ( 20 %); CPU:  99 %

results\\logs\\thread\_analysis.txt:2307:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

57101920238

results\\logs\\thread\_analysis.txt:2308:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J ISR0                : STACK: unused 1504 usage

544 / 2048 ( 26 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2309:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used: 0

results\\logs\\thread\_analysis.txt:2369:Use this output to record allocated stack, used stack high-water, and unused

stack.

results\\logs\\thread\_analysis.txt:2371:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_proc     : STACK: unused  896 usage

1152 / 2048 ( 56 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2372:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

1171455

results\\logs\\thread\_analysis.txt:2373:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J fieldsense\_acq      : STACK: unused 1248 usage

800 / 2048 ( 39 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2374:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

4127978

results\\logs\\thread\_analysis.txt:2375:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J shell\_uart          : STACK: unused  144 usage

1904 / 2048 ( 92 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2376:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

14408545

results\\logs\\thread\_analysis.txt:2377:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J logging             : STACK: unused  608 usage

416 / 1024 ( 40 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2378:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

494115

results\\logs\\thread\_analysis.txt:2379:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J idle                : STACK: unused  816 usage

208 / 1024 ( 20 %); CPU:  99 %

results\\logs\\thread\_analysis.txt:2380:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used:

72054374339

results\\logs\\thread\_analysis.txt:2381:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J ISR0                : STACK: unused 1504 usage

544 / 2048 ( 26 %); CPU:   0 %

results\\logs\\thread\_analysis.txt:2382:␛\[1;32mfieldsense> ␛\[m␛\[12D␛\[J                     : Total CPU cycles used: 0



