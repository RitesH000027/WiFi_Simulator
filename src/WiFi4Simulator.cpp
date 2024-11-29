#include "WiFi4Simulator.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;

// Constructor implementation
WiFi4Simulator::WiFi4Simulator(int bandwidth, double backoffLimit)
    : bandwidth(bandwidth), backoffLimit(backoffLimit) {}

void WiFi4Simulator::simulate(int numUsers, int simulationTime) {
    // Random number generation setup
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> probDist(0, 1);
    uniform_int_distribution<> backoffDist(1, 2);

    // Theoretical max throughput calculation
    double channelWidth = 20.0; // MHz
    double bitsPerSymbol = log2(256); // 256-QAM 
    double symbolRate = channelWidth * 1e6 / 4.0; // OFDM symbols per second
    double codingRate = 5.0 / 6.0; // Coding rate
    double packetSizeBits = 1024 * 8.0; // 1 KB packet size in bits
    
    // Theoretical max throughput (in Mbps)
    double maxThroughput = symbolRate * bitsPerSymbol * codingRate * 1e-6;

    // Simulation variables
    double totalDataTransmitted = 0.0;
    double totalLatency = 0.0;
    double maxLatency = 0.0;
    int totalSuccessfulTransmissions = 0;

    // User transmission tracking
    vector<int> backoffTimes(numUsers, 0);
    vector<int> collisionCounters(numUsers, 0);

    // Transmission probability adjustment for multi-user scenario
    double baseTransmitProb = 0.9; // Probability of transmission for single user
    double multiUserTransmitProb = baseTransmitProb / (1 + numUsers * 0.05); // Adjust for multiple users

    // Simulation loop
    for (int t = 0; t < simulationTime; ++t) {
        // Track transmission attempts
        vector<int> attemptingUsers;

        // Determine which users can attempt transmission
        for (int i = 0; i < numUsers; ++i) {
            // If backoff time is zero, user can attempt transmission
            if (backoffTimes[i] == 0) {
                // Adjusted transmission probability for multiple users
                double transmitProb = multiUserTransmitProb / (1 + collisionCounters[i]);
                
                if (probDist(gen) < transmitProb) {
                    attemptingUsers.push_back(i);
                }
            }
        }

        // Transmission logic
        if (attemptingUsers.size() == 1) {
            // Successful transmission
            int user = attemptingUsers[0];
            
            // Minimal latency for single user
            double currentLatency = numUsers == 1 ? 1.0 : backoffDist(gen);
            totalLatency += currentLatency;
            maxLatency = max(maxLatency, currentLatency);

            // Transmit data
            totalDataTransmitted += packetSizeBits;
            totalSuccessfulTransmissions++;

            // Reset backoff and collision counter for this user
            backoffTimes[user] = numUsers == 1 ? 1 : backoffDist(gen);
            collisionCounters[user] = 0;
        }
        else if (attemptingUsers.size() > 1) {
            // Collision occurred
            for (int user : attemptingUsers) {
                // Exponential backoff with collision counter
                collisionCounters[user]++;
                backoffTimes[user] = backoffDist(gen) * (1 << min(5, collisionCounters[user]));
            }
        }

        // Decrease backoff times
        for (int i = 0; i < numUsers; ++i) {
            if (backoffTimes[i] > 0) {
                backoffTimes[i]--;
            }
        }
    }

    // Calculate actual throughput
    double actualThroughput = (totalDataTransmitted / (simulationTime * 1e6)); // Mbps

    // Calculate average latency
    double avgLatency = totalSuccessfulTransmissions
                            ? totalLatency / totalSuccessfulTransmissions
                            : 0.0;

    // Display results
    cout << "WiFi 4 Simulation Results:\n";
    cout << "Theoretical Max Throughput: " << maxThroughput << " Mbps\n";
    cout << "Number of Users: " << numUsers << endl;
    cout << "Actual Throughput: " << actualThroughput << " Mbps\n";
    cout << "Average Latency: " << avgLatency << " ms\n";
    cout << "Maximum Latency: " << maxLatency << " ms\n";
    cout << "Total Successful Transmissions: " << totalSuccessfulTransmissions << endl;
    cout << "Total Data Transmitted: " << totalDataTransmitted << " bits\n\n";
}
