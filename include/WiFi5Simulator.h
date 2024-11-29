#ifndef WIFI5SIMULATOR_H
#define WIFI5SIMULATOR_H

#include "AccessPoint.h"
#include "User.h"

class WiFi5Simulator {
public:
    WiFi5Simulator();
    void simulate(int numUsers, int simulationTime); // Simulate WiFi 5 MU-MIMO communication
};

#endif // WIFI5SIMULATOR_H
