#ifndef USER_H
#define USER_H

#include <queue>
#include "Packet.h"

class User {
private:
    int id;
    std::queue<Packet> packetQueue; // Queue of packets for the user
public:
    User(int id);
    void generatePacket(int size, double time); // Generate a packet
    bool hasPackets() const; // Check if the user has packets to send
    Packet getNextPacket(); // Get the next packet to transmit
};

#endif // USER_H
