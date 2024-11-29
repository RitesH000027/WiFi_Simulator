#ifndef WIFI4SIMULATOR_H
#define WIFI4SIMULATOR_H

#include <vector>
#include "AccessPoint.h"
#include "User.h"

class WiFi4Simulator {
private:
    int bandwidth;        // Bandwidth in MHz
    double backoffLimit;  // Maximum backoff time in ms
public:
    WiFi4Simulator(int bandwidth, double backoffLimit); // Constructor
    void simulate(int numUsers, int simulationTime);    // Simulation function
};

#endif // WIFI4SIMULATOR_H
