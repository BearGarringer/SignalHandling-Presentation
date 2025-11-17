// graceful_shutdown.cpp - Demonstrates graceful shutdown on SIGINT/SIGTERM
#include <csignal>
#include <iostream>
#include <unistd.h>
#include <atomic>

std::atomic<bool> shutdown_requested(false);

void signal_handler(int signum) {
    const char msg[] = "\nShutdown signal received...\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    shutdown_requested = true;
}

int main() {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    std::cout << "Server running... Press Ctrl+C for graceful shutdown\n";
    std::cout << "PID: " << getpid() << "\n";
    
    int counter = 0;
    while (!shutdown_requested) {
        std::cout << "Working... iteration " << ++counter << "\r" << std::flush;
        sleep(1);
    }
    
    std::cout << "\n\n=== CLEANUP PHASE ===\n";
    std::cout << "Closing database connections...\n";
    sleep(1);
    std::cout << "Flushing buffers...\n";
    sleep(1);
    std::cout << "Saving state...\n";
    sleep(1);
    std::cout << "Cleanup complete. Goodbye!\n";
    
    return 0;
}
