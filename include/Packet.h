#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int size; // Packet size in bytes
    double generationTime; // Time of packet generation
public:
    Packet(int size, double time);
    int getSize() const;
    double getGenerationTime() const;
};

#endif // PACKET_H
