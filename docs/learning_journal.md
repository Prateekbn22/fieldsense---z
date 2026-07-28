\# FieldSense-Z Learning Journal



\## Entry 1 — Repository initialization



\### 1. What I was trying to achieve



I was trying to start FieldSense-Z in a clean and organized way before writing any sensor code. The goal was to create the repository structure, document the project direction, and keep space for hardware photos, logs, and debugging evidence.



\### 2. What concept I learned



I learned that an embedded project starts before code is written. The exact board, module, connector, sensor breakout, voltage rules, and pin labels affect how the firmware should be configured and tested.



I also learned that Git does not track empty folders, so placeholder files such as `.gitkeep` are useful when I want the repository structure to appear before source code or test results exist.



\### 3. What I changed



I created the initial FieldSense-Z repository structure with folders for source code, headers, board configuration, tests, scripts, documentation, logs, plots, photos, and screenshots.



I added placeholder documentation files for the project overview, component audit, learning journal, and debug journal.



\### 4. How I tested it



I checked the repository using `git status` to confirm that Git could see the new files.



\### 5. What actually happened



TBD after I run the commands and confirm the files exist.



\### 6. Any problem and its root cause



TBD.



\### 7. What I would explain in an interview



I would explain that I did not start by writing sensor code because the hardware was not fully identified yet. Instead, I created a structured repository and documented the unknowns so that board-target selection, I2C wiring, and sensor configuration can be based on evidence.



\### 8. Blog-style paragraph



I started FieldSense-Z by treating project setup as the first engineering task. Instead of immediately writing sensor code, I created a repository structure that separates application code, board configuration, documentation, logs, photos, and debug notes. This gives me a clean base for hardware bring-up because every future test can be tied to real evidence from the board.

