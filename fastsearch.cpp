#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

// A mutex (Mutual Exclusion) acts like a lock. 
// We use it so that two threads don't try to print to the console at the exact same millisecond and scramble the text.
std::mutex console_mutex;

// This is the "Worker" function that each thread will execute independently
void SearchInFile(std::string filename, std::string keyword) {
    std::ifstream file(filename); // Open the file
    std::string line;
    int lineNumber = 1;

    if (!file.is_open()) {
        // Lock the console, print the error, unlock the console
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    // Read the file line by line
    while (std::getline(file, line)) {
        // If the keyword is found in the line
        if (line.find(keyword) != std::string::npos) {
            
            // LOCK the console so this thread can print its finding without interruption
            std::lock_guard<std::mutex> lock(console_mutex);
            std::cout << "[FOUND in " << filename << " on line " << lineNumber << "]: " << line << std::endl;
            // The lock is automatically released when this block finishes
        }
        lineNumber++;
    }
}

int main() {
    std::cout << "Starting FastSearch..." << std::endl;
    std::string targetKeyword = "ERROR";

    // List of files we want to search
    std::vector<std::string> files = {"server_log1.txt", "server_log2.txt", "big_log3.txt", "big_log4.txt"};
    
    // A vector (list) to hold our threads
    std::vector<std::thread> workers;

    // 1. SPAWN THREADS: For every file, launch a new thread to search it simultaneously
    for (const auto& file : files) {
        workers.push_back(std::thread(SearchInFile, file, targetKeyword));
    }

    // 2. JOIN THREADS: Tell the main program to wait here until all threads finish their jobs
    for (auto& t : workers) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "Search complete." << std::endl;
    return 0;
}