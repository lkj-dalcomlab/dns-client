//
// Created by lkj on 2022/12/05.
//

#include "packetbuilder.h"
#include <bitset>
#include <sstream>

// little-endian to big-endian
BufferPtr PacketBuilder::build(Header *header) {
    std::vector<char> buf;

    uint16_t id = header->getId();
    buf.push_back((id >> 8) & 0xff);
    buf.push_back(id & 0xff);

    uint16_t flags = flagsToLong(header);
    buf.push_back(flags & 0xff);
    buf.push_back((flags >> 8) & 0xff);

    uint16_t queryCount = header->getQDCount();
    buf.push_back((queryCount >> 8) & 0xff);
    buf.push_back(queryCount & 0xff);

    //Answer count
    buf.push_back(0x00);
    buf.push_back(0x00);

    //Authority count
    buf.push_back(0x00);
    buf.push_back(0x00);

    //Additional count
    buf.push_back(0x00);
    buf.push_back(0x00);

    for (int i = 0; i < queryCount; ++i) {
        auto question = header->getQuery(i);
        auto name = question->getName();
        auto qname = nameToQName(name);
        buf.insert(buf.end(), qname.begin(), qname.end());

        buf.push_back(0x00); // qtype -> A
        buf.push_back(0x01);

        buf.push_back(0x00); // qclass -> IN (internet)
        buf.push_back(0x01);
    }

    char *buffer = new char[buf.size()];
    for (auto i = 0; i < buf.size(); ++i) {
        buffer[i] = buf[i];
    }
    return std::make_unique<Buffer>(buffer, buf.size());
}

uint16_t PacketBuilder::flagsToLong(Header *header) {
    std::bitset<16> bits;
    bits.reset();

//    for (auto i = 0; i < bits.size(); ++i) {
//        bits.set(i, false);
//    }
//    bits.set(8, true);
//    bits.set(12, true);
//    bits.set(13, true);
//    bits.set(15, true);


    bits.set(7, header->isResponse());

    OpCode opCode = header->getOpCode();
    short i = static_cast<short>(opCode);
    bits.set(6, i & 0x01);
    bits.set(5, i & 0x02);
    bits.set(4, i & 0x04);
    bits.set(3, i & 0x08);

    bits.set(2, header->isAa());
    bits.set(1, header->isTc());
    bits.set(0, header->isRd());
    bits.set(15, header->isRa());

    bits.set(14, header->getZ() & 0x01);
    bits.set(13, header->getZ() & 0x02);
    bits.set(12, header->getZ() & 0x04);

    bits.set(11, header->getRcode() & 0x01);
    bits.set(10, header->getRcode() & 0x02);
    bits.set(9, header->getRcode() & 0x04);
    bits.set(8, header->getRcode() & 0x08);

    auto flags = bits.to_ulong();
    return flags;
}

std::vector<String> split(const String &text, char delimiter) {
    std::vector<String> internal;
    std::stringstream ss(text);
    String temp;
    while (getline(ss, temp, delimiter)) {
        internal.push_back(temp);
    }
    return internal;
}

void addString(const String &str, std::vector<char> &chars) {
    for (char c : str) {
        chars.push_back(c);
    }
}

std::vector<char> PacketBuilder::nameToQName(const String &name) {
    std::vector<char> qname;
    auto domains = split(name, '.');
    for (auto i = 0; i < domains.size(); ++i) {
        auto domain = domains.at(i);
        char size = domain.size() & 0xff;
        qname.push_back(size);
        addString(domain, qname);
    }
    qname.push_back(0x00);
    return qname;
}
