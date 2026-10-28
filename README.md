# SysMonitor (C++ Windows API)

A lightweight, low-level command-line utility built in C++ that interfaces directly with the Windows OS kernel to provide real-time hardware telemetry. 

## Features
* **Real-Time Memory Tracking:** Queries the OS kernel to track total, available, and consumed physical RAM natively.
* **CPU Architecture Polling:** Extracts logical processor counts and architecture details via system-level structs.
* **Optimized Rendering Loop:** Utilizes thread-sleeping mechanisms (`std::chrono`) to maintain a 1Hz refresh rate with near-zero CPU overhead.

## Technologies Used
* **Language:** Standard C++ (C++11)
* **API:** Native Windows API (`<windows.h>`)
* **Libraries:** `<iostream>`, `<thread>`, `<chrono>`

## How to Build and Run
This project requires a Windows environment and a C++ compiler (such as MinGW-w64 or MSVC).

1. Clone the repository:
   `git clone https://github.com/abhirav2108/SysMonitor-Windows.git`
2. Compile via terminal:
   `g++ sysmonitor.cpp -o sysmonitor.exe`
3. Execute the binary:
   `.\sysmonitor.exe`
