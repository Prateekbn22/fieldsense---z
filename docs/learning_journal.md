## Entry 3 — Zephyr environment setup and verification

### 1. What I was trying to achieve

I was trying to install and verify the Zephyr development environment before writing FieldSense-Z application code.

### 2. What concept I learned

I learned that Zephyr development depends on the host environment. The `west` tool, Python virtual environment, Zephyr workspace, CMake, Ninja, Git, and Zephyr SDK must all be available before board bring-up can start.

### 3. What I changed

I installed the missing Zephyr setup pieces and moved the Zephyr workspace to `C:\zephyrproject` to avoid problems caused by spaces in my Windows user path.

### 4. How I tested it

I activated the Zephyr virtual environment and ran `west --version`, `west topdir`, `west list zephyr`, `west boards` filtered for ESP32, `cmake --version`, `ninja --version`, `git --version`, `py -3.12 --version`, and `where.exe 7z`.

### 5. What actually happened

TBD after reviewing `results/logs/zephyr_environment_check.txt`.

### 6. Any problem and its root cause

Earlier, PowerShell could not recognize `west`, and the first Zephyr workspace path caused dependency-install issues because my Windows user path contained spaces. I fixed this by creating a clean Zephyr workspace at `C:\zephyrproject`.

### 7. What I would explain in an interview

I would explain that I verified the Zephyr toolchain before writing firmware. When `west` was missing and the first setup path caused issues, I treated it as an environment problem, documented the evidence, and fixed the setup before moving to board bring-up.

### 8. Blog-style paragraph

Before writing sensor code, I set up and verified the Zephyr environment on Windows. I captured the tool versions and ESP32 board listing in a log file so future build or flash issues can be compared against a known setup state. This step helped me separate toolchain problems from firmware or hardware problems.