//
// Created by lkj on 2022/12/01.
//

#include "packet.h"

#include <utility>

Packet::Packet() {
}

Packet::Packet(std::vector<char> buf) : m_buf(std::move(buf)) {}

void Packet::add(char byte) {
    m_buf.push_back(byte);
}

void Packet::add(char *bytes, int size) {
    for (int i = 0; i < size; ++i) {
        m_buf.push_back(bytes[i]);
    }
    m_size += size;
}

int Packet::getPacketSize() {
    return m_buf.size() - m_offset;
}

int Packet::getOffset() {
    return m_offset;
}

void Packet::setOffset(int offset) {
    m_offset = offset;
}

char *Packet::get() {
    return &m_buf[m_offset];
}
