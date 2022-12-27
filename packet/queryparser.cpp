//
// Created by lkj on 2022/12/22.
//

#include "queryparser.h"

QueryParser::QueryParser() {
}

QueryPtr QueryParser::parse(Buffer *buffer) {
    m_buffer = buffer;
    while (buffer->hasNext()) {
        switch (m_state) {
            case State::QNAME_BYTES:
                saveQNameBytes();
                break;
            case State::QNAME:
                parseQName();
                break;
            case State::QTYPE:
                parseQType();
                break;
            case State::QCLASS:
                parseQClass();
                break;
            case State::END:
                m_state = State::QNAME_BYTES;
                return std::move(m_query);
        }
    }
    return nullptr;
}

void QueryParser::saveQNameBytes() {
    char c = m_buffer->get();
    if (c == 0x00) {
        m_state = State::QNAME;
        return;
    }
    m_bytes.push_back(c);
}

void QueryParser::parseQName() {
    String qname;
    uint8_t size = m_bytes[0];
    for (auto idx = 0; idx < m_bytes.size(); ++idx) {
        qname += m_bytes[idx];
        --size;

        if (m_bytes.size() == idx + 1) {
            break;
        }

        if (size == 0) {
            size = m_bytes[idx];
        }
    }
    m_bytes.clear();
    m_query = std::make_unique<Query>(qname);
    m_state = State::QTYPE;
}

void QueryParser::parseQType() {
    if (m_bytes.size() < 2) {
        m_bytes.push_back(m_buffer->get());
        return;
    }
    m_query->setQType((QType)((m_bytes[0] & 0xff) & (m_bytes[1] << 8 & 0xff)));
    m_bytes.clear();
    m_state = State::QCLASS;
}

void QueryParser::parseQClass() {
    if (m_bytes.size() < 2) {
        m_bytes.push_back(m_buffer->get());
        return;
    }
    m_query->setQClass((QClass)((m_bytes[0] & 0xff) & (m_bytes[1] << 8 & 0xff)));
    m_bytes.clear();
    m_state = State::END;
}
