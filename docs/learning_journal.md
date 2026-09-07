# Learning Journal

## What I learned

FieldSense-Z helped me practice the difference between making a sensor print values and building a small embedded system that can be validated.

Key lessons:

- verify hardware identity instead of trusting breakout labels
- use I2C ACK only as the first check, not the final proof
- read chip ID to confirm the actual sensor
- keep humidity out of the project when the verified hardware is BMP280
- separate data acquisition from processing using RTOS threads
- use finite queues and define overflow behavior
- measure timing and missed deadlines
- model node health separately from environmental status
- add diagnostic shell commands to make validation easier
- use deterministic fault injection instead of relying only on random failures
- record evidence before marking a test PASS
- measure stack usage instead of guessing

## Most important engineering decisions

The most important decision was to keep the project honest. When the module was identified as BMP280, the project stopped claiming humidity support. When screenshots were not captured, serial logs were used instead. When the first cold boot output was incomplete, the test was rerun instead of marking it PASS without evidence.

## What this project demonstrates

This project demonstrates practical embedded engineering skills:

- Zephyr build and flash workflow
- device-tree based hardware configuration
- sensor driver integration
- C data structures for embedded samples
- RTOS thread design
- queue-based communication
- shell-based diagnostics
- validation discipline
- debugging and documentation
