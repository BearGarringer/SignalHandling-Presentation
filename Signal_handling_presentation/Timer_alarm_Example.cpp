// timer_alarm.cpp - Demonstrates SIGALRM for timeouts
#include <csignal>
#include <iostream>
#include <unistd.h>

volatile sig_atomic_t alarm_count = 0;

void alarm_handler(int signum) {
    alarm_count++;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, nullptr);
    
    std::cout << "Setting alarm for 3 seconds...\n";
    alarm(3);
    
    std::cout << "Doing work while waiting for alarm...\n";
    for (int i = 0; i < 10 && alarm_count == 0; i++) {
        std::cout << "  Working: " << i << std::endl;
        sleep(1);
    }
    
    if (alarm_count > 0) {
        std::cout << "\n⏰ ALARM! Timeout occurred after 3 seconds\n";
    }
    
    std::cout << "\n--- Periodic Alarm Demo ---\n";
    alarm_count = 0;
    for (int i = 0; i < 5; i++) {
        alarm(2);
        int prev_count = alarm_count;
        
        while (alarm_count == prev_count) {
            std::cout << "  Waiting for alarm " << (i + 1) << "...\r" << std::flush;
            usleep(100000);
        }
        
        std::cout << "\n  ✓ Alarm " << (i + 1) << " triggered!\n";
    }
    
    return 0;
}
