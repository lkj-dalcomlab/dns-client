//
// Created by lkj on 2022/12/01.
//

#include "packetbuilder.h"
uint8_t PacketBuilder::m_id = 1;
PacketPtr PacketBuilder::build(const std::string &domain, RecordType type) {
    auto packet = std::make_unique<Packet>();
    packet->setId(m_id);

    auto query = std::make_unique<Query>(domain);
    query->setQType(type);
    packet->addQuery(std::move(query));

    m_id++;
    return packet;
}
