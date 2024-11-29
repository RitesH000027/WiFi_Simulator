#include "WiFi5Simulator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

WiFi5Simulator::WiFi5Simulator() {}

void WiFi5Simulator::simulate(int numUsers, int simulationTime) {
    // Seed for random number generation
    srand(time(0));

    // Simulation Variables
    int totalData = 0;        // Total data transmitted (in bytes)
    double totalLatency = 0;  // Total latency across all transmissions (in ms)
    double maxLatency = 0;    // Maximum latency experienced
    int transmissions = 0;    // Total number of transmissions

    // Base WiFi 5 (802.11ac) parameters
    const double totalBandwidth = 100.0; // Total bandwidth in Mbps
    const int csiPacketSize = 200;       // CSI packet size (bytes)
    const int dataPacketSize = 1024;     // Data packet size (1 KB)
    const int parallelCommTime = 15;     // Parallel communication time (ms)
    const int broadcastLatency = 2;      // Broadcast packet latency (ms)

    double throughput;

    // Adjust throughput scaling
    if (numUsers == 1) {
        throughput = totalBandwidth; // Full bandwidth for single user
    } else {
        // Non-linear throughput reduction with minimum guarantee
        throughput = totalBandwidth / pow(numUsers, 0.5); // Improved scaling
        throughput = max(5.0, throughput); // Minimum throughput guarantee
    }

    // Simulation loop (time progression)
    for (int t = 0; t < simulationTime; t += parallelCommTime + broadcastLatency) {
        // Phase 1: Broadcast Packet
        totalLatency += broadcastLatency;
        maxLatency = max(maxLatency, static_cast<double>(broadcastLatency));

        // Phase 2: CSI Exchange (200 bytes per user)
        for (int i = 0; i < numUsers; ++i) {
            int csiLatency = rand() % 3 + 1; // Random latency for CSI exchange (1–3 ms)
            totalLatency += csiLatency;
            maxLatency = max(maxLatency, static_cast<double>(csiLatency));
            transmissions++; // Count CSI transmission
        }

        // Phase 3: Parallel Communication (15 ms for all users)
        double perUserBandwidth = throughput / numUsers; // Bandwidth per user
        for (int i = 0; i < numUsers; ++i) {
            int packetsTransmitted = rand() % 5 + 1; // Random packets per user (1 to 5 packets)
            int userData = packetsTransmitted * dataPacketSize; // Data sent by user

            // Simulate channel noise (reduce throughput by 0–20%)
            double channelQualityFactor = 1.0 - (rand() % 21 / 100.0);
            userData = static_cast<int>(userData * channelQualityFactor);

            totalData += userData; // Accumulate total data transmitted
            transmissions += packetsTransmitted; // Count packets transmitted
            totalLatency += parallelCommTime; // Add parallel communication time
            maxLatency = max(maxLatency, static_cast<double>(parallelCommTime));
        }
    }

    // Final calculations (including average latency and throughput)
    double avgLatency = transmissions ? totalLatency / transmissions : 0;
    double simulationThroughput = (totalData * 8.0) / (simulationTime * 1e3); // Convert bytes to Mbps
    simulationThroughput = min(simulationThroughput, totalBandwidth); // Ensure throughput doesn't exceed base

    // Per-user throughput
    double perUserThroughput = simulationThroughput / numUsers;

    // Output results
    cout << "\nWiFi 5 Simulation Results:\n";
    cout << "Number of Users: " << numUsers << endl;
    cout << "Total Throughput (Aggregated): " << simulationThroughput << " Mbps\n";
    cout << "Per User Throughput: " << perUserThroughput << " Mbps\n";
    cout << "Average Latency: " << avgLatency << " ms\n";
    cout << "Maximum Latency: " << maxLatency << " ms\n";
    cout << "Total Data Transmitted: " << totalData << " bytes\n" << endl;
}
