#include <CPUStats.hpp>

CPUStats::CPUStats() {
    retrievalInterval = 3;
    baseSpeed = getCPUBaseSpeed() * 1e6;
}

CPUStats::CPUStats(int __retrievalInterval) {
    if (__retrievalInterval <= 0) {
        throw std::range_error("Retrieval Interval must be positive");
    }
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
    for (int i = 0; i < int(v0.size()); ++i) {
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
        std::string inp;
        int cnt = 0;
        while (fi >> inp) {
            if (inp[0] >= '0' && inp[0] <= '9') {
                long long num = atoll(&inp[0]);
                ret.push_back(num);
            } else {
                ++cnt;
            }
            if (cnt == 2) {
                break;
            } 
        }
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
    fi.close();
    return ret;
}
