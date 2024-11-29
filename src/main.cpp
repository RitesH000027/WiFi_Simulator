#include <iostream>
#include "WiFi4Simulator.h"
#include "WiFi5Simulator.h"
#include "WiFi6Simulator.h"

using namespace std;

int main() {
    int simulationTime = 1000; // 1 second in ms

    int userCounts[] = {1, 10, 100};

    // Choose WiFi6 Allocation Mode and Sub-Channel Size
    bool multiSubChannelAllocation;
    int subChannelSize;

    cout << "Choose WiFi6 Allocation Mode:\n";
    cout << "1. Multi-Sub-Channel Allocation Enabled\n";
    cout << "2. Single-User Access to One Sub-Channel\n";
    cout << "Enter your choice (1/2): ";
    int allocationChoice;
    cin >> allocationChoice;
    multiSubChannelAllocation = (allocationChoice == 1);

    cout << "Choose Sub-Channel Size:\n";
    cout << "1. 2 MHz\n";
    cout << "2. 4 MHz\n";
    cout << "3. 10 MHz\n";
    cout << "Enter your choice (1/2/3): ";
    int sizeChoice;
    cin >> sizeChoice;

    // Map size choice to sub-channel size in MHz
    switch (sizeChoice) {
        case 1: subChannelSize = 2; break;
        case 2: subChannelSize = 4; break;
        case 3: subChannelSize = 10; break;
    }

    for (int users : userCounts) {
        cout << endl;
        cout << "Simulating WiFi4 for " << users << " users...\n";
        WiFi4Simulator wifi4(20, 5);
        wifi4.simulate(users, simulationTime);

        cout << "Simulating WiFi5 for " << users << " users...\n";
        WiFi5Simulator wifi5;
        wifi5.simulate(users, simulationTime);

        cout << "Simulating WiFi6 for " << users << " users...\n";
        WiFi6Simulator wifi6(multiSubChannelAllocation, subChannelSize);
        wifi6.simulate(users, simulationTime);
    }

    return 0;
}
