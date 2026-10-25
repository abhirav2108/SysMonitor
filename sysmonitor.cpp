#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

void PrintSystemStats() {
    // Clear the terminal screen to create a static dashboard effect
    system("cls");

    std::cout << "========== SYS-MONITOR DASHBOARD ==========" << std::endl;

    // 1. FETCH CPU INFO
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    
    std::cout << "--- CPU ---" << std::endl;
    std::cout << "Logical Cores: " << sysInfo.dwNumberOfProcessors << std::endl;
    std::cout << "Architecture:  ";
    if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) std::cout << "x64 (64-bit)" << std::endl;
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) std::cout << "ARM" << std::endl;
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) std::cout << "x86 (32-bit)" << std::endl;
    else std::cout << "Unknown" << std::endl;

    // 2. FETCH MEMORY INFO
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    
    if (GlobalMemoryStatusEx(&memInfo)) {
        const double GB = 1024.0 * 1024.0 * 1024.0;
        double totalRAM = memInfo.ullTotalPhys / GB;
        double availRAM = memInfo.ullAvailPhys / GB;
        double usedRAM = totalRAM - availRAM;

        std::cout << "\n--- MEMORY ---" << std::endl;
        std::cout << "Memory Load: " << memInfo.dwMemoryLoad << "%" << std::endl;
        std::cout << "Total RAM:   " << totalRAM << " GB" << std::endl;
        std::cout << "Used RAM:    " << usedRAM << " GB" << std::endl;
        std::cout << "Free RAM:    " << availRAM << " GB" << std::endl;
    }

    std::cout << "===========================================" << std::endl;
    std::cout << "Press Ctrl+C to exit." << std::endl;
}

int main() {
    // Infinite loop to update the dashboard every 1 second
    while (true) {
        PrintSystemStats();
        // Pause the thread for 1 second to prevent maxing out the CPU
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}