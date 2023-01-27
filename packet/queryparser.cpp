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
//            case State::QNAME_BYTES:
//                saveQNameBytes();
//                break;
            case State::QNAME:
                parseQName();
                break;
//            case State::QNAME_OFFSET:
//                parseQNameOffset();
//                break;
            case State::QTYPE:
                parseQType();
                break;
            case State::QCLASS:
                parseQClass();
                break;
            case State::END:
                m_state = State::QNAME;
                return std::move(m_query);
        }
    }
    return nullptr;
}

void QueryParser::saveQNameBytes() {
    unsigned char c = m_buffer->get();

    if (m_bytes.empty() && (c & 0xc0) == 0xc0) {
        m_bytes.push_back(c & 0x3f);
        m_state = State::QNAME_OFFSET;
        return;
    }

    if (c == 0x00) {
        m_state = State::QNAME;
        return;
    }
    m_bytes.push_back(c);
}

void QueryParser::parseQName() {
    auto qname = m_queryNameParser.parse(m_buffer);
    if (qname.empty()) {
        return;
    }
//    String qname;
//    uint8_t size = m_bytes[0];
//    for (auto idx = 1; idx < m_bytes.size(); ++idx) {
//        qname += m_bytes[idx];
//        --size;
//
//        if (m_bytes.size() == idx + 1) {
//            break;
//        }
//
//        if (size == 0) {
//            ++idx;
//            size = m_bytes[idx];
//            qname += '.';
//        }
//    }
//    m_bytes.clear();
    m_query = std::make_unique<Query>(qname);
//
//    if (m_tempOffset != 0) {
//        m_buffer->setIndex(m_tempOffset);
//        m_tempOffset = 0;
//    }

    m_state = State::QTYPE;
}

void QueryParser::parseQNameOffset() {
    m_query = std::make_unique<Query>();

    uint16_t offset = (m_bytes[0] << 8) + (m_buffer->get());
    m_tempOffset = m_buffer->getIndex();
    m_buffer->setIndex(offset);
//    m_query->setNameOffset(offset);
    m_bytes.clear();

//    m_state = State::QNAME_BYTES;
}

void QueryParser::parseQType() {
    if (m_bytes.size() < 2) {
        m_bytes.push_back(m_buffer->get());
        return;
    }
    m_query->setQType((RecordType)((m_bytes[0] << 8) + (m_bytes[1])));
    m_bytes.clear();
    m_state = State::QCLASS;
}

void QueryParser::parseQClass() {
    if (m_bytes.size() < 2) {
        m_bytes.push_back(m_buffer->get());
        return;
    }
    m_query->setQClass((QClass)((m_bytes[0] << 8) + (m_bytes[1])));
    m_bytes.clear();
    m_state = State::END;
}
