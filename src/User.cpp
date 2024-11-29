#include "User.h"

User::User(int id) : id(id) {}

void User::generatePacket(int size, double time) {
    packetQueue.push(Packet(size, time));
}

bool User::hasPackets() const {
    return !packetQueue.empty();
}

Packet User::getNextPacket() {
    Packet packet = packetQueue.front();
    packetQueue.pop();
    return packet;
}
