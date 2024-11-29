#include "AccessPoint.h"

AccessPoint::AccessPoint() : isChannelBusy(false) {}

bool AccessPoint::channelStatus() const {
    return isChannelBusy;
}

void AccessPoint::setChannelStatus(bool status) {
    isChannelBusy = status;
}
