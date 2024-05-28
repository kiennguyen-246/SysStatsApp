#ifndef CPUSTATS_GUARD
#define CPUSTATS_GUARD

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <future>

#include <SysStats.hpp>

class CPUStats: public SysStats {
    public:
    const std::string STAT_PATH = "/proc/stat";
    const std::string CPUINFO_PATH = "/proc/cpuinfo";

    /**
     * Default constructor
    */
    CPUStats();

    /**
     * Construct an object with preset retrieval interval
    */
    CPUStats(int __retrievalInterval);

    /**
     * Default destructor
    */
    ~CPUStats();

    /**
     * Get the total CPU time (in second) used by processes in the last 3 seconds
    */
    double getCurrentUsed();

    /**
     * Get the total CPU time (in seconds) used by processes in the last 3 seconds
    */
    double getCurrentTotal();

    /**
     * Get the CPU usage percentage used by processes in the last 3 seconds
    */
    double getCurrentUsage();

    private:
    int retrievalInterval;
    double baseSpeed;

    std::vector<long long> readProcFile();

    double getCPUBaseSpeed();
};
#endif