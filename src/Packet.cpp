#include "Packet.h"

Packet::Packet(int size, double time) : size(size), generationTime(time) {}

int Packet::getSize() const {
    return size;
}

double Packet::getGenerationTime() const {
    return generationTime;
}
