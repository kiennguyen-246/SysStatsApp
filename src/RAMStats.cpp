#include <RAMStats.hpp>

RAMStats::RAMStats() {
    retrievalInterval = 3;
}

RAMStats::RAMStats(int __retrievalInterval) {
    retrievalInterval = __retrievalInterval;
}

RAMStats::~RAMStats() {
    
}

double RAMStats::getCurrentUsed() {
    sleep(retrievalInterval);
    auto v = this->readProcFile();
    return v[0] - v[1];

}

double RAMStats::getCurrentTotal() {
    sleep(retrievalInterval);
    auto v = this->readProcFile();
    return v[0];
}

double RAMStats::getCurrentUsage() {
    auto future3 = std::async(&RAMStats::getCurrentUsed, this);
    auto future4 = std::async(&RAMStats::getCurrentTotal, this);
    auto ramUsed = future3.get();
    auto ramTotal = future4.get();
    double ramPct = 100.0 * ramUsed / ramTotal;
    return ramPct;
}

std::vector<long long> RAMStats::readProcFile() {
    std::vector<long long> ret;
    ret.clear();
    std::ifstream fi;
    fi.open(MEMINFO_PATH);
    if (fi.is_open()) {
        std::string cat0, cat1, unit0, unit1;
        long long total, free;
        fi >> cat0 >> total >> unit0 >> cat1 >> free >> unit1;
        // std::cout << cat0 << " " << total << " " << unit0 << " " << cat1 << " " << free << " " << unit1 << "\n";
        ret = {total, free};
    } else {
        throw std::ios_base::failure("/proc/meminfo not found");
    }
    fi.close();
    // for (auto i : ret) std::cout << i << " ";
    // std::cout << "\n";
    return ret;
}
