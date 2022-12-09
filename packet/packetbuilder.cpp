//
// Created by lkj on 2022/12/05.
//

#include "packetbuilder.h"
#include <bitset>

PacketPtr PacketBuilder::build(Header *header) {
    auto packet = std::make_unique<Packet>();

    auto id = header->getId();
    unsigned char bytes[2] = {0, };
    bytes[0] = id & 0xff;
    bytes[1] = (id >> 8) & 0xff;
    packet->add(bytes, 2);

    auto flags = flagsToLong(header);
    bytes[0] = flags & 0xff;
    bytes[1] = (flags >> 8) & 0xff;
    packet->add(bytes, 2);;

    return packet;
}

unsigned long PacketBuilder::flagsToLong(Header *header) {
    std::bitset<16> bits;
    bits.reset();
    bits.set(0, header->isResponse());

    OpCode opCode = header->getOpCode();
    short i = static_cast<short>(opCode);
    bits.set(1, i & 0x01);
    bits.set(2, i & 0x02);
    bits.set(3, i & 0x04);
    bits.set(4, i & 0x10);

    bits.set(5, header->isAa());
    bits.set(6, header->isTc());
    bits.set(7, header->isRd());
    bits.set(8, header->isRa());

    bits.set(9, header->getZ() & 0x01);
    bits.set(10, header->getZ() & 0x02);
    bits.set(11, header->getZ() & 0x04);

    bits.set(12, header->getRcode() & 0x01);
    bits.set(13, header->getRcode() & 0x02);
    bits.set(14, header->getRcode() & 0x04);
    bits.set(15, header->getRcode() & 0x10);

    return bits.to_ulong();
}
