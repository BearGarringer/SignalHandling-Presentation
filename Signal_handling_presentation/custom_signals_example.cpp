```cpp
// custom_signals.cpp - Demonstrates SIGUSR1/SIGUSR2 for IPC
#include <csignal>
#include <iostream>
#include <unistd.h>

volatile sig_atomic_t usr1_count = 0;
volatile sig_atomic_t usr2_count = 0;

void user_signal_handler(int signum) {
    if (signum == SIGUSR1) {
        usr1_count++;
    } else if (signum == SIGUSR2) {
        usr2_count++;
    }
}

int main() {
    signal(SIGUSR1, user_signal_handler);
    signal(SIGUSR2, user_signal_handler);
    
    pid_t pid = getpid();
    
    std::cout << "Custom Signal Handler Demo\n";
    std::cout << "==========================\n";
    std::cout << "Process ID: " << pid << "\n\n";
    std::cout << "Send signals from another terminal:\n";
    std::cout << "  kill -SIGUSR1 " << pid << "\n";
    std::cout << "  kill -SIGUSR2 " << pid << "\n";
    std::cout << "  kill -SIGTERM " << pid << "  (to exit)\n\n";
    
    std::cout << "Waiting for signals... (Ctrl+C to exit)\n\n";
    
    int prev_usr1 = 0, prev_usr2 = 0;
    
    while (true) {
        if (usr1_count != prev_usr1) {
            std::cout << "📨 SIGUSR1 received! Count: " << usr1_count << std::endl;
            prev_usr1 = usr1_count;
        }
        
        if (usr2_count != prev_usr2) {
            std::cout << "📬 SIGUSR2 received! Count: " << usr2_count << std::endl;
            prev_usr2 = usr2_count;
        }
        
        sleep(1);
    }
    
    return 0;
}
```
