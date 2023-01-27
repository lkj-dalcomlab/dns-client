//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_PACKETBUILDER_H
#define DNS_CLIENT_PACKETBUILDER_H


#include "struct/packet.h"
#include <string>

class PacketBuilder {
private:
    static uint8_t m_id;
public:
    PacketPtr build(const std::string &domain, RecordType type);
};


#endif //DNS_CLIENT_PACKETBUILDER_H
