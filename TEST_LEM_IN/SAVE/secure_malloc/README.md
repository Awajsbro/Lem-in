# Secure malloc

## Description
This small python program permits to check if malloc are secured in C programs by infecting executable file.

## How to run
### Step 1: compile your program and run the following command
```
python mc.py EXE_FILE [arg]
```
### Step 2: in case of unsecure malloc, display the .sym_logs file to get memory address of your issues
```
cat .sym_logs
```
### Step 3: run otool to find the cause of your issue
```
otool -tVj EXE_FILE.infected | grep @malloc -a40
```
