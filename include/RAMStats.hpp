#ifndef RAMSTATS_GUARD
#define RAMSTATS_GUARD

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <future>

#include <SysStats.hpp>

class RAMStats: public SysStats {
    public:
    const std::string MEMINFO_PATH = "/proc/meminfo";

    /**
     * Default constructor
    */
    RAMStats();

    /**
     * Construct an object with preset retrieval interval
    */
    RAMStats(int __retrievalInterval);

    /**
     * Default destructor
    */
    ~RAMStats();

    /**
     * Get the total RAM time used by processes in the last 3 seconds
    */
    double getCurrentUsed();

    /**
     * Get the total RAM time used by processes in the last 3 seconds
    */
    double getCurrentTotal();

    /**
     * Get the CPU usage percentage used by processes in the last 3 seconds
    */
    double getCurrentUsage();

    private:
    int retrievalInterval;

    std::vector<long long> readProcFile();
};
#endif