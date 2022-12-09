//
// Created by lkj on 2022/12/05.
//

#ifndef DNS_CLIENT_PACKETBUILDER_H
#define DNS_CLIENT_PACKETBUILDER_H


#include "struct/packet.h"
#include "struct/header.h"

class PacketBuilder {
public:
    PacketPtr build(Header* header);

private:
    unsigned long flagsToLong(Header* header);
};


#endif //DNS_CLIENT_PACKETBUILDER_H
