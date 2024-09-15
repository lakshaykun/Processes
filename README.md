# Lab 3: Processes

## Overview

This project implements three approaches to measure the elapsed time taken to execute a command in a Unix-like environment. Each method utilizes process management with `fork()`, `exec()`, and `gettimeofday()` functions. The primary objective is to calculate execution time with increasing accuracy, minimizing external factors such as context switches and scheduling delays.

### Part 1: Simplistic Method
The first approach involves measuring the time taken for a command by recording timestamps in the parent process before and after the execution of a child process, which runs the specified command.

### Part 2: Enhanced Methods
To refine the time measurement, we implemented two additional methods where the child process shares the exact start time with the parent:
1. **Shared Memory**: Uses `mmap()` to create shared memory between the parent and child processes to communicate the start time.
2. **Message Passing**: Uses pipes to pass the start time from the child to the parent process.

## Files

- **`time.cpp`**: Implements the simplistic approach (Part 1).
- **`stime.cpp`**: Uses shared memory for more accurate timing (Part 2).
- **`mtime.cpp`**: Uses message passing (pipes) for communication (Part 2).
- **`Makefile`**: Automates compilation and execution of all three programs.

## Compilation

Run the following command to compile the programs:

```bash
make
```

This will generate three executables:
- `bin/time.out`: Simplistic method
- `bin/stime.out`: Shared memory method
- `bin/mtime.out`: Message passing method

## Running the Programs

To run the programs, use the following command after compilation:

```bash
make run
```

This will execute the following:
- **Simplistic method**: Runs the `bin/time.out` program.
- **Shared memory method**: Runs the `bin/stime.out` program.
- **Message passing method**: Runs the `bin/mtime.out` program.

## Comparison of Approaches

1. **Simplistic Method**: The time measured by the parent process includes context switches and scheduling time. While easy to implement, it results in less accurate measurements.
   
2. **Shared Memory Method**: Using shared memory ensures that the parent receives the exact start time from the child process, excluding scheduling delays. This leads to more precise timing.

3. **Message Passing Method**: By using pipes to transfer the start time from the child to the parent, we achieve similar accuracy as with shared memory. This approach adds minimal overhead for passing data but is still more precise than the simplistic method.

## Cleaning Up

To remove object files and executables, run:

```bash
make clean
```

## Conclusion

This project demonstrates how different inter-process communication techniques can affect the accuracy of measuring execution time. The shared memory and message passing methods offer more accurate timing compared to the simplistic approach, as they eliminate delays caused by context switching.
