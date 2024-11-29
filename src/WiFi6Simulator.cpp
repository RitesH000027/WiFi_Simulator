#include "WiFi6Simulator.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
using namespace std;

// Constructor to initialize allocation option and sub-channel size
WiFi6Simulator::WiFi6Simulator(bool multiSubChannelAllocation, int subChannelSize)
    : multiSubChannelAllocation(multiSubChannelAllocation), subChannelSize(subChannelSize) {
    srand(time(0));  // Seed the random number generator
}

void WiFi6Simulator::simulate(int numUsers, int simulationTime) {
    const int subChannelRate = 10; // Mbps per 20 MHz
    int subChannelCount = 20 / subChannelSize; // Number of sub-channels
    double throughputPerSubChannel = subChannelRate * subChannelSize / 20.0;
    double totalThroughput = 0.0;

    double totalDataTransmitted = 0.0;
    vector<int> userBackoffs(numUsers, 0);
    vector<int> userDelays(numUsers, 0);
    vector<int> userTransmissionCounts(numUsers, 0);
    vector<int> userRetries(numUsers, 0); // Track the number of retries for each user

    for (int t = 0; t < simulationTime; t += 5) { // 5 ms time slots
        vector<bool> subChannelOccupied(subChannelCount, false);
        vector<int> usersOnSubChannel(subChannelCount, 0); // Track number of users on each sub-channel

        for (int i = 0; i < numUsers; ++i) {
            if (userBackoffs[i] > 0) {
                userBackoffs[i] -= 5; // Decrement backoff time
                userDelays[i] += 5;   // Increment latency
            } else {
                int subChannel = i % subChannelCount; // Round-robin allocation
                if (!subChannelOccupied[subChannel]) {
                    subChannelOccupied[subChannel] = true;
                    usersOnSubChannel[subChannel] = 1;
                    totalDataTransmitted += throughputPerSubChannel * 5 / 1000.0; // Convert to KB
                    userTransmissionCounts[i]++;
                    totalThroughput += throughputPerSubChannel;
                } else {
                    // Collision happens, backoff for a longer time and increment retries
                    int collisionBackoff = (rand() % 10 + 1) * 5; // Random backoff in multiples of 5ms
                    userBackoffs[i] = collisionBackoff;
                    userDelays[i] += collisionBackoff;
                    userRetries[i]++; // Track number of retries
                }
            }
        }

        // Simulate throughput adjustment based on contention
        double contentionFactor = max(1.0 - (numUsers / (double)(subChannelCount * 5)), 0.1);
        totalThroughput *= contentionFactor;

        // Ensure throughput doesn't exceed the total available bandwidth
        totalThroughput = min(totalThroughput, (double)(subChannelRate * subChannelCount));
    }

    // Calculate average and maximum latency
    int maxLatency = *max_element(userDelays.begin(), userDelays.end());
    double averageLatency = accumulate(userDelays.begin(), userDelays.end(), 0.0) / numUsers;

    // Calculate 90th percentile latency
    vector<int> sortedDelays = userDelays;
    sort(sortedDelays.begin(), sortedDelays.end());
    int latency90thPercentile = sortedDelays[(int)(0.9 * numUsers)];

    // Display results
    cout << "WiFi6 Simulation Results:\n";
    cout << "Sub-Channel Size: " << subChannelSize << " MHz\n";
    cout << "Number of Users: " << numUsers << "\n";
    cout << "Total Throughput: " << totalThroughput / simulationTime << " Mbps\n";
    cout << "Total Data Transmitted: " << totalDataTransmitted << " KB\n";
    cout << "Average Latency: " << averageLatency << " ms\n";
    cout << "Maximum Latency: " << maxLatency << " ms\n";
    cout << "90th Percentile Latency: " << latency90thPercentile << " ms\n";
    cout << "Total Retries: " << accumulate(userRetries.begin(), userRetries.end(), 0) << "\n"; // Total retries across all users
    cout << "-----------------------------------\n";
}

