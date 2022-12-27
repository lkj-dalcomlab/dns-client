//
// Created by lkj on 2022/12/05.
//

#ifndef DNS_CLIENT_PACKETBUILDER_H
#define DNS_CLIENT_PACKETBUILDER_H

#include "../struct/packet.h"
#include "../struct/header.h"
#include "../buffer/buffer.h"

class PacketBuilder {
public:
    BufferPtr build(Header* header);

private:
    uint16_t flagsToLong(Header* header);
    std::vector<char> nameToQName(const String &name);
};


#endif //DNS_CLIENT_PACKETBUILDER_H
