#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

class AccessPoint {
private:
    bool isChannelBusy; // True if channel is currently being used
public:
    AccessPoint();
    bool channelStatus() const; // Check if the channel is busy
    void setChannelStatus(bool status); // Set the channel status
};

#endif // ACCESSPOINT_H
