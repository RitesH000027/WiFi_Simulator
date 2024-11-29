#ifndef WIFI6SIMULATOR_H
#define WIFI6SIMULATOR_H

#include <iostream>
#include <cmath>
using namespace std;

class WiFi6Simulator {
private:
    bool multiSubChannelAllocation;  // Flag for multi-sub-channel allocation
    int subChannelSize;              // Size of each sub-channel in MHz

public:
    // Constructor to initialize allocation option and sub-channel size
    WiFi6Simulator(bool multiSubChannelAllocation, int subChannelSize);

    // Simulation function
    void simulate(int numUsers, int simulationTime);
};

#endif // WIFI6SIMULATOR_H
