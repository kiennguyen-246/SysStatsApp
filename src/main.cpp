#include <iostream>
#include <future>
#include <iomanip>

#include <CPUStats.hpp>
#include <RAMStats.hpp>

int main(int argc, char* argv[]) {
    int retrievalInterval = 0;
    if (argc == 1) {
        retrievalInterval = 3;
    } 
    else {
        retrievalInterval = atoi(argv[1]);
    }
    // int retrievalInterval = 3;
    CPUStats* cpus;
    RAMStats* rams;
    try {
        cpus = new CPUStats(retrievalInterval);
        rams = new RAMStats(retrievalInterval);
    } catch (std::runtime_error& e) {
        std::cout << "An error occured.\n";
        return 0;
    }
    
    for (int loop = 0; loop < 100; ++loop) {
        // std::cout << "Loop " << loop << ":\n";
        auto futureCPUUsage = std::async(&CPUStats::getCurrentUsage, cpus);
        auto futureRAMUSage = std::async(&RAMStats::getCurrentUsage, rams);
        auto future3 = std::async(&RAMStats::getCurrentUsed, rams);
        auto future4 = std::async(&RAMStats::getCurrentTotal, rams);

        auto ramUsed = future3.get();
        auto ramTotal = future4.get();
        double cpuPct = futureCPUUsage.get();
        double ramPct = futureRAMUSage.get();

        printf("Current CPU usage: %0.2f%%\n", cpuPct);
        printf("Current RAM usage: %0.0f/%0.0f (kb) (%0.2f%%)\n", ramUsed, ramTotal, ramPct);
    }
}