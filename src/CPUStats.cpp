#include <CPUStats.hpp>

CPUStats::CPUStats() {
    retrievalInterval = 3;
    baseSpeed = getCPUBaseSpeed() * 1e6;
}

CPUStats::CPUStats(int __retrievalInterval) {
    retrievalInterval = __retrievalInterval;
    baseSpeed = getCPUBaseSpeed() * 1e6;
}

CPUStats::~CPUStats() {
    
}

double CPUStats::getCurrentUsed() {
    auto v0 = this->readProcFile();
    sleep(retrievalInterval);
    auto v1 = this->readProcFile();
    long long ans0 = 0;
    long long ans1 = 0;
    for (int i = 0; i < 7; ++i) {
        ans0 += v0[i];
        ans1 += v1[i];
    }
    ans0 -= v0[3];
    ans1 -= v1[3];
    // std::cout << "Used CPU time over last 3s retrieved\n";
    return (1.0 * (ans1 - ans0) / baseSpeed);

}

double CPUStats::getCurrentUsage() {
    auto future1 = std::async(&CPUStats::getCurrentUsed, this);
    auto future2 = std::async(&CPUStats::getCurrentTotal, this);
    auto cpuUsed = future1.get();
    auto cpuTotal = future2.get();
    double cpuPct = 100.0 * cpuUsed / cpuTotal;
    return cpuPct;
}

double CPUStats::getCurrentTotal() {
    auto v0 = this->readProcFile();
    sleep(retrievalInterval);
    auto v1 = this->readProcFile();
    long long ans0 = 0;
    long long ans1 = 0;
    for (int i = 0; i < 7; ++i) {
        ans0 += v0[i];
        ans1 += v1[i];
    }
    // std::cout << "Total CPU time over last 3s retrieved\n";
    return (1.0 * (ans1 - ans0) / baseSpeed);
}

std::vector<long long> CPUStats::readProcFile() {
    std::vector<long long> ret;
    ret.clear();
    std::ifstream fi;
    fi.open(STAT_PATH);
    if (fi.is_open()) {
        std::string cpuName;
        long long user, nice, system, idle, iowait, irq, softirq;
        fi >> cpuName >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
        ret = {user, nice, system, idle, iowait, irq, softirq};
    } else {
        throw std::ios_base::failure("/proc/stat not found");
    }
    fi.close();
    // for (auto i : ret) std::cout << i << " ";
    // std::cout << "\n";
    return ret;
}

double CPUStats::getCPUBaseSpeed() {
    double ret = 0;
    std::ifstream fi;
    fi.open(CPUINFO_PATH);
    if (fi.is_open()) {
        std::string cur, last;
        fi >> last;
        while (fi >> cur) {
            // std::cout << cur << "\n";
            if (cur == "MHz" && last == "cpu") {
                std::string s1, s2;
                fi >> s1 >> s2;
                ret = atof(&s2[0]);
                break;
            }
            last = cur;
        }
    }
    else {
        throw std::ios_base::failure("/proc/cpuinfo not found");
    }
    fi.close();
    return ret;
}
