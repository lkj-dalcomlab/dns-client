//
// Created by lkj on 2022/12/05.
//

#include "bufferbuilder.h"
#include <bitset>
#include <sstream>

// little-endian to big-endian
BufferPtr BufferBuilder::build(Packet *header) {
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
        auto query = header->getQuery(i);
        auto name = query->getName();
        auto qname = nameToQName(name);
        buf.insert(buf.end(), qname.begin(), qname.end());

        uint16_t qtype = (uint16_t)query->getQType();
        buf.push_back((qtype >> 8) & 0xff); // qtype
        buf.push_back(qtype & 0xff);

        uint16_t qclass = (uint16_t)query->getQClass();
        buf.push_back((qclass >> 8) & 0xff); // qclass
        buf.push_back(qclass & 0xff);
    }

    char *bufArray = new char[buf.size()];
    for (auto i = 0; i < buf.size(); ++i) {
        bufArray[i] = buf[i];
    }
    auto buffer = std::make_unique<Buffer>();
    buffer->appendBuffer(bufArray, buf.size());
    return std::move(buffer);
}

uint16_t BufferBuilder::flagsToLong(Packet *header) {
    std::bitset<16> bits;
    bits.reset();

    for (auto i = 0; i < bits.size(); ++i) {
        bits.set(i, false);
    }

    bits.set(7, header->isResponse());

    OpCode opCode = header->getOpCode();
    short i = static_cast<short>(opCode);
    bits.set(6, i & 0x08);
    bits.set(5, i & 0x04);
    bits.set(4, i & 0x02);
    bits.set(3, i & 0x01);

    bits.set(2, header->isAa());
    bits.set(1, header->isTc());
    bits.set(0, header->isRd());
    bits.set(15, header->isRa());

    bits.set(14, header->getZ() & 0x04);
    bits.set(13, header->getZ() & 0x02);
    bits.set(12, header->getZ() & 0x01);

    bits.set(11, header->getRcode() & 0x08);
    bits.set(10, header->getRcode() & 0x04);
    bits.set(9, header->getRcode() & 0x02);
    bits.set(8, header->getRcode() & 0x01);

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

std::vector<char> BufferBuilder::nameToQName(const String &name) {
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
