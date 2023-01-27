//
// Created by lkj on 2023/01/25.
//

#include "arecordparser.h"
#include "struct/arecord.h"
#include <sstream>

RecordPtr ARecordParser::parse(Buffer *buffer) {
    m_buffer = buffer;
    while (buffer->hasNext()) {
        switch (m_state) {
            case State::INIT:
                m_record = nullptr;
                m_state = State::RDATA_LENGTH;
                break;
            case State::RDATA_LENGTH:
                parseRdLength();
                break;
            case State::IP:
                parseIP();
                break;
            case State::END:
                m_state = State::INIT;
                return std::move(m_record);
        }
    }
    return m_state == State::END ? std::move(m_record) : nullptr;
}

void ARecordParser::parseRdLength() {
    m_bytes.push_back(m_buffer->get());
    if (m_bytes.size() < 2) {
        return;
    }

    uint32_t rdLength{0};
    rdLength += (m_bytes[0] & 0xff) << 8;
    rdLength += (m_bytes[1] & 0xff);

    m_rDataLength = rdLength;
    m_state = State::IP;
    m_bytes.clear();
}

void ARecordParser::parseIP() {
    m_bytes.push_back(m_buffer->get());
    if (m_bytes.size() != m_rDataLength) {
        return;
    }

    m_record = std::make_unique<ARecord>(toIP());

    m_state = State::END;
    m_bytes.clear();
}

String ARecordParser::toIP() {
    std::stringstream stream;
    for (uint8_t idx = 1; const auto &item: m_bytes) {
        stream << std::to_string((unsigned char)item);
        if (idx++ < m_bytes.size()) {
            stream << '.';
        }
    }
    return stream.str();
}