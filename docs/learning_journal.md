## Entry 3 — Zephyr environment check

### 1. What I was trying to achieve

I was trying to verify my Zephyr development environment before writing application code or choosing an ESP32 board target.

### 2. What concept I learned

I learned that Zephyr development depends on the shell environment. Even before writing code, tools like `west`, Python, CMake, and the Zephyr workspace must be available from the terminal.

### 3. What I changed

I saved the Zephyr environment check output in `results/logs/zephyr_environment_check.txt`.

### 4. How I tested it

I started a PowerShell transcript and ran `west --version`, `where.exe west`, and `Get-Command west`.

### 5. What actually happened

PowerShell could not find the `west` command. `where.exe west` also could not find a west executable.

### 6. Any problem and its root cause

The root cause is not fully confirmed yet. The current evidence shows that west is not available in this PowerShell environment. It may not be installed, may not be on PATH, or may require activation of a Python virtual environment.

### 7. What I would explain in an interview

I would explain that I checked the Zephyr toolchain before writing firmware. When `west` was not recognized, I treated it as an environment setup issue and documented the exact evidence instead of changing project code randomly.

### 8. Blog-style paragraph

During the Zephyr environment check, I found that my current PowerShell session could not recognize the `west` command. I saved the error output in the project logs and documented it in the debug journal. This was useful because it separated a toolchain problem from a firmware problem and gave me a clear next step before board bring-up.